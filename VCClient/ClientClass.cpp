// ClientClass.cpp : Implementation of CVCClientApp and DLL registration.

#include "stdafx.h"
#include "VCClient.h"
#include "ClientClass.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CClientClass::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IClientClass,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
