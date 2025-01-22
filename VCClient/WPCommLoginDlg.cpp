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

  File Name     : WPCommLoginDlg.cpp

  Project		: WP-CS API Test Client

  Originator	: Sathish Guru V

  APPLICATION	: WP-CS API Communication server Test Client

  MODULE		: 

  PURPOSE		: Login Dialog

  REVISION HISTORY:

  Rev	   Date		 Programmer            Comment
  ----    --------	--------------   ---------------------
  1.0	 29 Nov  2011	Sathish Guru	Initial Version
  1.1	 02 Jan	 2012	Sathish Guru	Prototype Bugfixes
  1.2	 16 Feb	 2012	Sathish Guru	Added dedicaed Login Error Messages
  1.3	 08 Aug  2013	Sathish Guru	Added the Logic for Loading the Domains for the Coke Build


/********************************************************************************/

#include "stdafx.h"
#include "vcclient.h"
#include "WPCommLoginDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWPCommLoginDlg dialog


CWPCommLoginDlg::CWPCommLoginDlg(CWnd* pParent)
	: CDialog(CWPCommLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWPCommLoginDlg)
	m_strMacName = _T("");
	m_strPassword = _T("");
	m_strUname = _T("");
	m_strDomain = _T("");
	m_bLogin = FALSE;
	m_pParent = (CVCClientDlg *)pParent;
	//}}AFX_DATA_INIT
}


void CWPCommLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWPCommLoginDlg)
	DDX_Text(pDX, IDC_MAC_NAME, m_strMacName);
	DDX_Text(pDX, IDC_PWD, m_strPassword);
	DDX_Text(pDX, IDC_UNAME, m_strUname);
	DDX_Text(pDX, IDC_DOMAINNAME, m_strDomain);
	//DDX_Control(pDX, IDC_CMBDOMAIN, m_CmbDomain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWPCommLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CWPCommLoginDlg)
	ON_BN_CLICKED(ID_LOGIN, OnLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CWPCommLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_CmbDomain.Clear();

	//LoadDomains();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CWPCommLoginDlg message handlers

void CWPCommLoginDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString sDomainName;

	int iSel = m_CmbDomain.GetCurSel();
	if(m_CmbDomain.GetCount() > 0 && iSel<0)
		return;
	if(iSel != CB_ERR) //To fix invalid parameter issue while login
		m_CmbDomain.GetLBText(iSel, sDomainName);
		
	VARIANT_BOOL pbResult;
	HRESULT hRes;
	
	try
	{
		
		
		hRes = CComObject<CClientClass>::CreateInstance(&(m_pParent->m_pCallback));
		
		hRes = m_pParent->m_pServer.CreateInstance("accw.MTSCBServer");
		
	}
	catch(...)
	{

		AfxMessageBox(_T("Login Fail Due to Unknown COM Failure"));
	}

	BSTR bstrUser = m_strUname.AllocSysString();
	BSTR bstrPswd = m_strPassword.AllocSysString();
	BSTR bstrDomain = m_strDomain.AllocSysString();
	
	// changed InitServer2 to InitServer do to COM API crash ----------praveen ....WPACT-228  

	if(m_strDomain == (_T("")))
	{
		hRes = m_pParent->m_pServer->InitServer(m_pParent->m_pCallback,3,bstrUser,bstrPswd, 1, &pbResult);
	}
	else	
	{
		hRes = m_pParent->m_pServer->InitServer2(m_pParent->m_pCallback,3,bstrUser,bstrPswd, bstrDomain, 1, &pbResult);
	
	}
	if(FAILED(hRes))
	{
	
		AfxMessageBox(_T("Login Fail Due to Unknown COM Failure"));
		
		try
		{
			if(m_pParent->m_pServer)
			{
				m_pParent->m_pServer->Release();
				m_pParent->m_pServer = NULL;
			}
		}
		catch(...)
		{}

		m_bLogin = FALSE;
	}
	else if(VARIANT_FALSE == pbResult)
	{
		AfxMessageBox(_T("Login Fail Due Invalid Credentials or\n WP DB Server Unavailable"));
		
		try
		{
			if(m_pParent->m_pServer)
			{
				m_pParent->m_pServer->Release();
				m_pParent->m_pServer = NULL;
			}
		}	
		catch(...)
		{}

		m_bLogin = FALSE;
	}
	else
		m_bLogin = TRUE;
	
	::SysFreeString(bstrUser);
	::SysFreeString(bstrPswd);
	::SysFreeString(bstrDomain);

	CDialog::OnOK();
}

void CWPCommLoginDlg::OnCancel() 
{
	
	m_pParent->m_bLoggedIn = FALSE;
	CDialog::OnCancel();
}


void CWPCommLoginDlg::LoadDomains()
{
	_variant_t vDomains;
	//IMTSCBServerPtr				pServer;
	
	vDomains.Clear();

	HRESULT hRes = m_pParent->m_pServer.CreateInstance("accw.MTSCBServer");
	if(FAILED(hRes))
	{
		return;
	}
	
	hRes = m_pParent->m_pServer->GetConfiguredWPDomains(&vDomains);
	
	if(FAILED(hRes) || vDomains.vt == VT_EMPTY)
	{
		AfxMessageBox(_T("No Domains or Logon without Domain Credentials"));
		
		m_pParent->m_pServer->Release();
              
		
		return;
	}
	
	long uBound =0 ;
	
	COleSafeArray sa(vDomains);
		
	sa.GetUBound(1,&uBound);
		
	UpdateData(TRUE);
	BSTR bstrDomain;
	for(long i =0 ;i <= uBound ; i++)
	{
			
		sa.GetElement(&i,(void*)&bstrDomain);
			
		CString sDomain = CString(bstrDomain);
			
		//AfxMessageBox(scard);
		m_CmbDomain.AddString(sDomain);
			
	}
	m_CmbDomain.SetCurSel(0);


	m_pParent->m_pServer->Release();
	
	m_pParent->m_pServer = NULL;
 
	UpdateData(FALSE);
}