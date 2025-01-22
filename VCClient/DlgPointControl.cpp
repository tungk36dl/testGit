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

  File Name     : DlgPointControl.cpp

  Project		: WP-CS API Test Client

  Originator	: Sathish Guru V

  APPLICATION	: WP-CS API Communication server Test Client

  MODULE		: 

  PURPOSE		: Dialog of Having the Test of Contolling all Panel ADVs

  REVISION HISTORY:

  Rev	   Date		 Programmer            Comment
  ----    --------	--------------   ---------------------
  1.0	 29 Nov  2011	Sathish Guru	Initial Version
  1.1	 02 Jan	 2012	Sathish Guru	Prototype Bugfixes


/********************************************************************************/

#include "stdafx.h"
#include "vcclient.h"
#include "DlgPointControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPointControl dialog


CDlgPointControl::CDlgPointControl(CWnd* pParent)
	: CDialog(CDlgPointControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPointControl)
	m_bAccessArea = FALSE;
	m_bAccessLevels = FALSE;
	m_bPanelConfig = FALSE;
	m_bCards = FALSE;
	m_bCardFormats = FALSE;
	m_bCmdFiles = FALSE;
	m_bTZRefresh = FALSE;
	m_bGroups = FALSE;
	m_bHolidays = FALSE;
	m_bInputScanCodes = FALSE;
	m_bInputs = FALSE;
	m_bMCPGroups = FALSE;
	m_bOutputs = FALSE;
	m_bProcedures = FALSE;
	m_bReaderLED = FALSE;
	m_bDateTime = FALSE;
	m_bSIO = FALSE;
	m_bTimezones = FALSE;
	m_bTriggers = FALSE;
	m_nPanelHID = 0;
	m_bMCBConfig = FALSE;
	m_bPSeriesPanel = FALSE;
	// For P-Series Encryption -- Guru
	m_bMCBEncryption = FALSE;
	m_pParent = (CVCClientDlg *)pParent;
	m_lHIDType = 0;
	m_nPanelType = 0;

	m_lPanelType = 0;
	m_lDoorHID = 0;
	m_lDoorPointID = 0;
	m_lTZID = 0;

	m_bSelectAll = TRUE;
	//}}AFX_DATA_INIT
}


void CDlgPointControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPointControl)
	DDX_Check(pDX, IDC_CHK_ACCESS_AREA__WINPAK, m_bAccessArea);
	DDX_Check(pDX, IDC_CHK_ACCESS_LEVEL__WINPAK, m_bAccessLevels);
	DDX_Check(pDX, IDC_CHK_BASIC_CONFIG__WINPAK, m_bPanelConfig);
	DDX_Check(pDX, IDC_CHK_CARD__WINPAK, m_bCards);
	DDX_Check(pDX, IDC_CHK_CARD_FMT__WINPAK, m_bCardFormats);
	DDX_Check(pDX, IDC_CHK_CMD_FILES__WINPAK, m_bCmdFiles);
	DDX_Check(pDX, IDC_CHK_TZREFRESH__WINPAK, m_bTZRefresh);
	DDX_Check(pDX, IDC_CHK_GROUPS__WINPAK, m_bGroups);
	DDX_Check(pDX, IDC_CHK_HOLIDAY__WINPAK, m_bHolidays);
	DDX_Check(pDX, IDC_CHK_INP_SCAN_CNV__WINPAK, m_bInputScanCodes);
	DDX_Check(pDX, IDC_CHK_INPUTS__WINPAK, m_bInputs);
	DDX_Check(pDX, IDC_CHK_MP_GROUP__WINPAK, m_bMCPGroups);
	DDX_Check(pDX, IDC_CHK_OUTPUTS__WINPAK, m_bOutputs);
	DDX_Check(pDX, IDC_CHK_PROC_ACTION__WINPAK, m_bProcedures);
	DDX_Check(pDX, IDC_CHK_READER_LED__WINPAK, m_bReaderLED);
	DDX_Check(pDX, IDC_CHK_SCP_TIME__WINPAK, m_bDateTime);
	DDX_Check(pDX, IDC_CHK_SIO__WINPAK, m_bSIO);
	DDX_Check(pDX, IDC_CHK_TIMEZONE__WINPAK, m_bTimezones);
	DDX_Check(pDX, IDC_CHK_TRIGGER__WINPAK, m_bTriggers);
	DDX_Text(pDX, IDC_EDIT_PANEL_HID, m_nPanelHID);
	DDX_Text(pDX, IDC_EDIT_HID_TYPE, m_lHIDType);
	DDX_Check(pDX, IDC_CHK_SCP_CONFIG__WINPAK, m_bMCBConfig);
	DDX_Radio(pDX, IDC_RADIO_NS_PANELS, m_nPanelType);
	DDX_Check(pDX, IDC_CHK_ENCRYPT__WINPAK, m_bMCBEncryption);
	

	DDX_Text(pDX, IDC_EDIT_PANEL_TYPE, m_lPanelType);
	DDX_Text(pDX, IDC_EDIT_DOOR_HID, m_lDoorHID);
	DDX_Text(pDX, IDC_EDIT_DOOR_POINTID, m_lDoorPointID);
	DDX_Text(pDX, IDC_EDIT_TZID, m_lTZID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPointControl, CDialog)
	//{{AFX_MSG_MAP(CDlgPointControl)
	ON_BN_CLICKED(IDC_BTN_INIT_START, OnBtnInitStart)
	ON_BN_CLICKED(IDC_BTN_INIT_END, OnBtnInitEnd)
	ON_BN_CLICKED(IDC_RADIO_NS_PANELS, OnRadioNSPanels)
	ON_BN_CLICKED(IDC_RADIO_P_SERIES, OnRadioPSeries)
	ON_BN_CLICKED(IDC_BTN_BUFFER, OnBtnPanelBuffer)
	ON_BN_CLICKED(IDC_BTN_UNBUFFER, OnBtnPanelUnbuffer)
	ON_BN_CLICKED(IDC_BTN_EXECUTE, OnBtnExecuteDoorScdl)
	ON_BN_CLICKED(IDC_BTN_SELECTALL__WINPAK, OnBtnSelectAll)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPointControl message handlers


