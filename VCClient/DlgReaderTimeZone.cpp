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

  File Name     : DlgReaderTimezone.cpp

  Project		: WP-CS API Test Client

  Originator	: Sathish Guru V

  APPLICATION	: WP-CS API Communication server Test Client

  MODULE		: 

  PURPOSE		: Dialog to Display the NetAXS Door Mode for Readers

  REVISION HISTORY:

  Rev	   Date		 Programmer            Comment
  ----    --------	--------------   ---------------------
  1.0	 05 Nov	 2011	Sathish Guru	Initial Version
  1.1	 29 Nov  2011	Sathish Guru	Implementing CSAC API NetAXS Changes
  1.2	 02 Jan	 2012	Sathish Guru	Prototype Bugfixes


/********************************************************************************/
#include "stdafx.h"
#include "vcclient.h"
#include "DlgReaderTimeZone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgReaderTimeZone dialog


CDlgReaderTimeZone::CDlgReaderTimeZone(CWnd* pParent /*=NULL*/, long lHID, BOOL bEdit, INetAXSDoorInfo *pData)
	: CDialog(CDlgReaderTimeZone::IDD, pParent)
{
	short shCardOnlyPriority = -1, shPinOnlyPriority = -1, shCardAndPinPriority = -1, shCardOrPinPriority = -1;
	//{{AFX_DATA_INIT(DlgReaderTimeZone)
	m_nHID = lHID;
	m_bEdit = bEdit;
	if(false)
	{
		m_nDisableTimeZoneID = 0;
		m_nLockTimeZoneID = 0;
		m_nCardAndPinTimeZoneID = 0;
		m_nCardOrPinTimeZoneID = 0;
		m_nPinOnlyTimeZoneID = 0;
		m_nCardOnlyTimeZoneID = 0;
		
		
		m_nCardAndPinPriority = -1;
		m_nCardOrPinPriority = -1;
		m_nPinOnlyPriority = -1;
		m_nCardOnlyPriority = -1;
		m_nHWDeviceID = 0;
		m_nHWDeviceSubID2 = 0;
	}
	else
	{
		pData->get_DisableDoorTimezone(&m_nDisableTimeZoneID);
		pData->get_LockdownReaderTimezone(&m_nLockTimeZoneID);
		pData->get_CardOnlyTimezone(&m_nCardOnlyTimeZoneID);
		pData->get_PINOnlyTimezone(&m_nPinOnlyTimeZoneID);
		pData->get_CardAndPINTimezone(&m_nCardAndPinTimeZoneID);
		pData->get_CardOrPINTimezone(&m_nCardOrPinTimeZoneID);

		pData->get_CardOnlyPriority(&shCardOnlyPriority);
		pData->get_PINOnlyPriority(&shPinOnlyPriority);
		pData->get_CardAndPINPriority(&shCardAndPinPriority);
		pData->get_CardOrPINPriority(&shCardOrPinPriority);

		m_nCardAndPinPriority = (int) shCardAndPinPriority;
		m_nCardOrPinPriority = (int) shCardOrPinPriority;
		m_nCardOnlyPriority = (int) shCardOnlyPriority;
		m_nPinOnlyPriority = (int) shPinOnlyPriority;
	}
	//}}AFX_DATA_INIT
}

CDlgReaderTimeZone::~CDlgReaderTimeZone()
{
}

