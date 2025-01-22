// VCClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VCClient.h"
#include "VCClientDlg.h"
#include <initguid.h>
#include "VCClient_i.c"
#include "ClientClass.h"
#include "WPCommLoginDlg.h"
#include "DlgPointControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVCClientApp

BEGIN_MESSAGE_MAP(CVCClientApp, CWinApp)
	//{{AFX_MSG_MAP(CVCClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCClientApp construction

CVCClientApp::CVCClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVCClientApp object

CVCClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVCClientApp initialization

BOOL CVCClientApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	if (!InitATL())
		return FALSE;

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	//Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();
	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);

	}
	else
	{
		// When a server application is launched stand-alone, it is a good idea
		//  to update the system registry in case it has been damaged.
		COleObjectFactory::UpdateRegistryAll();
	}

	CVCClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

	
CVCClientModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
//OBJECT_ENTRY(CLSID_ClientClass, CClientClass)
OBJECT_ENTRY_NON_CREATEABLE(CClientClass)
END_OBJECT_MAP()

LONG CVCClientModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CVCClientModule::Lock()
{
	AfxOleLockApp();
	return 1;
}


int CVCClientApp::ExitInstance()
{
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	}

	return CWinApp::ExitInstance();

}

BOOL CVCClientApp::InitATL()
{
	m_bATLInited = TRUE;

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	return TRUE;

}
