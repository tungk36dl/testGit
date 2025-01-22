// VCClientDlg.cpp : implementation file
/****************************************************************************************************
  						COPYRIGHT @ 2012
						HONEYWELL INC.,
 			    		ALL RIGHTS RESERVED
 
 	This software is a copyrighted work and/or information protected as a trade secret. 
	Legal rights of Honeywell Inc. in this software is distinct from ownership of any medium 
	in which the software is embodied.Copyright or trade secret notices included must be 
	reproduced in any copies authorized by Honeywell Inc. The information in this software 
	is subject to change without notice and should not be considered as a commitment by Honeywell Inc.
/******************************************************************************************************

  File Name     : VCClieentDlg.cpp

  Project		: WP-CS API Test Client

  Originator	: Nagarajan S

  APPLICATION	: WP-CS API Communication server Test Client

  MODULE		: 

  PURPOSE		: 

  REVISION HISTORY:

  Rev	   Date		 Programmer            Comment
  ----    --------	--------------   ---------------------
  1.0	 22 July 2007   Nagarajan S		Initial Version
  2.0	 19 Oct  2007	Nagarajan S		Modified for Event Code formation
  2.1	 20 oct 2009	Nagarajan S		Added panel initilize function for WPPCS web enhancements
  2.5	 02 Nov	 2011	Sathish Guru	WP SEPE API Prototype
  3.0	 23 Nov  2011	Sathish Guru	Merge with CSAC API NetAXS Changes
  3.1	 02 Jan	 2012	Sathish Guru	Prototype Bugfixes
  3.2	 13 Feb  2012	Sathish Guru	Added PRO2200 Input States

/********************************************************************************/

#include "stdafx.h"
#include "VCClient.h"
#include "VCClientDlg.h"
#include "DlgProxy.h"
#include "Protocol.h"
#include "DlgPointControl.h"
#include "DlgADVControl.h"
#include "WPCommLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const int g_nsize = 8;
CString g_SystemAlarmActions[g_nsize] = { _T("Panel Comm Alarm"),_T("Aux Port Alarm"),
_T("Primary Power Alarm"),
_T("Tamper Alarm"),
_T("Ground Fault Alarm"),
_T("Low Voltage Alarm"),
_T("Ext 5 Volt Alarm"),
_T("Poll Response Alarm")};

//CString GetFieldFromInput(CString szInput,CString szField);	//Parses the XML Message
CString GetStatusDescriptionByStatusID(CString szInput);    //Retrieves the status description from status ID

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCClientDlg dialog

IMPLEMENT_DYNAMIC(CVCClientDlg, CDialog);