void CDlgReaderTimeZone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgReaderTimeZone)
	DDX_Radio(pDX, IDC_CTP_READER_STAN_CARD_AND_PIN,		 	  m_nCardAndPinPriority);
	DDX_Radio(pDX, IDC_CTP_READER_STAN_CARD_OR_PIN,				  m_nCardOrPinPriority);
	DDX_Radio(pDX, IDC_CTP_READER_STAN_PIN_ONLY,				  m_nPinOnlyPriority);
	DDX_Radio(pDX, IDC_CTP_READER_STAN_CARD_ONLY,			  m_nCardOnlyPriority);
	
	DDX_Text(pDX, IDC_CTP_PANEL_HID, m_nHID);
	DDX_Text(pDX, IDC_CTP_PANEL_COMBO_AD_READER_DISABLE_DOOR, m_nDisableTimeZoneID);
	DDX_Text(pDX, IDC_CTP_PANEL_COMBO_AD_READER_LOCK, m_nLockTimeZoneID);
	DDX_Text(pDX, IDC_CTP_PANEL_COMBO_AD_READER_CARD_AND_PIN, m_nCardAndPinTimeZoneID);
	DDX_Text(pDX, IDC_CTP_PANEL_COMBO_AD_READER_CARD_OR_PIN, m_nCardOrPinTimeZoneID);
	DDX_Text(pDX, IDC_CTP_PANEL_COMBO_AD_READER_PIN_ONLY, m_nPinOnlyTimeZoneID);
	DDX_Text(pDX, IDC_CTP_PANEL_COMBO_AD_READER_CARD_ONLY, m_nCardOnlyTimeZoneID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgReaderTimeZone, CDialog)
	//{{AFX_MSG_MAP(CDlgReaderTimeZone)
	ON_BN_CLICKED(IDC_CTP_READER_STAN_CARD_AND_PIN           , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_SUPERVISOR_CARD_AND_PIN     , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_ESCORT_CARD_AND_PIN         , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_STAN_CARD_OR_PIN            , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_SUPERVISOR_CARD_OR_PIN      , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_ESCORT_CARD_OR_PIN          , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_STAN_PIN_ONLY               , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_SUPERVISOR_PIN_ONLY         , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_ESCORT_PIN_ONLY             , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_STAN_CARD_ONLY              , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_SUPERVISOR_CARD_ONLY        , OnPriorityChanged)
	ON_BN_CLICKED(IDC_CTP_READER_ESCORT_CARD_ONLY            , OnPriorityChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgReaderTimeZone message handlers

BOOL CDlgReaderTimeZone::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_CTP_PANEL_HID)->EnableWindow(FALSE);

	UpdateData(FALSE);

	if(!m_bEdit)
	{
		DisableAllControls();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgReaderTimeZone::OnOK() 
{
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CDlgReaderTimeZone::EnableCardPriorityControls(int m_nCardAndPinTimeZoneID, int m_nCardOrPinTimeZoneID,
									int	m_nPinOnlyTimeZoneID, int m_nCardOnlyTimeZoneID)
{

	if(m_nCardAndPinTimeZoneID == 0)
	{
		GetDlgItem(IDC_CTP_READER_STAN_CARD_AND_PIN)->EnableWindow(FALSE);      
		GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_AND_PIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTP_READER_ESCORT_CARD_AND_PIN)->EnableWindow(FALSE);
	}
	else if(m_nCardAndPinTimeZoneID > 0)
	{
		GetDlgItem(IDC_CTP_READER_STAN_CARD_AND_PIN)->EnableWindow(TRUE);      
		GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_AND_PIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_CTP_READER_ESCORT_CARD_AND_PIN)->EnableWindow(TRUE);
	}

	if(m_nCardOrPinTimeZoneID == 0)
	{
		GetDlgItem(IDC_CTP_READER_STAN_CARD_OR_PIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_OR_PIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTP_READER_ESCORT_CARD_OR_PIN)->EnableWindow(FALSE);
	}
	else if(m_nCardOrPinTimeZoneID > 0)
	{
		GetDlgItem(IDC_CTP_READER_STAN_CARD_OR_PIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_OR_PIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_CTP_READER_ESCORT_CARD_OR_PIN)->EnableWindow(TRUE);
	}
		
	if(m_nPinOnlyTimeZoneID == 0)
	{
		GetDlgItem(IDC_CTP_READER_STAN_PIN_ONLY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTP_READER_SUPERVISOR_PIN_ONLY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTP_READER_ESCORT_PIN_ONLY)->EnableWindow(FALSE);
	}
	else if(m_nPinOnlyTimeZoneID > 0)
	{
		GetDlgItem(IDC_CTP_READER_STAN_PIN_ONLY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CTP_READER_SUPERVISOR_PIN_ONLY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CTP_READER_ESCORT_PIN_ONLY)->EnableWindow(TRUE);
	}

	if(m_nCardOnlyTimeZoneID == 0)
	{
		GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_ONLY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTP_READER_ESCORT_CARD_ONLY)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTP_READER_STAN_CARD_ONLY)->EnableWindow(FALSE);
	}
	else if(m_nCardOnlyTimeZoneID > 0)
	{
		GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_ONLY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CTP_READER_ESCORT_CARD_ONLY)->EnableWindow(TRUE);
		GetDlgItem(IDC_CTP_READER_STAN_CARD_ONLY)->EnableWindow(TRUE);
	}
}

void CDlgReaderTimeZone::OnPriorityChanged()
{
	UpdateData( TRUE );
}

void CDlgReaderTimeZone::DisableAllControls()
{
	GetDlgItem(IDC_CTP_PANEL_HID)->EnableWindow(FALSE);

	GetDlgItem(IDC_CTP_READER_STAN_CARD_AND_PIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_STAN_CARD_OR_PIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_STAN_PIN_ONLY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_STAN_CARD_ONLY)->EnableWindow(FALSE);

	GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_AND_PIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_OR_PIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_SUPERVISOR_PIN_ONLY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_ONLY)->EnableWindow(FALSE);

	GetDlgItem(IDC_CTP_READER_ESCORT_CARD_AND_PIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_ESCORT_CARD_OR_PIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_ESCORT_PIN_ONLY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_ESCORT_CARD_ONLY)->EnableWindow(FALSE);

	GetDlgItem(IDC_CTP_PANEL_COMBO_AD_READER_DISABLE_DOOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_PANEL_COMBO_AD_READER_LOCK)->EnableWindow(FALSE);	
	GetDlgItem(IDC_CTP_PANEL_COMBO_AD_READER_CARD_AND_PIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_PANEL_COMBO_AD_READER_CARD_OR_PIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_PANEL_COMBO_AD_READER_PIN_ONLY)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTP_PANEL_COMBO_AD_READER_CARD_ONLY)->EnableWindow(FALSE);
}

void CDlgReaderTimeZone::HideFewControls()
{
	GetDlgItem(IDC_CTP_READER_STAN_CARD_AND_PIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_STAN_CARD_OR_PIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_STAN_PIN_ONLY)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_STAN_CARD_ONLY)->ShowWindow(FALSE);

	GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_AND_PIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_OR_PIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_SUPERVISOR_PIN_ONLY)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_SUPERVISOR_CARD_ONLY)->ShowWindow(FALSE);

	GetDlgItem(IDC_CTP_READER_ESCORT_CARD_AND_PIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_ESCORT_CARD_OR_PIN)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_ESCORT_PIN_ONLY)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_ESCORT_CARD_ONLY)->ShowWindow(FALSE);

	GetDlgItem(IDC_CTP_READER_STANDARD)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_SUPERVISOR)->ShowWindow(FALSE);
	GetDlgItem(IDC_CTP_READER_ESCORT)->ShowWindow(FALSE);	
}

