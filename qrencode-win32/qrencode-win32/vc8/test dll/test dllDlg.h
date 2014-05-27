
// test dllDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <string>

using namespace std;
// CtestdllDlg dialog
class CtestdllDlg : public CDialogEx
{
// Construction
public:
	CtestdllDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTDLL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	CStatic mStatic;
//	CString m_static_text;
	size_t CtestdllDlg::GetContent( char *buffer, size_t size, size_t nmemb, void *userdata);
	size_t CtestdllDlg::FuncCallBack(char *data, size_t size, size_t nmemb, string *writerData);
//	CStatic m_static;
//	CStatic m_static;
//	CStatic m_static;
//	CString m_text;
	CEdit m_edit1;
};