CVCClientDlg::CVCClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVCClientDlg)
	m_lAlarmHID = 0;
	m_lAlarmPointID = 0;
	m_strNote = _T("");
	m_pAutoProxy = NULL;
	m_iEventItemNo = 0;
	m_iStatusItemNo = 0;
	m_strUser = _T("");
	m_strPswd = _T("");
	m_bLoggedIn = FALSE;

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CVCClientDlg::~CVCClientDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	UnRegister();

	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CVCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVCClientDlg)
	DDX_Control(pDX, IDC_LST_DETAILS, m_LstDetails);
	DDX_Control(pDX, IDC_LIST_ALARM, m_ctlListAlarm);
	DDX_Control(pDX, IDC_LST_STATUS, m_cLstStatus);
	DDX_Control(pDX, IDC_LST_EVENT, m_cLstEvent);
	DDX_Text(pDX, IDC_TXT_ALRM_HID, m_lAlarmHID);
	DDX_Text(pDX, IDC_TXT_ALRM_POINTID, m_lAlarmPointID);
	DDX_Text(pDX, IDC_EDIT_OP_NOTE, m_strNote);
	DDX_Text(pDX, IDC_STATIC_OPERATOR, m_strUser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVCClientDlg, CDialog)
	//{{AFX_MSG_MAP(CVCClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BtnAck, OnBtnAck)
	ON_BN_CLICKED(IDC_BtnClear, OnBtnClear)
	ON_BN_CLICKED(IDC_BTN_STATUS, OnBtnStatus)
	ON_BN_CLICKED(IDC_BTNDETAILS, OnBtndetails)
	ON_COMMAND(ID_OPERATIONS_PANELCONTROL, OnMenuPanelControl)
	ON_COMMAND(ID_OPERATIONS_OTHERADVCONTROLS, OnMenuADVControl)
	ON_COMMAND(ID_HELP_ABOUT, OnMenuAbout)
	ON_COMMAND(ID_FILE_LOGIN, OnMenuLogin)
	ON_COMMAND(ID_FILE_LOGOUT, OnMenuLogout)
	ON_COMMAND(ID_FILE_EXIT, OnMenuExit)
	ON_BN_CLICKED(IDC_BTN_ADD_NOTE, OnBtnAddNote)
	ON_LBN_SELCHANGE(IDC_LIST_ALARM, OnLbnSelchangeListAlarm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVCClientDlg message handlers

BOOL CVCClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ctlListAlarm.SetHorizontalExtent(5000);	
	m_LstDetails.SetHorizontalExtent(10000);
	b_transaction = NULL;
	//Register();
	LoadColumnHeaders();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVCClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVCClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CVCClientDlg::OnClose() 
{
	if(FALSE == m_bLoggedIn)
	{
		CDialog::OnClose();
		return;
	}
	OnMenuLogout();
	ShowWindow(SW_HIDE);
	UnRegister();
	CDialog::OnClose();
}

void CVCClientDlg::OnOK() 
{
	if(FALSE == m_bLoggedIn)
	{
		CDialog::OnCancel();
		return;
	}
	OnMenuLogout();
	ShowWindow(SW_HIDE);
	UnRegister();
	CDialog::OnOK();
}

void CVCClientDlg::OnCancel() 
{
	if(FALSE == m_bLoggedIn)
	{
		CDialog::OnCancel();
		return;
	}
	OnMenuLogout();
	ShowWindow(SW_HIDE);
	UnRegister();
	CDialog::OnCancel();
}

BOOL CVCClientDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		UnRegister();
		return FALSE;
	}

	return TRUE;
}

/*void log_trace( CString str)
{

	CFile file("C:\\Events.txt", CFile::modeWrite);
	str = str + "\r\n";
	file.Write(str , str.GetLength()*2);
	file.Close();
}*/
/*********************************************************************************/
// Description : Thread spying on any message from the Winpak Commserver API
// Parameter   : lpParam - void pointer of the CVCClientDlg class
/*********************************************************************************/

