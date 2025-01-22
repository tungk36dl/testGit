// VCClientDlg.h : header file
//
#include "ClientClass.h"
#include "DlgReaderTimezone.h"


#if !defined(AFX_VCCLIENTDLG_H__E0A1F026_6DA4_4870_B740_325C0C373B32__INCLUDED_)
#define AFX_VCCLIENTDLG_H__E0A1F026_6DA4_4870_B740_325C0C373B32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVCClientDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CVCClientDlg dialog

class CVCClientDlg : public CDialog
{
	DECLARE_DYNAMIC(CVCClientDlg);
	friend class CVCClientDlgAutoProxy;

// Construction
public:
	CVCClientDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CVCClientDlg();

// Dialog Data
	//{{AFX_DATA(CVCClientDlg)
	enum { IDD = IDD_VCCLIENT_DIALOG };
	CComboBox	m_ComboDoorMode;
	CListBox	m_LstDetails;
	CListBox	m_ctlListAlarm;
	CListCtrl	m_cLstStatus;
	CListCtrl	m_cLstEvent;
	long	m_lAlarmHID;
	long	m_lAlarmPointID;
	CString	m_strNote;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CVCClientDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CVCClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnRegister();
	afx_msg void OnBtnAck();
	afx_msg void OnBtnClear();
	afx_msg void OnBtnStatus();
	afx_msg void OnBtndetails();
	afx_msg void OnMenuPanelControl();
	afx_msg void OnMenuADVControl();
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuLogin();
	afx_msg void OnMenuLogout();
	afx_msg void OnMenuExit();
	afx_msg void OnBtnAddNote();
	afx_msg void OnLbnSelchangeListAlarm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public :
	IMTSCBServerPtr				m_pServer;		//Pointer to the Server (CommServer API)
	CComObject<CClientClass>*	m_pCallback;	//Pointer of Client to pass to the server
	HANDLE						m_hdlThread;	//Thread handle to spy on messages from the server

	BOOL						m_bLoggedIn;	//To hold the logged in status for the whole
	BSTR						b_transaction;
public :
	void AddToEventList(CString);				//Function for displaying events
	void AddToStatusList(CString);				//Function for displaying HID status
	//Helper
	CString GetFieldFromInput(const CString ,const CString );

private:
	int m_iEventItemNo;									
	int m_iStatusItemNo;
	CString m_strUser;
	CString m_strPswd;

private :
	void Register();
	void UnRegister();							// Unregistration of the client from the server
	void LoadColumnHeaders();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCCLIENTDLG_H__E0A1F026_6DA4_4870_B740_325C0C373B32__INCLUDED_)
