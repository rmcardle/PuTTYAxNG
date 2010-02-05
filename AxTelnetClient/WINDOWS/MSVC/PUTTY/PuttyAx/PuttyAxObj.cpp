// PuttyAxObj.cpp : Implementation of CPuttyAxObj

#include "stdafx.h"
#include "PuttyAx.h"
#include "PuttyAxObj.h"

#include <shlobj.h>

/////////////////////////////////////////////////////////////////////////////

class CTlsAllocator
{
public:

	CTlsAllocator ()
	{
		tls = ::TlsAlloc ();
		if ( tls == TLS_OUT_OF_INDEXES )
			throw;
	}

	virtual ~ CTlsAllocator ()
	{
		::TlsFree( tls );
	}

	DWORD			tls;
};

CTlsAllocator	g_Tls;

//////////////////////////////////////////////////////////////////////////////////////////////////

static VOID* ReturnIfAllocated_NOLOCK( CHAR* name, INT size )
{
	// already allocated ?

	std::vector< SMemRegionInfo >*		pvec = & ( (CPuttyAxObj*) ::TlsGetValue( g_Tls.tls ) )->m_vsMemRegionInfo;

	for( unsigned int i=0; i<pvec->size (); i ++ )
	{
		SMemRegionInfo*		p = & (*pvec)[ i ];
		if ( ::strcmp( p->pszName, name ) == 0 )
		{
			if ( p->iMemSize != size )
				throw;
			else
				return p->pvMem;
		}
	}

	return NULL;
}

