// PicDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "mfcdll.h"
#include "PicDisplay.h"
#include "afxdialogex.h"
#include "curl.h"
#include <string>

using namespace std;


// PicDisplay dialog

IMPLEMENT_DYNAMIC(PicDisplay, CDialog)

static CString path;
static bool changed = true;

static CWnd *inst;
PicDisplay::PicDisplay(CWnd* pParent /*=NULL*/)
	: CDialog(PicDisplay::IDD, pParent)
{
	inst = this;
}

PicDisplay::~PicDisplay()
{
	inst = NULL;
}

void PicDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PICT1, m_pic);
	//DDX_Control(pDX, IDC_STATIC_LABEL, m_static_label);
}

BEGIN_MESSAGE_MAP(PicDisplay, CDialog)
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// PicDisplay message handlers


void PicDisplay::OnPaint()
{
	if(!changed)
		return;
	CPaintDC dc(&m_pic); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	CImage image;
	CString str(path);
	image.Load(str);
	
	RECT rect;
	
	m_pic.GetClientRect(&rect);
	image.Draw(dc,rect);

	ReleaseDC(&dc);
	changed = false;

}

void PicDisplay::setPath(CString str){
	path=str;
	changed = true;
	Invalidate();
}



void PicDisplay::OnMove(int x, int y)
{
	changed = true;
	CDialog::OnMove(x, y);

	// TODO: Add your message handler code here
}


void PicDisplay::OnSize(UINT nType, int cx, int cy)
{
	changed = true;
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

/*size_t FuncCallBack1(char *data, size_t size, size_t nmemb, string *writerData)
{
	size_t sizes = size * nmemb;
	if (NULL == data)
		return 0;
	writerData->append(data);
	LPWSTR str = new WCHAR[1024];
	MultiByteToWideChar(936,MB_COMPOSITE,writerData->c_str(),-1,str,1024);
	inst->GetDlgItem(IDC_STATIC_LABEL)->SetWindowText(str);
	//m_static_label.SetWindowText(str);
	return sizes;
}*/
/*
void PicDisplay::OnBnClickedOk()
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
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FuncCallBack);  
		res = curl_easy_perform( curl );
		curl_easy_cleanup( curl );

	}
	//CDialog::OnOK();
}*/




void PicDisplay::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	changed = true;
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
}


/*void PicDisplay::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	inst->GetDlgItem(IDC_STATIC_LABEL)->SetWindowText(_T("sfsfsf"));
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if( curl ) {
		string RevBuff;

		curl_easy_setopt(curl,CURLOPT_HTTPGET,1);
		curl_easy_setopt( curl, CURLOPT_URL, "www.baidu.com");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&RevBuff);    //设置接收数据的缓冲区，此时一定要设置回调函数来对数据进行处理
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FuncCallBack1);  
		res = curl_easy_perform( curl );
		curl_easy_cleanup( curl );

	}
}*/