void CDlgPointControl::OnBtnSelectAll()
{
	UpdateData();

	m_bAccessArea = m_bSelectAll;
	m_bAccessLevels = m_bSelectAll;
	m_bPanelConfig = m_bSelectAll;
	m_bCards = m_bSelectAll;
	m_bCardFormats = m_bSelectAll;
	m_bCmdFiles = m_bSelectAll;
	m_bTZRefresh = m_bSelectAll;
	m_bGroups = m_bSelectAll;
	m_bHolidays = m_bSelectAll;
	m_bInputScanCodes = m_bSelectAll;
	m_bInputs = m_bSelectAll;
	m_bMCPGroups = m_bSelectAll;
	m_bOutputs = m_bSelectAll;
	m_bProcedures = m_bSelectAll;
	m_bReaderLED = m_bSelectAll;
	m_bDateTime = m_bSelectAll;
	m_bSIO = m_bSelectAll;
	m_bTimezones = m_bSelectAll;
	m_bTriggers = m_bSelectAll;
	m_bMCBConfig = m_bSelectAll;
	m_bMCBEncryption = m_bSelectAll;

	UpdateData(FALSE);

	m_bSelectAll = !m_bSelectAll;

	if(m_bSelectAll)
		GetDlgItem(IDC_BTN_SELECTALL__WINPAK)->SetWindowText(_T("Select All"));
	else
		GetDlgItem(IDC_BTN_SELECTALL__WINPAK)->SetWindowText(_T("Deselect All"));
	
}

