// ClientClass.h: Definition of the CClientClass class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTCLASS_H__BE1F38DC_8555_4816_B4A3_0D99962633B3__INCLUDED_)
#define AFX_CLIENTCLASS_H__BE1F38DC_8555_4816_B4A3_0D99962633B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientClass

class CClientClass : 
	public IDispatchImpl<IClientClass, &IID_IClientClass, &LIBID_VCClient>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CClientClass,&CLSID_ClientClass>,
	//public IDispatchImpl<IWPAVCallBack, &IID_IWPAVCallBack, &LIBID_Accw>
	public IDispEventImpl<1, CClientClass, 
&IID_IWPAVCallBack, &LIBID_Accw, 1, 0> //Implement the IWPAVCallBack interface to support events from Winpak CommServer API
{
public:
CStringList m_szListInput;  // List of messages from Winpak CommServer API

public:
	CClientClass() {}
	~CClientClass() { m_szListInput.RemoveAll();}

BEGIN_COM_MAP(CClientClass)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IClientClass)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY2(IDispatch, IClientClass)
//	COM_INTERFACE_ENTRY(IWPAVCallBack)
	COM_INTERFACE_ENTRY_IID(IID_IWPAVCallBack, IDispatch)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CClientClass) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 


// Add to Event Sink Map : Declaring the handler function of Winpak CommServer API
BEGIN_SINK_MAP(CClientClass)
      SINK_ENTRY_EX(1, IID_IWPAVCallBack, 1, GotMessage)
	  SINK_ENTRY_EX(1, IID_IWPAVCallBack, 2, ServerError)
END_SINK_MAP() 


DECLARE_REGISTRY_RESOURCEID(IDR_ClientClass)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IClientClass

CString GetFieldFromInput(CString szInput,CString szField)
{
	
	int iStartPos = szInput.Find("<" + szField,0);
	if(iStartPos >= 0) 
	{
		int iSize = szField.GetLength();
		int iLastPos = szInput.Find("</" + szField,iStartPos+1);
		
		iSize = iStartPos + 2 + iSize;
		iLastPos = iLastPos -  iSize; 
		return(szInput.Mid(iSize,iLastPos));
	}
	else
		return("");
	
}
// IWPAVCallBack - Implementation
STDMETHOD(GotMessage)(BSTR bstrTranInfo)
{
    AFX_MANAGE_STATE(AfxGetAppModuleState())
	
	/*	CString sInput;
		CString sAcctName="Account1";

		sInput = CString(bstrTranInfo);

		CString sRes = GetFieldFromInput(sInput,"Account");

		if(sRes == sAcctName || sRes.IsEmpty())
		{
			
			m_szListInput.AddHead(CString(bstrTranInfo)); 	
		}*/

		m_szListInput.AddHead(CString(bstrTranInfo)); 

	return E_NOTIMPL;
}

STDMETHOD(ServerError)(BSTR bstrErrorInfo)
{
	AfxMessageBox(CString(bstrErrorInfo));
	return E_NOTIMPL;
}


};

#endif // !defined(AFX_CLIENTCLASS_H__BE1F38DC_8555_4816_B4A3_0D99962633B3__INCLUDED_)
