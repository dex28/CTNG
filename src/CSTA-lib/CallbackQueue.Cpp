/*
    Project: CSTALib

    Module: CallbackQueue.Cpp

    Description: CallbackQueue class implementation

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "CSTA-Lib.h"

#include <process.h> // _beginthreadex()

using namespace CTsvcLIB;

/////////////////////////////////////////////////////////////////////////////
namespace MidCSTA
{

///////////////////////////////////////////////////////////////////////////////
// CallbackQueue

CallbackQueue:: CallbackQueue( long size )
    : cbProc( NULL )
    , isTerminating( false )
    , dispatcherCount( 0 )
    , MQue( NULL )
    , maxQueueLen( size )
    , queueLen( 0 )
    , putPtr( 0 )
    , getPtr( 0 )
{
    TRACE( this << " CallbackQueue::CallbackQueue" );

    MQue = new Msg[ maxQueueLen ];

    if ( ! semaFull.Create( 0, maxQueueLen ) )
        TRASSERT( false );

    if ( ! semaEmpty.Create( maxQueueLen, maxQueueLen ) )
        TRASSERT( false );

    unsigned int threadId;
    HANDLE hT = (HANDLE) _beginthreadex( NULL, 0, 
        Dispatcher_Thread, this, NULL, &threadId );

    ::CloseHandle( hT );
    ::Sleep( 0 ); // yield CPU
    }

CallbackQueue:: ~CallbackQueue ()
{
    TRACE( this << " CallbackQueue::~CallbackQueue" );

    // Wait all messages to be dispatched
    //

    while( ::InterlockedExchangeAdd( &queueLen, 0 ) > 0 )
    {
        ::Sleep( 10 ); // Give chance to thread to exit
        }

    isTerminating = true;

    // Signal and wait all CBQ dispatchers threads to exit.
    //
    while( ::InterlockedExchangeAdd( &dispatcherCount, 0 ) > 0 )
    {
        Put( NULL );
        ::Sleep( 10 ); // Give chance to thread to exit
        }

    delete [] MQue;
    }

void CallbackQueue:: Put
(
    CallbackInfo* info,
    DWORD dwTimeout
    )
{
    if ( ! semaEmpty.Wait( dwTimeout ) )
        return;

    ::InterlockedIncrement( &queueLen );

    if ( info )
        info->AddRef ();

    TRACE( this << " CallbackQueue::Put: info " << info );

    mutex.Lock ();

    MQue[ putPtr ].info = info;

    if ( ++putPtr >= maxQueueLen )
        putPtr = 0;

    semaFull.Release( 1 );

    mutex.Unlock ();
    }

bool CallbackQueue:: Get
(
    CallbackInfo*& info,
    DWORD dwTimeout
    )
{
    if ( ! semaFull.Wait( dwTimeout ) )
        return false;

    mutex.Lock ();

    info = MQue[ getPtr ].info;

    if ( ++getPtr >= maxQueueLen )
        getPtr = 0;

    semaEmpty.Release( 1 );

    mutex.Unlock ();

    TRACE( this << " CallbackQueue::Get: info " << info );

    return true;
    }

//  Function:   CallbackQueue:: Dispacther_Thread
//
//  Synopsis:   
//      This is the main worker routine for the Callback dispatcher threads.
//      CB dispatcher threads are serving CB queue by dispatching callback
//      messages to appropriate callback procedure parametrized with callback
//      info.
//
//  Arguments:  
//      workContext - 'this' pointer to the CallbackQueue object
//
//  Return value:
//      DWORD - status of the thread.
//
unsigned int __stdcall 
CallbackQueue:: Dispatcher_Thread
(
    void* thisCBQ
    )
{
    CallbackQueue* queue = (CallbackQueue*)thisCBQ;

    ::InterlockedIncrement( &queue->dispatcherCount );

    TRACE( queue << " CallBackQueue::Dispatcher_Thread: BEGIN" );

    // NOTE: In Non-MTA model CoInitializeEx needed here, 
    // if we need to fire ATL events.

    DWORD threadRC = 1;

    try
    {
        // Loop servicing Callback requests
        //
        while ( ! queue->isTerminating )
        {
            // Get a Callback dispatch request.
            CallbackInfo* info = NULL;
            queue->Get( info );

            if ( info == NULL )
                continue; // check if we've been killed.

            queue->procMutex.Lock ();
            CallbackProcedure* proc = queue->cbProc;
            if ( proc )
            {
                TRACE( queue << " CallbackQueue::Dispatcher_Thread: Begin Call proc " << proc << ", info " << info );

                // Dispatch Callback; catch & report all exceptions
                //
                try
                {
                    proc->Procedure( info );
                    }
                catch ( ... )
                {
                    LOG( DBG_ERROR ) << queue 
                        << " CallbackQueue:: Dispatcher_Thread: "
                            "MISHAP: Catched exception while dispatching CBI to Procedure"
                        << eline;
                    }

                TRACE( queue << " CallbackQueue::Dispatcher_Thread: End Call proc " << proc << ", info " << info );
                }
            queue->procMutex.Unlock ();

            // Remove references to proc and info objects
            info->RemoveRef ();

            // message has been dispatched
            ::InterlockedDecrement( &queue->queueLen );

            // Loop around to get another CB request.
            }

        threadRC = 0;
        }
    catch( ... )
    {
        LOG( DBG_ERROR ) << queue 
            << " CallBackQueue::Dispatcher_Thread: SEVERE exception catched." 
            << eline;
        threadRC = 1;
        }

    TRACE( queue << " CallBackQueue::Dispatcher_Thread: END" );

    ::InterlockedDecrement( &queue->dispatcherCount );

    return threadRC; // 0 means OK
    }

/////////////////////////////////////////////////////////////////////////////
} // namespace MidCSTA