void CDlgPointControl::OnBtnInitStart() 
{
	UpdateData(TRUE);

	int arrTasks[21];

	for (int i = 0; i < 21; i++) 
	{ 
		arrTasks[i] = 0; //TT 838 FIX,840 FIX 
	}

	if(m_bPSeriesPanel)
	{
		arrTasks[1/*(int)panelInitTask.taskTIMEDATE*/] = m_bDateTime;
		arrTasks[2/*(int)panelInitTask.taskCARD*/] = m_bCards;
		arrTasks[4/*(int)panelInitTask.taskHOLIDAY*/] = m_bHolidays;
		arrTasks[5/*(int)panelInitTask.taskTIMEZONE*/] = m_bTimezones;
	

		arrTasks[9/*(int)panelInitTask.taskMCBCONFIG*/] = m_bMCBConfig;
		arrTasks[10/*(int)panelInitTask.taskINPUTSCAN*/] = m_bInputScanCodes;
		arrTasks[11/*(int)panelInitTask.taskCARDFORMAT*/] = m_bCardFormats;
		arrTasks[12/*(int)panelInitTask.taskSIOBOARD*/] = m_bSIO;
		arrTasks[13/*(int)panelInitTask.taskACCESSLEVELS*/] = m_bAccessLevels;
		arrTasks[14/*(int)panelInitTask.taskTRIGGERS*/] = m_bTriggers;
		arrTasks[15/*(int)panelInitTask.taskPROCEDURES*/] = m_bProcedures;
		arrTasks[16/*(int)panelInitTask.taskMPGROUPS*/] = m_bMCPGroups;
		arrTasks[17/*(int)panelInitTask.taskACCESSAREAS*/] = m_bAccessArea;
		arrTasks[18/*(int)panelInitTask.taskREADERLED*/] = m_bReaderLED;
		arrTasks[19/*(int)panelInitTask.taskTZREFRESH*/] = m_bTZRefresh;
		// Added for the P-Series Encryption Option -- Guru
		arrTasks[19/*(int)panelInitTask.taskMCPENCRYPT*/] = m_bMCBEncryption;
	}
	else
	{
		arrTasks[0/*(int)panelInitTask.taskINIT*/] = m_bPanelConfig;
		arrTasks[1/*(int)panelInitTask.taskTIMEDATE*/] = m_bDateTime;
		arrTasks[2/*(int)panelInitTask.taskCARD*/] = m_bCards;
		arrTasks[3/*(int)panelInitTask.taskCMDFILE*/] = m_bCmdFiles;
		arrTasks[4/*(int)panelInitTask.taskHOLIDAY*/] = m_bHolidays;
		arrTasks[5/*(int)panelInitTask.taskTIMEZONE*/] = m_bTimezones;
		arrTasks[6/*(int)panelInitTask.taskINPUT*/] = m_bInputs;
		arrTasks[7/*(int)panelInitTask.taskOUTPUT*/] = m_bOutputs;
		arrTasks[8/*(int)panelInitTask.taskGROUP*/] = m_bGroups;
	}

	_variant_t vTasks;
	VariantInit(&vTasks);
	vTasks.vt = VT_ARRAY | VT_R4;
	SAFEARRAYBOUND rgsabounds;
	rgsabounds.cElements = 20;
	rgsabounds.lLbound = 0;

	COleSafeArray psaTasks;
	psaTasks.CreateOneDim(VT_I4, 21, arrTasks);

	//psaTasks.UnaccessData();
	//LPCVARIANT pcVariant = (LPCVARIANT)psaTasks; 
	//vTasks.parray = pcVariant->parray;
	psaTasks.Copy(&vTasks.parray);//WPACT-6003
	

	HRESULT hRes = m_pParent->m_pServer->PanelInitialize(m_nPanelHID, m_lHIDType, vTasks);
	if(FAILED(hRes))
		AfxMessageBox(_T("Error in Initialization"));
}

void CDlgPointControl::OnBtnInitEnd() 
{
	UpdateData(TRUE);
	m_pParent->m_pServer->PanelCancelInitialize(m_nPanelHID);
}

void CDlgPointControl::OnRadioNSPanels() 
{
	CheckPanelType();
}

void CDlgPointControl::OnRadioPSeries() 
{
	CheckPanelType();
}

void CDlgPointControl::DisableSomeControls()
{
	UpdateData();

	if(m_bPSeriesPanel)
	{
		GetDlgItem(IDC_CHK_SCP_CONFIG__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_INP_SCAN_CNV__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_CARD_FMT__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_SIO__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_TRIGGER__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_MP_GROUP__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_ACCESS_AREA__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_READER_LED__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_PROC_ACTION__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_ACCESS_LEVEL__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_TZREFRESH__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_ENCRYPT__WINPAK)->EnableWindow(TRUE);

		GetDlgItem(IDC_CHK_BASIC_CONFIG__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_CMD_FILES__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_INPUTS__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_OUTPUTS__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_GROUPS__WINPAK)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHK_SCP_CONFIG__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_INP_SCAN_CNV__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_CARD_FMT__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_SIO__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_TRIGGER__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_MP_GROUP__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_ACCESS_AREA__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_READER_LED__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_PROC_ACTION__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_ACCESS_LEVEL__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_TZREFRESH__WINPAK)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_ENCRYPT__WINPAK)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHK_BASIC_CONFIG__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_CMD_FILES__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_INPUTS__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_OUTPUTS__WINPAK)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHK_GROUPS__WINPAK)->EnableWindow(TRUE);
	}
}

BOOL CDlgPointControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DisableSomeControls();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgPointControl::CheckPanelType()
{
	UpdateData();

	switch(m_nPanelType)
	{
		case 0:
			m_bPSeriesPanel = FALSE;
			break;

		case 1:
			m_bPSeriesPanel = TRUE;
			break;
	}

	DisableSomeControls();
}

void CDlgPointControl::OnBtnPanelBuffer() 
{
	UpdateData();
	m_pParent->m_pServer->BufferByHID(m_nPanelHID, m_nBufferMode);
}



void CDlgPointControl::OnBtnPanelUnbuffer() 
{
	UpdateData();
	m_pParent->m_pServer->UnBufferByHID(m_nPanelHID, m_nBufferMode);
}


void CDlgPointControl::OnBtnExecuteDoorScdl()
{
	UpdateData();
	m_pParent->m_pServer->ExecuteDoorSchedule(m_nPanelHID, m_lPanelType, m_lDoorHID, m_lDoorPointID, m_lTZID);
}