DWORD WINAPI ClientThread(LPVOID lpParam)
{
	CVCClientDlg* pParent = (CVCClientDlg*)lpParam;
	
	while(1)
	{
		if(!  (pParent->m_pCallback->m_szListInput.IsEmpty())  )
		{
			CString szTemp;
			szTemp = pParent->m_pCallback->m_szListInput.RemoveTail();
			
			CString szAckStatus,szIdx,szHID,szPoint,szADVStatus ,szAccount ;

			szIdx		 = pParent->GetFieldFromInput(szTemp, PR_Idx);
			szAckStatus  = pParent->GetFieldFromInput(szTemp, PR_AckStatus);
			szHID		 = pParent->GetFieldFromInput(szTemp, PR_HID);
			szPoint		 = pParent->GetFieldFromInput(szTemp, PR_Point);
			szADVStatus  = pParent->GetFieldFromInput(szTemp, PR_ADVStatus);
			 

			//log_trace(szTemp);
				//AfxMessageBox(szTemp);

			if( ! (szADVStatus.IsEmpty()) )
			{
				//AfxMessageBox(szTemp);	
				pParent->AddToStatusList(szTemp);
			}
				
			else
			{	//If event
				if (! szIdx.Compare(_T("-1")))
					pParent->AddToEventList(szTemp);
				else 
					pParent->m_ctlListAlarm.AddString(szTemp);
			}
		}
		else
		{
				Sleep(1000);
		}
	}

	return 1;
}
/*********************************************************************************/
// Description :This method is called by the client to register itself to the client. 
//				It passes the callback pointer to the API so that API can send 
//				alarm/event/command/status messages to the client 
// Parameters  : -
/*********************************************************************************/
void CVCClientDlg::Register()
{
	::CoInitialize(0);
	
	HRESULT hRes;

	hRes = CComObject<CClientClass>::CreateInstance(&m_pCallback);
	hRes = m_pServer.CreateInstance("accw.MTSCBServer");

	DWORD dwThreadID;
	m_hdlThread  =  CreateThread(0,0,ClientThread,this,0,&dwThreadID);

	::CoUninitialize();
}
/*********************************************************************************/
// Description : This method is the last call made to the Winpak Commserver API to 
//				 unregister itself from the Winpak CommServer API. 
//				 Releases all the resources used.
//Parameters   : -				 
/*********************************************************************************/
void CVCClientDlg::UnRegister()
{
	VARIANT_BOOL pbResult;
	if(m_bLoggedIn)
	{
		m_pServer->DoneServer(m_pCallback,&pbResult);
	}
		
	DWORD dwExitCode = 0;
	TerminateThread(m_hdlThread,dwExitCode);	

	m_pServer = NULL;
	m_pCallback = NULL;
}
/*********************************************************************************/
// Description : Creates column headers to the list.
// Parameters  : -
/*********************************************************************************/
void CVCClientDlg::LoadColumnHeaders()
{
	// Load Column headers to IDC_LST_EVENT
	m_cLstEvent.InsertColumn(0,_T("Idx"),LVCFMT_LEFT,50);
	m_cLstEvent.InsertColumn(1,_T("Prio"),LVCFMT_LEFT,50);
	m_cLstEvent.InsertColumn(2,_T("Date"),LVCFMT_LEFT,80);
	m_cLstEvent.InsertColumn(3,_T("Time"),LVCFMT_LEFT,70);
	m_cLstEvent.InsertColumn(4,_T("Cnt"),LVCFMT_LEFT,50);
	m_cLstEvent.InsertColumn(5,_T("Status"),LVCFMT_LEFT,150);
	m_cLstEvent.InsertColumn(6,_T("EventID"),LVCFMT_LEFT,80);//eventid
	m_cLstEvent.InsertColumn(7,_T("Reader/Point"),LVCFMT_LEFT,150);
	m_cLstEvent.InsertColumn(8,_T("Site"),LVCFMT_LEFT,50);
	m_cLstEvent.InsertColumn(9,_T("Card No"),LVCFMT_LEFT,50);
	
	m_cLstEvent.InsertColumn(10,_T("Card Holder Name"),LVCFMT_LEFT,100);
	m_cLstEvent.InsertColumn(11,_T("CommServerID"),LVCFMT_LEFT,50);
	m_cLstEvent.InsertColumn(12,_T("HID"),LVCFMT_LEFT,50);
	m_cLstEvent.InsertColumn(13,_T("DeviceID"),LVCFMT_LEFT,50);
	m_cLstEvent.InsertColumn(14,_T("Note"),LVCFMT_LEFT,50);
	//Removed as Obselete -- Guru
	//m_cLstEvent.InsertColumn(15,_T("No"),LVCFMT_LEFT,50);

	m_cLstEvent.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// Load Column headers to IDC_LST_Status
	m_cLstStatus.InsertColumn(0,_T("HID"),LVCFMT_LEFT,90);
	m_cLstStatus.InsertColumn(1,_T("Device Type"),LVCFMT_LEFT,100);
	m_cLstStatus.InsertColumn(2,_T("Device Name"),LVCFMT_LEFT,100);
	m_cLstStatus.InsertColumn(3,_T("Status ID"),LVCFMT_LEFT,70);
	m_cLstStatus.InsertColumn(4,_T("Status Description"),LVCFMT_LEFT,150);
	
	m_cLstStatus.SetExtendedStyle(LVS_EX_FULLROWSELECT);

}	
/*********************************************************************************/
// Description : Parses the XML string and returns the field value requested
//				 If the field is not found in the XML string it returns null.
// Parameters  : szInput - CString object which contains an XML string 
//				 szField - CString object which contains the field name
/*********************************************************************************/
CString CVCClientDlg::GetFieldFromInput(const CString szInput,const CString szField)
{
	
	int iStartPos = szInput.Find(_T("<") + szField,0);
	if(iStartPos >= 0) 
	{
		int iSize = szField.GetLength();
		int iLastPos = szInput.Find(_T("</") + szField,iStartPos+1);
		
		iSize = iStartPos + 2 + iSize;
		iLastPos = iLastPos -  iSize; 
		return(szInput.Mid(iSize,iLastPos));
	}
	else
		return(_T(""));	
}
/*********************************************************************************/
// Description : Adds the event string to the event list
// Parameters  : szInput - contains the event message from API 
/*********************************************************************************/
void CVCClientDlg::AddToEventList(CString szInput)
{
	CStringArray szarr;
	szarr.Add(PR_Idx);
	szarr.Add(PR_Prio);
	szarr.Add(PR_Date);
	szarr.Add(PR_Time);
	szarr.Add(PR_Cnt);
	szarr.Add(PR_Status);
	szarr.Add(PR_Event); //eventid
	szarr.Add(PR_RP);
	szarr.Add(PR_Site);
	szarr.Add(PR_CardNumber);
	
	szarr.Add(PR_FullName);
	szarr.Add(PR_CommSrvID);
	szarr.Add(PR_HID);
	szarr.Add(PR_DEVICEID);
	szarr.Add(PR_Note);

	LVITEM lvi;
	CString szTemp1;

	lvi.mask = LVIF_TEXT;
	lvi.iItem = m_iEventItemNo;
	lvi.iSubItem = 0;
	szTemp1 = GetFieldFromInput(szInput,szarr.GetAt(0) );
	lvi.pszText = szTemp1.GetBuffer(szTemp1.GetLength());
	m_cLstEvent.InsertItem(&lvi);

	for( int i = 1 ; i<15 ; i++)
	{
		lvi.iSubItem  = i;
		szTemp1 = GetFieldFromInput(szInput,szarr.GetAt(i) );
		lvi.pszText = szTemp1.GetBuffer(szTemp1.GetLength());
		m_cLstEvent.SetItem( &lvi);
	}

	m_iEventItemNo++;
}
/*********************************************************************************/
// Description : Adds the status string to the status list
// Parameter   : szInput - contains the status message from the API
/*********************************************************************************/
void CVCClientDlg::AddToStatusList(CString szInput)
{
	
	//AfxMessageBox (szInput);

	CStringArray szarr;
	szarr.Add(PR_ADVHid);
	szarr.Add(PR_ADVDeviceType);
	szarr.Add(PR_ADVDeviceName);
	szarr.Add(PR_ADVStatus);

	LVITEM lvi;
	CString szTemp1;

	lvi.mask = LVIF_TEXT;
	lvi.iItem = m_iStatusItemNo;
	lvi.iSubItem = 0;
	szTemp1 = GetFieldFromInput(szInput,szarr.GetAt(0) );
	
	lvi.pszText = szTemp1.GetBuffer(szTemp1.GetLength());
	m_cLstStatus.InsertItem(&lvi);

	for( int i = 1 ; i<4 ; i++)
	{
		lvi.iSubItem  = i;
		szTemp1 = GetFieldFromInput(szInput,szarr.GetAt(i) );
		lvi.pszText = szTemp1.GetBuffer(szTemp1.GetLength());
		m_cLstStatus.SetItem( &lvi);
	}
	lvi.iSubItem  = 4;
	szTemp1 = GetStatusDescriptionByStatusID( GetFieldFromInput(szInput,szarr.GetAt(3)) );
	lvi.pszText = szTemp1.GetBuffer(szTemp1.GetLength());
	m_cLstStatus.SetItem( &lvi);

	m_iStatusItemNo++;
	
}
/*********************************************************************************/
// Acknowledges an alarm 
/*********************************************************************************/
void CVCClientDlg::OnBtnAck() 
{
	UpdateData(TRUE);
	CString bSelectedItem = "";

	if (m_bLoggedIn)
	{
		int nSel = m_ctlListAlarm.GetCurSel();
		if (nSel != LB_ERR)
		{
			m_ctlListAlarm.GetText(nSel, bSelectedItem);
			b_transaction = bSelectedItem.AllocSysString();
			m_pServer->AckAlarm(b_transaction, m_lAlarmHID, m_lAlarmPointID);
			if (SysStringByteLen(b_transaction))
				SysFreeString(b_transaction);
			m_ctlListAlarm.DeleteString(nSel);
			
		}
		else
			AfxMessageBox(_T("Select the Alarm to Acknowlede"));
	}
	else
		AfxMessageBox(_T("Please Login First"));

	
}
/*********************************************************************************/
// Clears an alarm
/*********************************************************************************/
void CVCClientDlg::OnBtnClear() 
{	
	UpdateData(TRUE);
	CString bSelectedItem = "";
	
	if (m_bLoggedIn)
	{
		int nSel = m_ctlListAlarm.GetCurSel();
		if (nSel != LB_ERR)
		{
			m_ctlListAlarm.GetText(nSel, bSelectedItem);
			b_transaction = bSelectedItem.AllocSysString();
			m_pServer->ClrAlarm(b_transaction, m_lAlarmHID, m_lAlarmPointID);
			if (SysStringByteLen(b_transaction))
				SysFreeString(b_transaction);
			m_ctlListAlarm.DeleteString(nSel);
		}
		else
			AfxMessageBox(_T("Select the Alarm to Clear"));
	}
	else
		AfxMessageBox(_T("Please Login First"));
	
}
/*********************************************************************************/
// Retrieves the status message of all the configured devices
/*********************************************************************************/
void CVCClientDlg::OnBtnStatus() 
{
	if(!m_bLoggedIn)
	{
		AfxMessageBox(_T("Please Login First"));
		return;
	}

	VARIANT VarDevices;
	m_pServer->ListConnectedDevices(&VarDevices);	
	
	Device *pDevice;
	SafeArrayAccessData(VarDevices.parray,(void**)&pDevice);
	
	long lStatusID ;
	
	for( unsigned int i =0 ; i < (VarDevices.parray->rgsabound[0].cElements) ; i++)
	{	
		m_pServer->GetStatus(pDevice[i].lDeviceID,pDevice[i].lDeviceType, &lStatusID);
	}
}
/*********************************************************************************/
// Retrieves the detailed message of an alarm
/*********************************************************************************/
void CVCClientDlg::OnBtndetails() 
{
	BSTR bstrTransaction;
	UpdateData(TRUE);
	if(!m_bLoggedIn)
	{
		AfxMessageBox(_T("Please Login First"));
		return;
	}
	m_pServer->GetDetailsByID(m_lAlarmHID,m_lAlarmPointID,&bstrTransaction);
	m_LstDetails.AddString(CString( bstrTransaction) );
}
/*********************************************************************************/
// Description : Returns the status description of the status ID
// Parameter   : szInput - contains the status ID 
/*********************************************************************************/
CString GetStatusDescriptionByStatusID(CString szInput)
{
	CString szSDesc ;
	CStringArray szarr300;
	CStringArray szarr400;
	CStringArray szarr900;

	szarr300.Add("");	//0
	szarr300.Add("Entrance Unknown");
	szarr300.Add("Entrance Alarm");
	szarr300.Add("Entrance OK");
	szarr300.Add("Entrance Trouble"); //4

	szarr400.Add("Input Unknown"); //0
	szarr400.Add("Input Alarm");
	szarr400.Add("Door Ajar");
	szarr400.Add("Input Normal");
	szarr400.Add("Input Trouble"); //4
	// Added for PRO2200 Input States, for SE/PE API
	szarr400.Add("Exit in Progress");
	szarr400.Add("Entry in Progress");
	// Added for the NetAXS Addition -- Guru
	szarr400.Add("Input Trouble Cut");
	szarr400.Add("Input Trouble Short");

	szarr900.Add("Panel Unknown");	//0
	szarr900.Add("Panel Alarms:");	//1
	szarr900.Add("Panel OK");	//2
	
	switch( _wtoi(szInput.GetBuffer(4)) )
	{
		case 300:	 // NULL
			szSDesc = szarr300.GetAt(0);	break; 
		case 301:   // Entrance Unknown
			szSDesc = szarr300.GetAt(1);	break; 
		case 302:	// Entrance Alarm
			szSDesc = szarr300.GetAt(2);	break; 
		case 303:	// Entrance OK
			szSDesc = szarr300.GetAt(3);	break; 
		case 304:	// Entrance Trouble
			szSDesc = szarr300.GetAt(4);	break; 
		case 401:	// Input Unknown
			szSDesc = szarr400.GetAt(0);	break; 
		case 402:	// Input Alarm
			szSDesc = szarr400.GetAt(1);	break;
		case 403:	// Door Ajar
			szSDesc = szarr400.GetAt(2);	break;
		case 404:	// Input Normal
			szSDesc = szarr400.GetAt(3);	break;
		case 405:	// Input Trouble
			szSDesc = szarr400.GetAt(4);	break;
		case 406:	// Entry in Progress
			szSDesc = szarr400.GetAt(5);	break;
		case 407:	// Exit in Progress
			szSDesc = szarr400.GetAt(6);	break;
		case 408:	// Input Trouble Cut
			szSDesc = szarr400.GetAt(7);	break;
		case 409:	// Input Trouble Short
			szSDesc = szarr400.GetAt(8);	break;
		case 501:
			szSDesc = "Output Unknown";		break;
		case 502:
			szSDesc = "Output Deenergized"; break;
		case 503:
			szSDesc = "Output  Energized";	break;
		case 504:
			szSDesc = "Output Trouble";		break;
		case 801:
			szSDesc = "Server Unknown";		break;
		case 802:
			szSDesc = "Server Trouble";		break;
		case 803:
			szSDesc = "Server OK";			break;
		case 901:	// Panel Unknown
			szSDesc = szarr900.GetAt(0);	break;
		case 902:	// Panel Alarms:
			szSDesc = szarr900.GetAt(1);	break;
		case 903:	// Panel OK
			szSDesc = szarr900.GetAt(2);	break;
		case 601:
			szSDesc = "Loop Unknown";		break;
		case 602:
			szSDesc = "Loop Alarm";			break;
		case 603:
			szSDesc = "Loop OK";			break;
		case 701:
			szSDesc = "Unknown";			break;
		case 702:
			szSDesc = "Alarm";				break;
		case 703:
			szSDesc = "OK";					break;
		// Added for the NetAXS Addition -- Guru
		case 1001:
			szSDesc = "NX4 Device Unknown";			break;
		case 1002:
			szSDesc = "NX4 Device Normal";			break;
		case 1003:
			szSDesc = "NX4 Device Trouble";			break;

		default:
			{
				switch( _wtoi(szInput.Mid(0,2).GetBuffer(3)) ) 
				{
				case 35: // Shunted - if status ID is 35* (i.e) 350/351/352/353/354
					{
						szSDesc = _T("Shunted ");
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 4)&&(szInput.Mid(2,1).Compare(_itow(i, ch, 10))) ; i++);
							szSDesc += szarr300.GetAt(i);
		
					}break;
				case 45: // Shunted - if status ID is 45* 
					{
						szSDesc = _T("Shunted ");
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 5)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc += szarr400.GetAt(i-1);
					}break;
				case 91: // Panel Comm -  if status ID is 91* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " Panel Comm ";
					}break;
				case 92: // AUX Port - if status ID is 92* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " AUX Port ";						
					}break;
				case 93: // Primary Power - if status ID is 93* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " Primary Power ";
					
					}break;
				case 94:// Panel Tamper - if status ID is 94* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " Panel Tamper ";
					
					}break;
				case 95: // Ground Fault - if status ID is 95* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " Ground Fault ";
					}break;
				case 96: // Low Voltage - if status ID is 96* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " Low Voltage ";
					}break;
				case 97: // Ext 5V - if status ID is 97* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " Ext 5V ";
					}break;
				case 98: // Poll Response - if status ID is 98* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " Poll Response ";
					}break;
				case 99: // Remote - if status ID is 99* 
					{
						_TCHAR ch[2];
						// To Do Porting : Kalpesh : 19-oct-21 : error C2065 : declare int i variable outside
						int i = 0 ;
						for( i = 0 ;(i <= 3)&&(szInput.Mid(2,1).Compare(_itow(i,ch,10))) ; i++);
							szSDesc = szarr900.GetAt(i-1);
						szSDesc += " Remote ";
					}break;
				}// switch - level2 
			}// default - level1
	}// switch - level1
	return szSDesc;
}


