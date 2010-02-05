
PuttyAxps.dll: dlldata.obj PuttyAx_p.obj PuttyAx_i.obj
	link /dll /out:PuttyAxps.dll /def:PuttyAxps.def /entry:DllMain dlldata.obj PuttyAx_p.obj PuttyAx_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del PuttyAxps.dll
	@del PuttyAxps.lib
	@del PuttyAxps.exp
	@del dlldata.obj
	@del PuttyAx_p.obj
	@del PuttyAx_i.obj
