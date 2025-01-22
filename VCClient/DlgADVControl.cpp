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

  File Name     : DlgADVControl.cpp

  Project		: WP-CS API Test Client

  Originator	: Sathish Guru V

  APPLICATION	: WP-CS API Communication server Test Client

  MODULE		: 

  PURPOSE		: Dialog of Having the Test of Contolling all ADVs other than Panels

  REVISION HISTORY:

  Rev	   Date		 Programmer            Comment
  ----    --------	--------------   ---------------------
  1.0	 29 Nov  2011	Sathish Guru	Initial Version
  1.1	 02 Jan	 2012	Sathish Guru	Prototype Bugfixes
  1.2	 16 Feb	 2012	Sathish Guru	Added NX Card Mode Error Codes
  1.32	 8 Apr	 2017	Vellai			PRO3000 - HBAC API Implementation


/********************************************************************************/
#include "stdafx.h"
#include "vcclient.h"
#include "DlgADVControl.h"
#include <comutil.h> // Cho _variant_t

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgADVControl dialog

//Parental Guidance Advised - No Calling without Parents -- Guru
CDlgADVControl::CDlgADVControl(CWnd* pParent)
	: CDialog(CDlgADVControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgADVControl)
	m_lTPulseTime = 0;
	m_iTPulseUnit = 0;
	m_lPointHID = 0;
	m_pParent = (CVCClientDlg *)pParent;
	//}}AFX_DATA_INIT
}


void CDlgADVControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgADVControl)
	DDX_Control(pDX, IDC_COMBO_DOORMODE2, m_ComboPro3kDoorMode);
	DDX_Control(pDX, IDC_COMBO_DOORMODE, m_ComboDoorMode);
	DDX_Text(pDX, IDC_EDIT_TP, m_lTPulseTime);
	DDX_Text(pDX, IDC_EDIT_TP_UNIT, m_iTPulseUnit);
	DDX_Text(pDX, IDC_EDIT_HID, m_lPointHID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgADVControl, CDialog)
	//{{AFX_MSG_MAP(CDlgADVControl)
	ON_BN_CLICKED(IDC_BTN_LOCK, OnBtnLock)
	ON_BN_CLICKED(IDC_BTN_UNLOCK, OnBtnUnlock)
	ON_BN_CLICKED(IDC_BTN_SHUNT, OnBtnShunt)
	ON_BN_CLICKED(IDC_BTN_UNSHUNT, OnBtnUnshunt)
	ON_BN_CLICKED(IDC_BTN_ENERGIZE, OnBtnEnergize)
	ON_BN_CLICKED(IDC_BTN_DEENERGIZE, OnBtnDeenergize)
	ON_BN_CLICKED(IDC_BTN_PULSE, OnBtnPulse)
	ON_BN_CLICKED(IDC_BTN_TZ, OnBtnRestoreToTz)
	ON_BN_CLICKED(IDC_BTN_TIMEDPULSE, OnBtnTimedpulse)
	ON_BN_CLICKED(IDC_BTN_DOORMODE, OnBtnDoormode)
	ON_BN_CLICKED(IDC_BTN_GET_NXDOORMODE, OnBtnGetNxdoormode)
	ON_BN_CLICKED(IDC_BTN_SET_NXDOORMODE, OnBtnSetNxdoormode)
	ON_BN_CLICKED(IDC_BTN_ACR_MODE, OnBtnACRMode)
	ON_BN_CLICKED(IDC_BTN_DOOR_STATUS, OnBtnDoorStatus)
	ON_BN_CLICKED(IDC_BTN_ACR_MODE2, OnBtnAcrMode_PRO3000)
	ON_BN_CLICKED(IDC_BTN_DOORMODE2, OnBtnDoormode_PRO3000)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgADVControl message handlers

void CDlgADVControl::OnBtnLock() 
{
	UpdateData();
	m_pParent->m_pServer->EntryPointLockByHID(m_lPointHID);
}

void CDlgADVControl::OnBtnUnlock() 
{
	UpdateData();
	m_pParent->m_pServer->EntryPointUnLockByHID(m_lPointHID);
}

void CDlgADVControl::OnBtnShunt() 
{
	UpdateData();
	m_pParent->m_pServer->AlarmShuntByHID(m_lPointHID);
}

void CDlgADVControl::OnBtnUnshunt() 
{
	UpdateData();
	m_pParent->m_pServer->AlarmUnShuntByHID(m_lPointHID);
}