void CVCClientDlg::OnMenuPanelControl()
{
	if(!m_bLoggedIn)
	{
		AfxMessageBox(_T("Please Login First"));
		return;
	}
	CDlgPointControl dlg(this);
	dlg.DoModal();
}

void CVCClientDlg::OnMenuADVControl()
{
	if(!m_bLoggedIn)
	{
		AfxMessageBox(_T("Please Login First"));
		return;
	}
	CDlgADVControl dlg(this);
	dlg.DoModal();
}

void CVCClientDlg::OnMenuAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

/*********************************************************************************/
// Description :This method is called by the client to register itself to the client. 
//				It passes the callback pointer to the API so that API can send 
//				alarm/event/command/status messages to the client 
// Parameters  : -
/*********************************************************************************/

void CVCClientDlg::OnMenuLogin()
{
    
	if(m_bLoggedIn)
	{
		AfxMessageBox(_T("Sorry, Already Logged in!"));
		return;
	}

	::CoInitialize(NULL);


	CWPCommLoginDlg dlg(this);
	
	dlg.DoModal();

	if(FALSE == dlg.m_bLogin)
	{
		
		m_bLoggedIn = FALSE;
	
		return;
	}
	m_bLoggedIn = TRUE;
		
	m_strUser = dlg.m_strUname;
	DWORD dwThreadID;

	m_hdlThread  =  CreateThread(0,0,ClientThread,this,0,&dwThreadID);



	//GetDlgItem(IDC_STATIC_OPERATOR)->SetWindowText(m_strUser);

	::CoUninitialize();
	
	UpdateData(FALSE);
}

