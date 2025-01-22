// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "VCClient.h"
#include "DlgProxy.h"
#include "VCClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVCClientDlgAutoProxy

IMPLEMENT_DYNCREATE(CVCClientDlgAutoProxy, CCmdTarget)

CVCClientDlgAutoProxy::CVCClientDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CVCClientDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CVCClientDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CVCClientDlgAutoProxy::~CVCClientDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CVCClientDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CVCClientDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CVCClientDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVCClientDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CVCClientDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IVCClient to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A133626C-47D9-4EC8-8185-C7809AC3B6CF}
static const IID IID_IVCClient =
{ 0xa133626c, 0x47d9, 0x4ec8, { 0x81, 0x85, 0xc7, 0x80, 0x9a, 0xc3, 0xb6, 0xcf } };

BEGIN_INTERFACE_MAP(CVCClientDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CVCClientDlgAutoProxy, IID_IVCClient, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {7DED7EB1-4D40-41CF-99BE-A1BA59B47E7A}
IMPLEMENT_OLECREATE2(CVCClientDlgAutoProxy, "VCClient.Application", 0x7ded7eb1, 0x4d40, 0x41cf, 0x99, 0xbe, 0xa1, 0xba, 0x59, 0xb4, 0x7e, 0x7a)

/////////////////////////////////////////////////////////////////////////////
// CVCClientDlgAutoProxy message handlers
