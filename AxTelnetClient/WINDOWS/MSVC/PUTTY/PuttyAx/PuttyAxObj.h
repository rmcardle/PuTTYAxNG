// PuttyAxObj.h : Declaration of the CPuttyAxObj

#ifndef __PUTTYAXOBJ_H_
#define __PUTTYAXOBJ_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "PuttyAxCP.h"

#include "CCritSec.h"
#include "Helpers.h"

/////////////////////////////////////////////////////////////////////////////

extern "C" int WINAPI PuttyAx_WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmdline, int show, HWND hwndAx, VOID* pvWndData);
extern "C" void cleanup_exit(int code);

typedef struct _SMemRegionInfo
{
	_SMemRegionInfo( CHAR* _pszName, VOID* _pvMem, INT _iMemSize ) : pszName ( _pszName ), pvMem ( _pvMem ), iMemSize ( _iMemSize )
	{
	}

	CHAR*			pszName;
	VOID*			pvMem;
	INT				iMemSize;

} SMemRegionInfo;

/////////////////////////////////////////////////////////////////////////////
// CPuttyAxObj
class ATL_NO_VTABLE CPuttyAxObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IPuttyAxObj, &IID_IPuttyAxObj, &LIBID_PUTTYAXLib>,
	public CComControl<CPuttyAxObj>,
	public IPersistStreamInitImpl<CPuttyAxObj>,
	public IOleControlImpl<CPuttyAxObj>,
	public IOleObjectImpl<CPuttyAxObj>,
	public IOleInPlaceActiveObjectImpl<CPuttyAxObj>,
	public IViewObjectExImpl<CPuttyAxObj>,
	public IOleInPlaceObjectWindowlessImpl<CPuttyAxObj>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CPuttyAxObj>,
	public IPersistStorageImpl<CPuttyAxObj>,
	public ISpecifyPropertyPagesImpl<CPuttyAxObj>,
	public IQuickActivateImpl<CPuttyAxObj>,
	public IDataObjectImpl<CPuttyAxObj>,
	public IProvideClassInfo2Impl<&CLSID_PuttyAxObj, &DIID__IPuttyAxObjEvents, &LIBID_PUTTYAXLib>,
	public IPropertyNotifySinkCP<CPuttyAxObj>,
	public CComCoClass<CPuttyAxObj, &CLSID_PuttyAxObj>,
	public CProxy_IPuttyAxObjEvents< CPuttyAxObj >
{
public:
	CPuttyAxObj() : m_bConnectedEvFired( FALSE ), m_bDoPuttyCleanUp( FALSE )
	{
		m_bWindowOnly = TRUE;

		// attach the hook fn.
		m_hHook = ::SetWindowsHookEx( WH_KEYBOARD, & fnHookKeyboard, NULL, ::GetCurrentThreadId() );
	}

	virtual ~ CPuttyAxObj()
	{
		// free the hook.
		if ( m_hHook )
			::UnhookWindowsHookEx( m_hHook );

		// putty clean up.

		if ( m_bDoPuttyCleanUp )
		{
			PVOID			pv = EnterPutty ();
				cleanup_exit( 0 );
			LeavePutty( pv );
		}

		// free mem.

		{
			CCriticalSection::scope			__access__( m_csGetPointerAccess );

			for( int i=0; i<m_vsMemRegionInfo.size (); i ++ )
				::free( m_vsMemRegionInfo[ i ].pvMem );

			m_vsMemRegionInfo.clear ();
		}
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PUTTYAXOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPuttyAxObj)
	COM_INTERFACE_ENTRY(IPuttyAxObj)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CPuttyAxObj)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CPuttyAxObj)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IPuttyAxObjEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CPuttyAxObj)
	CHAIN_MSG_MAP(CComControl<CPuttyAxObj>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER( WM_SETFOCUS, OnRelayMessageHandler )
	MESSAGE_HANDLER( WM_KILLFOCUS, OnRelayMessageHandler )
	MESSAGE_HANDLER( WM_KEYDOWN, OnRelayMessageHandler )
	MESSAGE_HANDLER( WM_KEYUP, OnRelayMessageHandler )
	MESSAGE_HANDLER( WM_SYSKEYDOWN, OnRelayMessageHandler )
	MESSAGE_HANDLER( WM_SYSKEYUP, OnRelayMessageHandler )
	MESSAGE_HANDLER( WM_DESTROY, OnDestroy )
	MESSAGE_HANDLER( WM_PARENTNOTIFY, OnParentNotify )
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IPuttyAxObj,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::ATL::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IPuttyAxObj
public:
	STDMETHOD(get_IsInitialized)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(ExecuteCommand)(/*[in]*/ BSTR cmdText, /*[out, retval]*/ BSTR *pRetVal);
	STDMETHOD(get_Server)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Server)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Connected)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(Disconnect)();
	STDMETHOD(Connect)();

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		// draw a box and return.

		RECT& rc = *(RECT*)di.prcBounds;

		::SelectObject( di.hdcDraw, ::GetStockObject( BLACK_BRUSH ) );
		::SelectObject( di.hdcDraw, ::GetStockObject( BLACK_PEN ) );

		::Rectangle( di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom );

		return S_OK;
	}

public:

	//
	// Putty compatibility data.
	//

	CCriticalSection					m_csGetPointerAccess;
	std::vector< SMemRegionInfo >		m_vsMemRegionInfo; // acquire m_csGetPointerAccess before accessing.

	VOID SetPuttyErrStr( charstring& cs );

protected:

	//
	// data.
	//

	charstring			m_csCmdLine;
	BOOL				m_bConnectedEvFired;
	charstring			m_csServer;
	BOOL				m_bDoPuttyCleanUp;
	charstring			m_csPuttyErrStr;

	HHOOK				m_hHook;

	//
	// implementation.
	//

	LRESULT OnRelayMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnParentNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	static HWND GetChildWnd( HWND parent );
	HWND GetPuttyWnd ();

	PVOID EnterPutty ();
	VOID LeavePutty ( PVOID pv );

	static LRESULT CALLBACK fnHookKeyboard( int code, WPARAM wParam, LPARAM lParam );
	static BOOL IsPuttyWnd( HWND hwnd );

	BOOL CanEnter ();
};

#endif //__PUTTYAXOBJ_H_