void CVCClientDlg::OnMenuLogout()
{
	if(FALSE == m_bLoggedIn)
	{
		AfxMessageBox(_T("Please Login First"));
		return;
	}
	
	// To Reslove COM Server Crash-------->> praveen....WPACT-228 
	
	VARIANT_BOOL pbResult;
	
		m_pServer->DoneServer(m_pCallback,&pbResult);

	DWORD dwExitCode = 0;
	TerminateThread(m_hdlThread,dwExitCode);

	m_pServer = NULL;
	m_pCallback = NULL;

	//m_pServer->DoneServer(m_pCallback,&pbResult);

	//m_pServer = NULL;
	
	//DWORD dwExitCode = 0;
	//TerminateThread(m_hdlThread,dwExitCode);
	
	
	//Do not NULL the m_pServer and m_pCallback

	m_cLstEvent.DeleteAllItems();
		
	m_cLstStatus.DeleteAllItems();
	
	m_ctlListAlarm.ResetContent();
	
	m_LstDetails.ResetContent();
	
	m_bLoggedIn = FALSE;
	
	m_strUser = _T("");
	UpdateData(FALSE);
}


void CVCClientDlg::OnMenuExit()
{
	OnCancel();
}


void CVCClientDlg::OnBtnAddNote() 
{
	if(!m_bLoggedIn)
	{
		AfxMessageBox(_T("Please Login First"));
		return;
	}

	UpdateData();
	m_pServer->AddNote(m_lAlarmHID, m_lAlarmPointID, m_strNote.AllocSysString());
}

void CVCClientDlg::OnLbnSelchangeListAlarm()
{
	CString ItemSelected = _T("");


	CListCtrl LstCtrl;
	
	int nSel = m_ctlListAlarm.GetCurSel();
	if (nSel != LB_ERR)
	{
		m_ctlListAlarm.GetText(nSel, ItemSelected);
		LstCtrl.GetItemData(nSel);
	}

	if (!ItemSelected.IsEmpty())
	{
		CString strStatus = GetFieldFromInput(ItemSelected, PR_Status);
		CString strHID = GetFieldFromInput(ItemSelected, PR_HID);
		CString strPointID = GetFieldFromInput(ItemSelected, PR_Point);
		
		m_lAlarmHID = _wtol(strHID);
		m_lAlarmPointID = _wtol(strPointID);

		if (!strStatus.IsEmpty())
		{
			bool bFound = false;
			for (int nIndex = 0; nIndex < g_nsize; nIndex++)
			{
				if (0 == g_SystemAlarmActions[nIndex].Compare(strStatus))
				{
					bFound = true;
					break;
				}
			}

			if (bFound)
			{
				m_LstDetails.ResetContent();
				m_LstDetails.AddString(strStatus);

			}
		}
		UpdateData(FALSE);
	}
}