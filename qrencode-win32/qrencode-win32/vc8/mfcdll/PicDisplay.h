#pragma once

#include <string>
using namespace std;

// PicDisplay dialog

class PicDisplay : public CDialog
{
	DECLARE_DYNAMIC(PicDisplay)

public:
	PicDisplay(CWnd* pParent = NULL);   // standard constructor
	virtual ~PicDisplay();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void setPath(CString path);
	CStatic m_pic;
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//size_t FuncCallBack(char *data, size_t size, size_t nmemb, string *writerData);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnBnClickedOk();
};
