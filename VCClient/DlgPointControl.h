#if !defined(AFX_DLGPOINTCONTROL_H__07C1F36C_4E5C_4A75_93C0_49414D9BC182__INCLUDED_)
#define AFX_DLGPOINTCONTROL_H__07C1F36C_4E5C_4A75_93C0_49414D9BC182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPointControl.h : header file
//
#include "VCClientDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgPointControl dialog

class CDlgPointControl : public CDialog
{
// Construction
public:
	//Parental Guidance Advised - No Calling without Parents -- Guru
	CDlgPointControl(CWnd* pParent);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPointControl)
	enum { IDD = IDD_CONTROL_DIALOG };
	BOOL	m_bAccessArea;
	BOOL	m_bAccessLevels;
	BOOL	m_bPanelConfig;
	BOOL	m_bCards;
	BOOL	m_bCardFormats;
	BOOL	m_bCmdFiles;
	BOOL	m_bTZRefresh;
	BOOL	m_bGroups;
	BOOL	m_bHolidays;
	BOOL	m_bInputScanCodes;
	BOOL	m_bInputs;
	BOOL	m_bMCPGroups;
	BOOL	m_bOutputs;
	BOOL	m_bProcedures;
	BOOL	m_bReaderLED;
	BOOL	m_bDateTime;
	BOOL	m_bSIO;
	BOOL	m_bTimezones;
	BOOL	m_bTriggers;
	long	m_nPanelHID;
	BOOL	m_bMCBConfig;
	BOOL	m_bPSeriesPanel;
	CVCClientDlg*	m_pParent; // For holding the Main Dialog and hence the connection
	int		m_nPanelType;
	short	m_nBufferMode;
	long	m_lHIDType;

	// For P-Series Panel Encryption Option -- Guru
	BOOL	m_bMCBEncryption;

	long	m_lPanelType;
	long	m_lDoorHID;
	long	m_lDoorPointID;
	long	m_lTZID;

	BOOL	m_bSelectAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPointControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPointControl)
	afx_msg void OnBtnInitStart();
	afx_msg void OnBtnInitEnd();
	afx_msg void OnRadioNSPanels();
	afx_msg void OnRadioPSeries();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPanelBuffer();
	afx_msg void OnBtnPanelUnbuffer();
	afx_msg void OnBtnExecuteDoorScdl();
	afx_msg void OnBtnSelectAll();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void DisableSomeControls();
	void CheckPanelType();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOINTCONTROL_H__07C1F36C_4E5C_4A75_93C0_49414D9BC182__INCLUDED_)
