
CTNGps.dll: dlldata.obj CTNG_p.obj CTNG_i.obj
	link /dll /out:CTNGps.dll /def:CTNGps.def /entry:DllMain dlldata.obj CTNG_p.obj CTNG_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del CTNGps.dll
	@del CTNGps.lib
	@del CTNGps.exp
	@del dlldata.obj
	@del CTNG_p.obj
	@del CTNG_i.obj