static VOID* ForceAllocate_NOLOCK( CHAR* name, INT size )
{
	// allocate.

	std::vector< SMemRegionInfo >*		pvec = & ( (CPuttyAxObj*) ::TlsGetValue( g_Tls.tls ) )->m_vsMemRegionInfo;

	VOID*			mem = ::malloc( size );
	if ( mem == NULL )
		return NULL;

	::memset( mem, 0, size );

	pvec->push_back( SMemRegionInfo( name, mem, size ) );
	return mem;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" VOID* AX_GET_POINTER( CHAR* name, INT size )
{
	CCriticalSection::scope			__access__( ( (CPuttyAxObj*) ::TlsGetValue( g_Tls.tls ) )->m_csGetPointerAccess );

	// already allocated ?

	VOID*		pvExist = ::ReturnIfAllocated_NOLOCK( name, size );
	if ( pvExist )
		return pvExist;

	// allocate.

	return ::ForceAllocate_NOLOCK( name, size );
}

extern "C" VOID* AX_GET_POINTER_INT( CHAR* name, INT size, INT init )
{
	CCriticalSection::scope			__access__( ( (CPuttyAxObj*) ::TlsGetValue( g_Tls.tls ) )->m_csGetPointerAccess );

	if ( size != sizeof( INT ) )
		throw;

	VOID*		pvExist = ::ReturnIfAllocated_NOLOCK( name, size );
	if ( pvExist )
		return pvExist;

	INT* p = (INT*) ::ForceAllocate_NOLOCK( name, size );
	* p = init;
	return p;
}

extern "C" VOID* AX_GET_POINTER_UINT( CHAR* name, INT size, UINT init )
{
	CCriticalSection::scope			__access__( ( (CPuttyAxObj*) ::TlsGetValue( g_Tls.tls ) )->m_csGetPointerAccess );

	if ( size != sizeof( UINT ) )
		throw;

	VOID*		pvExist = ::ReturnIfAllocated_NOLOCK( name, size );
	if ( pvExist )
		return pvExist;

	UINT* p = (UINT*) ::ForceAllocate_NOLOCK( name, size );
	* p = init;
	return p;
}

/////////////////////////////////////////////////////////////////////////////

extern "C" LRESULT CALLBACK WndProc_Putty(HWND, UINT, WPARAM, LPARAM);

extern "C" LRESULT CALLBACK WndProc_Ax(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	CPuttyAxObj*		pAx = (CPuttyAxObj*) ::GetWindowLong( hwnd, GWL_USERDATA );

	PVOID				pvTlsOld = NULL;

	if ( pAx )
	{
		pvTlsOld = ::TlsGetValue( g_Tls.tls );
		::TlsSetValue( g_Tls.tls, pAx );
	}

		LRESULT lr = ::WndProc_Putty(hwnd, msg, wparam, lparam);

	if ( pAx )
	{
		::TlsSetValue( g_Tls.tls, pvTlsOld );
	}

	return lr;
}

extern "C" char *dupvprintf(const char *fmt, va_list ap);
extern "C" const char *const appname;
#define sfree safefree
extern "C" void safefree(void *);

extern "C" void connection_fatal(void *frontend, char *fmt, ...)
{
    va_list ap;
    char *stuff, morestuff[100];

    va_start(ap, fmt);
    stuff = dupvprintf(fmt, ap);
    va_end(ap);
    sprintf(morestuff, "%.70s Fatal Error", appname);

    //MessageBox(hwnd_, stuff, morestuff, MB_ICONERROR | MB_OK);
	( (CPuttyAxObj*) ::TlsGetValue( g_Tls.tls ) )->SetPuttyErrStr( charstring( morestuff ) + ": " + stuff );

    sfree(stuff);

/*
    if (cfg.close_on_exit == FORCE_ON)
	PostQuitMessage(1);
    else {
	close_session();
    }
*/
}

extern "C" void fatalbox(char *fmt, ...)
{
    va_list ap;
    char *stuff, morestuff[100];

    va_start(ap, fmt);
    stuff = dupvprintf(fmt, ap);
    va_end(ap);
    sprintf(morestuff, "%.70s Fatal Error", appname);

    //MessageBox(hwnd_, stuff, morestuff, MB_ICONERROR | MB_OK);
	( (CPuttyAxObj*) ::TlsGetValue( g_Tls.tls ) )->SetPuttyErrStr( charstring( morestuff ) + ": " + stuff );

    sfree(stuff);

/*
    cleanup_exit(1);
*/
}

extern "C" void modalfatalbox(char *fmt, ...)
{
    va_list ap;
    char *stuff, morestuff[100];

    va_start(ap, fmt);
    stuff = dupvprintf(fmt, ap);
    va_end(ap);
    sprintf(morestuff, "%.70s Fatal Error", appname);

    //MessageBox(hwnd_, stuff, morestuff,
	//       MB_SYSTEMMODAL | MB_ICONERROR | MB_OK);
	( (CPuttyAxObj*) ::TlsGetValue( g_Tls.tls ) )->SetPuttyErrStr( charstring( morestuff ) + ": " + stuff );

    sfree(stuff);

/*
    cleanup_exit(1);
*/
}

/////////////////////////////////////////////////////////////////////////////
// CPuttyAxObj

PVOID CPuttyAxObj::EnterPutty ()
{
	PVOID		pv = ::TlsGetValue( g_Tls.tls );
	::TlsSetValue( g_Tls.tls, this );
	return pv;
}

VOID CPuttyAxObj::LeavePutty ( PVOID pv )
{
	::TlsSetValue( g_Tls.tls, pv );
	return;
}

STDMETHODIMP CPuttyAxObj::Connect()
{
	//
	// can enter ???
	//

	if ( CanEnter () == FALSE )
		return E_FAIL;

	// validate.

	if ( m_csServer.size () == 0 )
		return AtlReportError( GetObjectCLSID (), "Server name not specified.", GUID_NULL, 0 );

	if ( m_csServer[ 0 ] == '-' || m_csServer[ 0 ] == '\\' || m_csServer[ 0 ] == '/' ||
		m_csServer.find( ' ' ) != charstring::npos )
	{
		return AtlReportError( GetObjectCLSID (), "Invalid server name specified.", GUID_NULL, 0 );
	}

	// set the command line str.

	m_csCmdLine = "-telnet " + m_csServer;

	//
	// call the original Putty init fn.
	//

	PVOID			pv = EnterPutty ();
		PuttyAx_WinMain(_Module.m_hInst, NULL, const_cast< CHAR* >( m_csCmdLine.c_str () ), SW_SHOW, m_hWnd, this);
	LeavePutty ( pv );

	// was the window created ?

	if ( GetPuttyWnd() )
	{
		// fire the connected ev...
		m_bConnectedEvFired = TRUE;
		Fire_OnConnected ();
	}
	else
	{
		return AtlReportError( GetObjectCLSID (), "Connect error.", GUID_NULL, 0 );
	}

	// return.

	return S_OK;
}

STDMETHODIMP CPuttyAxObj::Disconnect()
{
	//
	// can enter ???
	//

	if ( CanEnter () == FALSE )
		return E_FAIL;

	// disconnect.
	HWND		h = GetPuttyWnd();
	if ( h == NULL )
		return AtlReportError( GetObjectCLSID (), "You are not connected to any server.", GUID_NULL, 0 );
	else
		::SendMessage( h, WM_CLOSE, 0, 0 );

	// return.
	return S_OK;
}

STDMETHODIMP CPuttyAxObj::get_Connected(BOOL *pVal)
{
	//
	// can enter ???
	//

	if ( CanEnter () == FALSE )
		return E_FAIL;

	// return whether we are connected or not...
	* pVal = GetPuttyWnd () != NULL && m_bConnectedEvFired;
	return S_OK;
}

STDMETHODIMP CPuttyAxObj::get_Server(BSTR *pVal)
{
	//
	// can enter ???
	//

	if ( CanEnter () == FALSE )
		return E_FAIL;

	// return the information.
	* pVal = ::SysAllocString( ::CharStringToWideString( m_csServer ).c_str() );
	return S_OK;
}

STDMETHODIMP CPuttyAxObj::put_Server(BSTR newVal)
{
	//
	// can enter ???
	//

	if ( CanEnter () == FALSE )
		return E_FAIL;

	// store the server name...

	charstring		cs = ::BstrToCharstring( newVal );
	::TrimAtBothSides( cs );
	m_csServer = cs;

	return S_OK;
}

#define IDM_COPYALL   0x0170
#define IDM_PASTE     0x0190
#define IDM_ABOUT     0x0150

STDMETHODIMP CPuttyAxObj::ExecuteCommand(BSTR cmdText, BSTR *pRetVal)
{
	//
	// can enter ???
	//

	if ( CanEnter () == FALSE )
		return E_FAIL;

	// parse input params.

	charstring			csCmdText = ::BstrToCharstring( cmdText );
	charstring			csRetVal = "Command ok.";

	BOOL				bIsErr = FALSE;

	// which command ?

	HWND hwndPutty = GetPuttyWnd ();

	if ( hwndPutty )
	{
		::TrimAtBothSides( csCmdText );

		if ( ::stricmp( csCmdText.c_str (), "copyalltoclipboard" ) == 0 )
			::SendMessage( hwndPutty, WM_COMMAND, IDM_COPYALL, 0 );
		else if ( ::stricmp( csCmdText.c_str (), "paste" ) == 0 )
			::SendMessage( hwndPutty, WM_COMMAND, IDM_PASTE, 0 );
		else if ( ::stricmp( csCmdText.c_str (), "about" ) == 0 )
			::SendMessage( hwndPutty, WM_COMMAND, IDM_ABOUT, 0 );
	}
	else
	{
		// return an error.
		csRetVal = "Client not connected.";
		bIsErr = TRUE;
	}

	//
	// return.
	//

	if ( bIsErr )
	{
		// return failure.
		return AtlReportError( GetObjectCLSID (), csRetVal.c_str (), GUID_NULL, 0 );
	}
	else
	{
		// return success.
		* pRetVal = ::SysAllocString( ::CharStringToWideString( csRetVal ).c_str() );
		return S_OK;
	}
}

STDMETHODIMP CPuttyAxObj::get_IsInitialized(BOOL *pVal)
{
	//
	// can enter ???
	//

	if ( CanEnter () == FALSE )
		return E_FAIL;

	// return whether we are initialized...
	* pVal = m_hWnd != NULL;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////

static BOOL CALLBACK fnEnum ( HWND hwnd, LPARAM lParam )
{
	// return the first child...
	* (HWND*) lParam = hwnd;
	return FALSE;
}

HWND CPuttyAxObj::GetChildWnd( HWND parent )
{
	// enum the child windows.
	HWND hwnd = NULL;
	::EnumChildWindows( parent, & fnEnum, (LPARAM) & hwnd );
	return hwnd;
}

HWND CPuttyAxObj::GetPuttyWnd ()
{
	// call the implementation.
	return GetChildWnd( m_hWnd );
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CPuttyAxObj::OnRelayMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// we have to relay the msg ?

	HWND hwndPutty = GetPuttyWnd ();

	if ( hwndPutty )
	{
		::SendMessage( hwndPutty, uMsg, wParam, lParam );
		bHandled = TRUE;
	}

	// return.
	return 0;
}

LRESULT CPuttyAxObj::OnDestroy (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// we have to call the WM_CLOSE handler of the Putty app window ?

	HWND hwndPutty = GetPuttyWnd ();

	if ( hwndPutty )
		::SendMessage( hwndPutty, WM_CLOSE, 0, 0 );

	// return.
	return 0;
}

LRESULT CPuttyAxObj::OnParentNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// which event ?
	if ( LOWORD( wParam ) == WM_DESTROY && lParam != 0 )
	{
		// we have to fire the corresponding ev ?
		if ( m_bConnectedEvFired )
		{
			m_bConnectedEvFired = FALSE;

			// clean up Putty...
			m_bDoPuttyCleanUp = TRUE;

			// fire ev.
			Fire_OnDisconnected( CComBSTR( m_csPuttyErrStr.size () ? m_csPuttyErrStr.c_str () : "Connection ended." ) );
		}
	}

	// return.
	return 0;
}

VOID CPuttyAxObj::SetPuttyErrStr( charstring& cs )
{
	HWND hwndPutty = GetPuttyWnd ();

	if ( hwndPutty )
	{
		m_csPuttyErrStr = cs;
		::SendMessage( hwndPutty, WM_CLOSE, 0, 0 );
	}
}

/////////////////////////////////////////////////////////////////////////////

static WPARAM s_wpVirtualKeysToIntercept[] =
{
	VK_CANCEL,
	VK_BACK, VK_TAB,
	VK_CLEAR, VK_RETURN,
	VK_SHIFT, VK_CONTROL, VK_MENU, VK_PAUSE, VK_CAPITAL,
	VK_ESCAPE,
	VK_SPACE, VK_PRIOR, VK_NEXT, VK_END, VK_HOME, VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN, VK_SELECT, VK_PRINT, VK_EXECUTE, VK_SNAPSHOT, VK_INSERT, VK_DELETE, VK_HELP,
	VK_LWIN, VK_RWIN, VK_APPS,
	VK_NUMLOCK, VK_SCROLL
};

static BOOL VkHasToIntercept( WPARAM wp )
{
	// check in the vector...
	for( int i=0; i<sizeof(s_wpVirtualKeysToIntercept)/sizeof(WPARAM); i ++ )
		if ( s_wpVirtualKeysToIntercept[ i ] == wp )
			return TRUE;

	// return failure...
	return FALSE;
}

BOOL CPuttyAxObj::IsPuttyWnd( HWND hwnd )
{
	if ( hwnd == NULL )
		return FALSE;

	// get and check the class name...
	CHAR		szClassName[ MAX_PATH ] = "";
	::GetClassName( hwnd, szClassName, sizeof( szClassName ) );
	if ( ::strcmp( szClassName, "PuTTY" ) == 0 )
	{
		// return a non-zero value.
		return TRUE;
	}

	// return failure.
	return FALSE;
}

LRESULT CALLBACK CPuttyAxObj::fnHookKeyboard( int code, WPARAM wParam, LPARAM lParam )
{
	// process.
	if ( code < 0 )
		return ::CallNextHookEx( NULL, code, wParam, lParam );
	else if ( code == HC_ACTION )
	{
		// which key ?
		if ( ( lParam & (1<<29) ) || ::VkHasToIntercept( wParam ) )
		{
			// which window ?
			HWND		hwnd = ::GetFocus ();
			if ( hwnd )
			{
				HWND		child = GetChildWnd( hwnd );

				BOOL		resParent = IsPuttyWnd( hwnd );
				BOOL		resChild = IsPuttyWnd( child );
				if ( resParent || resChild )
				{
					// process the message...
					HWND		hwndTarget = resParent ? hwnd : child;
					::SendMessage( hwndTarget, WM_KEYDOWN, wParam, lParam );

					// return a nonzero value.
					return 1;
				}
			}
		}
	}

	// return.
	return ::CallNextHookEx( NULL, code, wParam, lParam );
}

/////////////////////////////////////////////////////////////////////////////

BOOL CPuttyAxObj::CanEnter ()
{
	return TRUE;

	// check out the URL of the calling page...

	HRESULT				hr;

	CComPtr<IServiceProvider>			pISP;
	hr = m_spClientSite->QueryInterface( IID_IServiceProvider, (void**) & pISP );

	if ( FAILED( hr ) || pISP == NULL )
		return FALSE;

	CComPtr<IWebBrowserApp>				pIWebBrowserApp;
	hr = pISP->QueryService( SID_SWebBrowserApp, IID_IWebBrowserApp, (void**) & pIWebBrowserApp );

	if ( FAILED( hr ) || pIWebBrowserApp == NULL )
		return FALSE;

	BSTR			bstrUrl;
	hr = pIWebBrowserApp->get_LocationURL( & bstrUrl );

	if ( FAILED( hr ) )
		return FALSE;

	charstring		csUrl = ::BstrToCharstring( bstrUrl );
	::SysFreeString( bstrUrl );

#ifndef _DEBUG

	CHAR*				psz = "https://www.gototerminal.com/";

	if ( csUrl.size () < ::strlen( psz ) ||
		::memicmp( csUrl.c_str (), psz, ::strlen( psz ) ) )
	{
		::MessageBox( NULL, "This Active-X object can be used only from https://www.GoToTerminal.com.\n\nPlease navigate to this address and try again...", "GoToTerminal", MB_OK );
		return FALSE;
	}

#endif

	// return success.

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
