#if !defined(AFX_DLGREADERTIMEZONE_H__E5FE70FD_B613_4040_AC86_D3BC47AF7300__INCLUDED_)
#define AFX_DLGREADERTIMEZONE_H__E5FE70FD_B613_4040_AC86_D3BC47AF7300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgReaderTimeZone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgReaderTimeZone dialog

class CDlgReaderTimeZone : public CDialog
{
// Construction
public:
	CDlgReaderTimeZone(CWnd* pParent = NULL, long iHID = 0, BOOL bEdit = FALSE, INetAXSDoorInfo *pDoorInfo = NULL);   // standard constructor
	void LoadData(INetAXSDoorInfo* pData);
// Dialog Data
	//{{AFX_DATA(CDlgReaderTimeZone)
	enum { IDD = IDD_CTP_ENTRANCE_TIMEZONE };
	long			m_nHID;
	int			m_nDeviceType;
	long			m_nLockTimeZoneID;
	long			m_nDisableTimeZoneID;
	long			m_nCardAndPinTimeZoneID;
	long			m_nCardOrPinTimeZoneID;
	long			m_nPinOnlyTimeZoneID;
	long			m_nCardOnlyTimeZoneID;
	int			m_nHWDeviceID;
	int			m_nHWDeviceSubID2;
	int			m_nCardAndPinPriority;
	int		    m_nCardOrPinPriority;
	int		    m_nPinOnlyPriority;
	int		    m_nCardOnlyPriority;
	BOOL		m_bEdit;
	long	m_nDisableTimeZoneID1;
	//}}AFX_DATA


	virtual ~CDlgReaderTimeZone();
private:
	void EnableCardPriorityControls(int m_nCardAndPinTimeZoneID, int m_nCardOrPinTimeZoneID,
									int	m_nPinOnlyTimeZoneID, int m_nCardOnlyTimeZoneID);
	void OnPriorityChanged();

	void DisableAllControls();

	void HideFewControls();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	// Generated message map functions
	//{{AFX_MSG(CDlgReaderTimeZone)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREADERTIMEZONE_H__E5FE70FD_B613_4040_AC86_D3BC47AF7300__INCLUDED_)
