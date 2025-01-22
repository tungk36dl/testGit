#if !defined(AFX_DLGADVCONTROL_H__538F3BD1_3AF6_49BB_B209_9A4735799FD5__INCLUDED_)
#define AFX_DLGADVCONTROL_H__538F3BD1_3AF6_49BB_B209_9A4735799FD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgADVControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgADVControl dialog

#include "VCClientDlg.h"

class CDlgADVControl : public CDialog
{
// Construction
public:
	CDlgADVControl(CWnd* pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgADVControl)
	enum { IDD = IDD_ADV_CONTROL_DLG };
	CComboBox	m_ComboPro3kDoorMode;
	CComboBox	m_ComboDoorMode;
	long	m_lTPulseTime;
	int		m_iTPulseUnit;
	long	m_lPointHID;
	CVCClientDlg*	m_pParent; // For holding the Main Dialog and hence the connection
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgADVControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgADVControl)
	afx_msg void OnBtnLock();
	afx_msg void OnBtnUnlock();
	afx_msg void OnBtnShunt();
	afx_msg void OnBtnUnshunt();
	afx_msg void OnBtnEnergize();
	afx_msg void OnBtnDeenergize();
	afx_msg void OnBtnPulse();
	afx_msg void OnBtnRestoreToTz();
	afx_msg void OnBtnTimedpulse();
	afx_msg void OnBtnDoormode();
	afx_msg void OnBtnGetNxdoormode();
	afx_msg void OnBtnSetNxdoormode();
	afx_msg void OnBtnACRMode();
	afx_msg void OnBtnDoorStatus();
	afx_msg void OnBtnAcrMode_PRO3000();
	afx_msg void OnBtnDoormode_PRO3000();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADVCONTROL_H__538F3BD1_3AF6_49BB_B209_9A4735799FD5__INCLUDED_)
