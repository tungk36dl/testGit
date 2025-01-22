// VCClient.h : main header file for the VCCLIENT application
//

#if !defined(AFX_VCCLIENT_H__D9E1ECB9_C1C4_4EEB_B328_9740383CC7A4__INCLUDED_)
#define AFX_VCCLIENT_H__D9E1ECB9_C1C4_4EEB_B328_9740383CC7A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "VCClient_i.h"

/////////////////////////////////////////////////////////////////////////////
// CVCClientApp:
// See VCClient.cpp for the implementation of this class
//

class CVCClientApp : public CWinApp
{
public:
	CVCClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCClientApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVCClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCCLIENT_H__D9E1ECB9_C1C4_4EEB_B328_9740383CC7A4__INCLUDED_)