void CDlgADVControl::OnBtnEnergize() 
{
	UpdateData();
	m_pParent->m_pServer->Energize(m_lPointHID);
}

void CDlgADVControl::OnBtnDeenergize() 
{
	UpdateData();
	m_pParent->m_pServer->DeEnergize(m_lPointHID);
}

void CDlgADVControl::OnBtnPulse() 
{
	UpdateData();
	m_pParent->m_pServer->PulseByHID(m_lPointHID);
}

void CDlgADVControl::OnBtnRestoreToTz() 
{
	UpdateData();
	m_pParent->m_pServer->RestoreTZByHID(m_lPointHID);
}

void CDlgADVControl::OnBtnTimedpulse() 
{
	UpdateData();
	if (( m_iTPulseUnit <0 ) || ( m_iTPulseUnit >2 ) )
		AfxMessageBox(_T("Please enter valid pulse time unit"));
	m_pParent->m_pServer->TimedPulseByHID(m_lPointHID,m_iTPulseUnit,m_lTPulseTime);
}

void CDlgADVControl::OnBtnDoormode() 
{
	int iSelectedRow = m_ComboDoorMode.GetCurSel();
	UpdateData(TRUE);
	m_pParent->m_pServer->DoorModeByHID( m_lPointHID,(iSelectedRow+1) );
}

void CDlgADVControl::OnBtnGetNxdoormode() 
{
	UpdateData();
	if(m_lPointHID == 0)
	{
		AfxMessageBox(_T("Nothing Returned"));
		return;
	}
	_variant_t pDoorInfo;
	pDoorInfo.Clear();
	pDoorInfo.vt = VT_EMPTY;
	m_pParent->m_pServer->GetNetAXSDoorModeByHID(m_lPointHID, &pDoorInfo);
	if(pDoorInfo.vt == VT_EMPTY)
	{
		AfxMessageBox(_T("Nothing Returned"));
		return;
	}
	if( pDoorInfo.vt & VT_DISPATCH)
	{
		INetAXSDoorInfoPtr pIDoorInfo(pDoorInfo.pdispVal);
		CDlgReaderTimeZone dlg(NULL, m_lPointHID, FALSE, pIDoorInfo);
		dlg.DoModal();
	}
}

void CDlgADVControl::OnBtnSetNxdoormode() 
{
	HRESULT hRes;
	UpdateData();
	if(m_lPointHID == 0)
	{
		AfxMessageBox(_T("Nothing Returned"));
		return;
	}

	INetAXSDoorInfoPtr pDoorInfo = NULL;
	_variant_t vDoorInfo;

	hRes = m_pParent->m_pServer->GetNetAXSDoorModeByHID(m_lPointHID, &vDoorInfo);
	if(FAILED(hRes))
	{
		AfxMessageBox(_T("Error"));
		return;
	}
	else if (vDoorInfo.vt == VT_EMPTY || vDoorInfo.vt == VT_NULL)
	{
		AfxMessageBox(_T("Nothing Returned"));
		return;
	}


	pDoorInfo = vDoorInfo.pdispVal;

	if(!FAILED(hRes))
	{
		//INetAXSDoorInfoPtr pDoorInfo(vDoorInfo.pdispVal);
		CDlgReaderTimeZone dlg(NULL, m_lPointHID, TRUE, pDoorInfo);
		if(dlg.DoModal()==IDOK)
		{
			pDoorInfo->put_DisableDoorTimezone(dlg.m_nDisableTimeZoneID);
			pDoorInfo->put_LockdownReaderTimezone(dlg.m_nLockTimeZoneID);
			pDoorInfo->put_CardOnlyTimezone(dlg.m_nCardOnlyTimeZoneID);
			pDoorInfo->put_PINOnlyTimezone(dlg.m_nPinOnlyTimeZoneID);
			pDoorInfo->put_CardAndPINTimezone(dlg.m_nCardAndPinTimeZoneID);
			pDoorInfo->put_CardOrPINTimezone(dlg.m_nCardOrPinTimeZoneID);
			pDoorInfo->put_CardOnlyPriority(dlg.m_nCardOnlyPriority);
			pDoorInfo->put_PINOnlyPriority(dlg.m_nPinOnlyPriority);
			pDoorInfo->put_CardAndPINPriority(dlg.m_nCardAndPinPriority);
			pDoorInfo->put_CardOrPINPriority(dlg.m_nCardOrPinPriority);
			long plStatus;
			HRESULT hRes = m_pParent->m_pServer->SetNetAXSDoorModeByHID(m_lPointHID, pDoorInfo, &plStatus);
			if(FAILED(hRes))
			{
				AfxMessageBox(_T("Setting Door Mode Failed"));
				return;
			}
			CString errCode;
			errCode.Format(_T("Return Status: %ld"), plStatus);
			CString errMsg;
			switch(plStatus)
			{
				case 0:
					errMsg = _T("Door Mode Updated Successfully");
					break;
				case 1:
					errMsg = _T("Door Mode Update Failed");
					break;
				case 2:
					errMsg = _T("Invalid HID");
					break;;
				case 3:
					errMsg = _T("Empty DoorInfo Object");
					break;
				case 4:
					errMsg = _T("Invalid Disable Door Timezone");
					break;
				case 5:
					errMsg = _T("Invalid Lockdown Reader Timezone");
					break;
				case 6:
					errMsg = _T("Invalid Card Only Timezone");
					break;
				case 7:
					errMsg = _T("Invalid PIN Only Timezone");
					break;
				case 8:
					errMsg = _T("Invalid Card and PIN Timezone");
					break;
				case 9:
					errMsg = _T("Invalid Card or PIN Timezone");
					break;
				case 10:
					errMsg = _T("Invalid Card Only Priority");
					break;
				case 11:
					errMsg = _T("Invalid PIN Only Priority");
					break;
				case 12:
					errMsg = _T("Invalid Card and PIN Priority");
					break;
				case 13:
					errMsg = _T("Invalid Card or PIN Priority");
					break;
			}
			AfxMessageBox(errCode+"\n"+errMsg);
		}
	}
}

