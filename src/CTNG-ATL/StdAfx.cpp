/*
    Project: CTNG COM ATL

    Module: stdafx.cpp

    Description: source file that includes just the standard includes
        stdafx.pch will be the pre-compiled header
    stdafx.obj will contain the pre-compiled type information

    Copyright (c) 2002 By Mikica B Kocic
    Copyright (c) 2002 By IPTC Technology Communication AB
*/

#include "stdafx.h"

#if _MSC_VER < 1300 // Depricated starting from MS VS.Net

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#include <statreg.cpp>
#endif

#include <atlimpl.cpp>

#endif