/*
    Project: ASN1Lib

    Module: asn-memmgr.Cpp

    Description: ASN.1 encode/decode garbage collector enabled memory manager

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "ASN1-Lib.h"

using namespace std;

// #define MEMMGR_DEBUG

namespace // unnamed
{
    const size_t MEMQUANT = 512;

    inline size_t alignTo8( size_t n )
    {
        return n % 8 ? n + 8 - ( n % 8 ) : n;
        }
}

///////////////////////////////////////////////////////////////////////////////
// MemPool implementation

MemPool::MemPool( const char* verbose_name, int initial_count )
{
    name = verbose_name;

#ifdef MEMMGR_DEBUG
    TRACE( "MemPool[ " << name << " ].Construct, initial count = "
        << initial_count );
#endif

    freeList = NULL;

    std_allocate_count = 0;
    std_free_count = 0;

    nstd_allocate_count = 0;
    nstd_free_count = 0;

    // Preallocate initial_count of free standard memory blocks
    //
    for ( int i = 0; i < initial_count; i++ )
    {
        Free( Allocate () );
        }
    }

MemPool:: ~MemPool( void )
{
    mutex.Lock ();

    // Remove free MemBlock list.
    //
    MemBlockStd* ptr = freeList;
    while( ptr )
    {
        MemBlockStd* ptrNext = ptr->next;
        ::delete[] (uint8*) ptr;
        ptr = ptrNext;
        }

    mutex.Unlock ();
    }

void MemPool:: DumpStatistics( CTsvcLIB::LOG& os )
{
    os  << "MemPool[ " << name << " ]: Statistics:" << CTsvcLIB::eline
        << "    Standard allocates......: " << std_allocate_count << CTsvcLIB::eline
        << "    Standard frees..........: " << std_free_count << CTsvcLIB::eline
        << "    Non-standard allocates..: " << nstd_allocate_count << CTsvcLIB::eline
        << "    Non-standard frees......: " << nstd_free_count << CTsvcLIB::eline;
    }

MemBlockStd* MemPool:: Allocate ()
{
#ifdef MEMMGR_DEBUG
    TRACE( "MemPool [" << name << " ].Allocate()" );
#endif

    mutex.Lock ();

    MemBlockStd* ptr = NULL;

    if ( freeList )
    {
        // Rremove block from chain
        std_allocate_count ++;
        ptr = freeList;
        freeList = freeList->next;
        }
    else
    {
        // Create new block from normal heap
        std_allocate_count ++;
        ptr = (MemBlockStd*) ::new uint8[ MEMQUANT ];
        }

    // Initialize it...
    //
    ptr->signature = 314159265;
    ptr->basePool = this;
    ptr->next = NULL;
    ptr->nextFreePtr = alignTo8( sizeof( MemBlockStd ) );

    mutex.Unlock ();

    return ptr;
    }

void MemPool:: Free( void* block )
{
#ifdef MEMMGR_DEBUG
    TRACE( "MemPool[ " << name << " ].FreeMemBlock" );
#endif

    TRASSERT( block != NULL );

    if ( block == NULL )
        return;

    mutex.Lock ();

    // Cast pointer to standard block pointer and verify
    // that it originated from this memory pool and that it has
    // valid signature.
    //
    MemBlockStd* ptr = (MemBlockStd*) block;

    if ( ptr->signature != 0 && ptr->basePool != this )
    {
        CTsvcLIB::LOG( CTsvcLIB::DBG_ERROR ) << "MemPool::Free: " 
            << block << " --- OUCH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" 
            << CTsvcLIB::eline;
        return;
        }

    std_free_count++;

    // Put standard block back into free list.
    //
    ptr->next = freeList;
    freeList = ptr;

    mutex.Unlock ();
    }

///////////////////////////////////////////////////////////////////////////////
// MemBlock implementation

MemBlock:: MemBlock( MemPool* mp )
{
#ifdef MEMMGR_DEBUG
    TRACE( "MemPool[ " << mp->GetName() << " ].MemBlock.Construct" );
#endif

    signature = 314159265;
    basePool = mp;
    stdList = NULL;
    specList = NULL;
    nextFreePtr = alignTo8( sizeof( MemBlock ) );

    G.curIndent = 0;

    G.stk.first = NULL;
    G.stk.lastUsed = NULL;
    G.stk.totalByteLen = 0;
    G.stk.unusedBits = 0;
    }

MemBlock:: MemBlock( MemPool& mp )
{
#ifdef MEMMGR_DEBUG
    TRACE( "MemPool[ " << mp.GetName() << " ].MemBlock.Construct" );
#endif

    signature = 314159265;
    basePool = &mp;
    stdList = NULL;
    specList = NULL;
    nextFreePtr = alignTo8( sizeof( MemBlock ) );

    G.curIndent = 0;

    G.stk.first = NULL;
    G.stk.lastUsed = NULL;
    G.stk.totalByteLen = 0;
    G.stk.unusedBits = 0;
    }

MemBlock:: ~MemBlock( void )
{
    // Delete standard memory blocks
    MemBlockStd* ptr = stdList;
    while( ptr )
    {
        MemBlockStd* ptrNext = ptr->next;
        basePool->Free( ptr );
        ptr = ptrNext;
        }

    // Delete special memory blocks
    MemBlockSpec* ptr2 = specList;
    while( ptr2 )
    {
        MemBlockSpec* ptrNext = ptr2->next;
        ::delete[] (uint8*) ptr2;
        ptr2 = ptrNext;
        }
    }

void* MemBlock::Allocate( size_t n )
{
#ifdef MEMMGR_DEBUG
    TRACE( "MemPool[ " << basePool->GetName() << " ].MemBlock.Allocate, size = " << n );
#endif

    void* ptr = NULL;

    if ( n == 0 )
        n = 4; // we have to create unique pointer anyhow

    if ( stdList == NULL && nextFreePtr + n <= MEMQUANT )
    {
        // Requested memory can fit in current local arena
        //
        ptr = (uint8*)this + nextFreePtr;
        nextFreePtr += alignTo8( n );
        }
    else if ( stdList != NULL && stdList->nextFreePtr + n <= MEMQUANT )
    {
        // Requested memory can fit in currently filling standard block
        //
        ptr = (uint8*)stdList + stdList->nextFreePtr;
        stdList->nextFreePtr += alignTo8( n );
        }
    else if ( alignTo8( sizeof( MemBlockStd ) ) + n <= MEMQUANT )
    {
        // Requested memory can fit in newly allocated standard block
        //
        MemBlockStd* mb = basePool->Allocate();
        mb->signature = 314159265;
        mb->basePool = basePool;
        mb->next = stdList;
        mb->nextFreePtr = alignTo8( sizeof( MemBlockStd ) );
        stdList = mb;

        ptr = (uint8*)stdList + stdList->nextFreePtr;
        stdList->nextFreePtr += alignTo8( n );
        }
    else
    {
        // Requested memory can not fit at all in any standard block,
        // and we must allocated it in special block
        //
        MemBlockSpec* mb = (MemBlockSpec*)::new uint8[ alignTo8( sizeof( MemBlockSpec ) ) + alignTo8( n ) ];
        mb->signature = 314159265;
        mb->next = specList;
        specList = mb;

        ptr = (uint8*)mb + alignTo8( sizeof( MemBlockSpec ) );
        }

    memset( ptr, 0, n );

    return ptr;
    }


void MemBlock::strStk_Reset()
{
    // free all elements
    //
    G.stk.lastUsed = NULL;
    G.stk.totalByteLen = 0;
    G.stk.unusedBits = 0;
    }

void MemBlock::strStk_Push( uint8 *str, size_t strLen)
{
    StrStack::Element* e = G.stk.lastUsed;

    // add at the end
    //
    if ( G.stk.first == NULL )
    {
        e = ::new(this) StrStack::Element;
        e->next = NULL;
        G.stk.first = e;
        G.stk.lastUsed = e;
        }
    else if ( G.stk.lastUsed->next == NULL )
    {
        e = ::new(this) StrStack::Element;
        G.stk.lastUsed->next = e;
        G.stk.lastUsed = e;
        }
    else
    {
        e = e->next;
        G.stk.lastUsed = e;
        }

    e->str = str;
    e->len = strLen;

    G.stk.totalByteLen += strLen;
    }

//
// copy string pieces (buffer refs) into single block.
// assumes that the buf is at least totalByteLen byte long.
//
void MemBlock::strStk_CopyOut (uint8 *buf)
{
    if ( G.stk.lastUsed == NULL )
        return;

    uint8* bufCurr = buf;
    for ( StrStack::Element* e = G.stk.first; e; e = e->next )
    {
        memcpy( bufCurr, e->str, e->len);
        bufCurr += e->len;
        if ( e == G.stk.lastUsed )
            break;
        }
    }

