
// test dllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test dll.h"
#include "test dllDlg.h"
#include "afxdialogex.h"
#include "curl.h"
#include <cstringt.h>
#include <string>
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestdllDlg dialog


using namespace std;

CtestdllDlg::CtestdllDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestdllDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_static_text = _T("");
	//  m_text = _T("");
}

void CtestdllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, ID_STATIC, mStatic);
	//  DDX_Text(pDX, ID_STATIC, m_static_text);
	//  DDX_Control(pDX, ID_STATIC, m_static);
	//  DDX_Control(pDX, ID_STATIC, m_static);
	//  DDX_Control(pDX, ID_STATIC1, m_static);
	//  DDX_Text(pDX, IDC_EDIT1, m_text);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
}

BEGIN_MESSAGE_MAP(CtestdllDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CtestdllDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CtestdllDlg message handlers

BOOL CtestdllDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtestdllDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtestdllDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

size_t CtestdllDlg::GetContent( char *buffer, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE *)userdata;
	size_t return_size = fwrite(buffer, size, nmemb, fp);
	return return_size;
}

size_t CtestdllDlg::FuncCallBack(char *data, size_t size, size_t nmemb, string *writerData)
{
	
	size_t sizes = size * nmemb;
	if (NULL == data)
		return 0;
	writerData->append(data);
	BSTR bstrText = ::SysAllocString(L"Test"); 
	m_text.SetSysString(&bstrText);
	return sizes;
}


void CtestdllDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if( curl ) {
		string RevBuff;

		curl_easy_setopt(curl,CURLOPT_HTTPGET,1);
		curl_easy_setopt( curl, CURLOPT_URL, "www.baidu.com");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&RevBuff);    //设置接收数据的缓冲区，此时一定要设置回调函数来对数据进行处理
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CtestdllDlg::FuncCallBack);  
		res = curl_easy_perform( curl );
		curl_easy_cleanup( curl );

	}
	//CDialogEx::OnOK();
}


