# Microsoft Developer Studio Project File - Name="CSTALib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CSTALib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CSTALib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CSTALib.mak" CFG="CSTALib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CSTALib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CSTALib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CSTALib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\ASN1 Lib" /I "..\CTsvcLIB" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /Zm500 /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CSTALib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\ASN1 Lib" /I "..\CTsvcLIB" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /Zm500 /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "CSTALib - Win32 Release"
# Name "CSTALib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CallbackQueue.Cpp
# End Source File
# Begin Source File

SOURCE=".\CSTA-Any.Cpp"
# End Source File
# Begin Source File

SOURCE=.\CSTA.Cpp
# End Source File
# Begin Source File

SOURCE=.\CSTAConn.Cpp
# End Source File
# Begin Source File

SOURCE=.\CSTAConnOnRecv.Cpp
# End Source File
# Begin Source File

SOURCE=.\CSTAConnServices.Cpp
# End Source File
# Begin Source File

SOURCE=.\Datatypes.Cpp
# End Source File
# Begin Source File

SOURCE=.\Device.Cpp
# End Source File
# Begin Source File

SOURCE=.\System.Cpp
# End Source File
# Begin Source File

SOURCE=.\VerboseEnums.Cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\CSTA-Any.h"
# End Source File
# Begin Source File

SOURCE=".\CSTA-EnumTypes.h"
# End Source File
# Begin Source File

SOURCE=".\CSTA-Eric.h"
# End Source File
# Begin Source File

SOURCE=".\CSTA-Lib.h"
# End Source File
# Begin Source File

SOURCE=".\CSTA-Lib2.h"
# End Source File
# Begin Source File

SOURCE=.\CSTA.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CSTA.asn1
# End Source File
# End Target
# End Project
