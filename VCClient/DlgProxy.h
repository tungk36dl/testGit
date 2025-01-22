// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__1C988DA2_BBCE_49CD_81F5_AC474FA6C48E__INCLUDED_)
#define AFX_DLGPROXY_H__1C988DA2_BBCE_49CD_81F5_AC474FA6C48E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVCClientDlg;

/////////////////////////////////////////////////////////////////////////////
// CVCClientDlgAutoProxy command target

class CVCClientDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CVCClientDlgAutoProxy)

	CVCClientDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CVCClientDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVCClientDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CVCClientDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CVCClientDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CVCClientDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CVCClientDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__1C988DA2_BBCE_49CD_81F5_AC474FA6C48E__INCLUDED_)
