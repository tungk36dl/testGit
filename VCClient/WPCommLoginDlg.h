#if !defined(AFX_WPCOMMLOGINDLG_H__BAE93913_47B8_4476_863C_2C6BBADEFAF3__INCLUDED_)
#define AFX_WPCOMMLOGINDLG_H__BAE93913_47B8_4476_863C_2C6BBADEFAF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WPCommLoginDlg.h : header file
//
#include "VCClient.h"
#include "VCClientDlg.h"
#include "DlgProxy.h"
#include "Protocol.h"
/////////////////////////////////////////////////////////////////////////////
// CWPCommLoginDlg dialog

class CWPCommLoginDlg : public CDialog
{

// Construction
public:

	void LoadDomains();
	//No Calling without the Parent -- Guru
	CWPCommLoginDlg(CWnd* pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWPCommLoginDlg)
	enum { IDD = IDD_LOGIN_DIALOG };
	CString	m_strMacName;
	CString	m_strPassword;
	CString	m_strUname;
	CString m_strDomain;
	BOOL m_bLogin;
	CComboBox m_CmbDomain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWPCommLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CVCClientDlg*	m_pParent; // For holding the Main Dialog and hence the connection

	// Generated message map functions
	//{{AFX_MSG(CWPCommLoginDlg)
	afx_msg void OnLogin();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WPCOMMLOGINDLG_H__BAE93913_47B8_4476_863C_2C6BBADEFAF3__INCLUDED_)