void CDlgADVControl::OnBtnACRMode()
{
	UpdateData();
	int nMode;
	m_pParent->m_pServer->GetDefaultACRMode(m_lPointHID,&nMode);
	if(-1 == nMode)
	{
		AfxMessageBox(_T("Wrong HID"));
		return;
	}
	CString arrACRMode[] = { 
								_T("Disable the Reader"),
								_T("Unlock (unlimited access)"),
								_T("Locked (no access, Egress active)"),
								_T("Site Code only"),
								_T("Card only"),
								_T("PIN only"),
								_T("Card and PIN"),
								_T("Card or PIN") 
							};
	AfxMessageBox(arrACRMode[nMode-1]);

}


void CDlgADVControl::OnBtnDoorStatus() 
{
	long lDoorStatus;

	UpdateData(TRUE);
	
	HRESULT hr = m_pParent->m_pServer->GetDoorStatus2(m_lPointHID, &lDoorStatus);
	
	CString sMsg, sFormat, sTemp;
	sFormat = _T("%ld : %s");

	switch(lDoorStatus)
	{
		case 0:
			sTemp = _T("Door Closed");
			break;
		case 1:
			sTemp = _T("Door Opened");
			break;
		case -1:
			sTemp = _T("Door Unknown");
			break;
	}
	sMsg.Format(sFormat, lDoorStatus, sTemp);
	AfxMessageBox(sMsg);
}
//Get DoorMode of PRO3000 - HBAC Panel
void CDlgADVControl::OnBtnAcrMode_PRO3000() 
{
	UpdateData();
	int nMode;
	m_pParent->m_pServer->GetDefaultACRMode(m_lPointHID,&nMode);
	if(-1 == nMode)
	{
		AfxMessageBox(_T("Wrong HID"));
		return;
	}
	CString arrACRMode[] = { 
								_T("Disable the Reader"),
								_T("Unlock (unlimited access)"),
								_T("Locked (no access, Egress active)"),								
								_T("Card only"),
								_T("PIN only"),
								_T("Card and PIN"),
								_T("Card or PIN") 
							};
	AfxMessageBox(arrACRMode[(nMode)]);
	
}
//Set the selected DoorMode of PRO3000 - HBAC Panel
void CDlgADVControl::OnBtnDoormode_PRO3000() 
{
	int iSelectedRow = m_ComboPro3kDoorMode.GetCurSel();
	UpdateData(TRUE);
	m_pParent->m_pServer->DoorModeByHID( m_lPointHID,(iSelectedRow) );
}
