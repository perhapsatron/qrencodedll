// mfcdll.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"

#include "mfcdll.h"
#include "Resource.h"
#include <Windows.h>
#include "qrencode.h"
#include <atlimage.h>
#include "PicDisplay.h"
#include "curl.h"
#include <locale.h>
#include "localconfig.h"

#include "Base64.h"
#include "sha1.h"
#include "Signature.h"
#include "VerifyCodeRequest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "qrenc.c"

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CmfcdllApp

BEGIN_MESSAGE_MAP(CmfcdllApp, CWinApp)
END_MESSAGE_MAP()


void test();
// CmfcdllApp construction

CmfcdllApp::CmfcdllApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CmfcdllApp object

CmfcdllApp theApp;


BOOL CALLBACK DlgProc(HWND hDlg, UINT message,	WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_CLOSE:
		DestroyWindow(hDlg);
		//hwndDLG = NULL;
		return TRUE;
	}
	return FALSE;
}

// CmfcdllApp initialization

BOOL CmfcdllApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}


bool GenQRCode (bool showPic,const char* mchtCode, const char* operNo, const char* machineCode, const char* transactCode, const char* timeStamp, float amount,char* returnPath){
	string code;
	code.append("http://logmonitor.hsltech.com/wxm-pay-api-demo.html");
	code.append("?mchtCode=");
	code.append(mchtCode);
	code.append("&operNo=");
	code.append(operNo);
	code.append("&machineCode=");
	code.append(machineCode);
	code.append("&transactCode=");
	code.append(transactCode);
	code.append("&amount=");
	char value[256];
	memset(value,0,256);
	snprintf(value,256,"%f",amount);
	code.append(value);
	code.append("&timestamp=");
	code.append(timeStamp);
	/*unsigned char* sign = new unsigned char[21];
	memset(sign,'\0',21);
	unsigned char* key = (unsigned char*)APPKEY;
	sha1_hmac(key,strlen(APPKEY),(unsigned char*)code.c_str(),code.size(),sign);

	int nwlen = MultiByteToWideChar(CP_UTF8,0,code.c_str(),-1,NULL,0);
	wchar_t *pwbuf = new wchar_t[nwlen+1];
	memset(pwbuf,0,nwlen*2+2);

	MultiByteToWideChar(CP_UTF8,0,code.c_str(),code.length(),pwbuf,nwlen);
	int nlen = WideCharToMultiByte(CP_ACP,0,pwbuf,-1,NULL,NULL,NULL,NULL);

	char * pbuf = new char[nlen+1];
	memset(pbuf,0,nlen+1);

	WideCharToMultiByte(CP_ACP,0,pwbuf,nwlen,pbuf,nlen,NULL,NULL);

	ZBase64 base64;
	string out = base64.Encode((unsigned char*)sign,strlen((char*)sign));
	printf("base64:%s\n",out);*/

	/*
	unsigned char* sign = new unsigned char[20];
	unsigned char* key = (unsigned char*)APPKEY;
	unsigned char* input = (unsigned char*)code.c_str();
	sha1_hmac(key,strlen((char*)key),input,strlen((char*)input),sign);
	//unsigned char* key = (unsigned char*)_T("citylife@2013#ec");
	//unsigned char* input = (unsigned char*)_T("http://logmonitor.hsltech.com/wxm-pay-api-demo.html");
	//sha1_hmac(key ,sizeof("ctylife@2013#ec"),input,sizeof("http://logmonitor.hsltech.com/wxm-pay-api-demo.html"),sign);
	
	printf("sizeof input:%d\n",code.length()*sizeof(char));
	printf("code:%s\n",code);
	printf("sha1mac:%s\n",sign);*/

	test();
	
	QRcode *qrCode = QRcode_encodeString(code.c_str(),3,QR_ECLEVEL_M,QR_MODE_KANJI,1);
	code.clear();
	string path ;
	path.append(mchtCode);
	path.append(operNo);
	path.append(machineCode);
	path.append(transactCode);
	path.append(".png");
	writePNG(qrCode,path.c_str());
	QRcode_free(qrCode);
	memset(returnPath,0,path.length());
	strcpy(returnPath,path.c_str());
	//if(showPic){
	//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//	PicDisplay display;
	//	display.setPath(CString(path.c_str()));
	//	display.DoModal();
	//}
	return true;
}


void Say(char* szWords,int nLen){
	
	//dialog.GetDlgItem
	QRcode *code = QRcode_encodeString(szWords,1,QR_ECLEVEL_H,QR_MODE_KANJI,1);
	writePNG(code,"test.png");
	//CDialog cdialog = CDialog(IDD_DIALOG1);
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	PicDisplay display;
	display.setPath(CString("test.png"));
	display.DoModal();
		
	//CImage image;
	//image.Load(_T("test.png"));
	//HBITMAP hbmp=image.Detach();
	//dialog.m_pictureControl.SetBitmap(hbmp);
	//cdialog.DoModal();
	//pWnd->SetWindowPos(NULL,0,0,100,50,SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER);
	//MessageBoxA(NULL,"sfs","",0);
	//dialog.DoModal();
	return;
}


size_t FuncCallBack(char *data, size_t size, size_t nmemb, string *writerData)
{
	size_t sizes = size * nmemb;
	if (NULL == data)
		return 0;
	writerData->append(data);
	LPWSTR str = new WCHAR[1024];
	MultiByteToWideChar(936,MB_COMPOSITE,writerData->c_str(),-1,str,1024);
	printf("%s",data);
	//m_static_label.SetWindowText(str);
	return sizes;
}

void testmap(){
	map<string,string> m;
	m["sdfsfs"]="123";
	m["1dsfsfsf"]="234";
	string signature;
	sign(m,"sdfsdf",signature);
}

void callback(bool success, string* result){
	//MessageBoxA(NULL,result->c_str(),NULL,0);
	printf("result:%s\n",result->c_str());
}

void testRequest(){
	VerifyCodeRequest request;
	/*type	是	值:telephone_register,生成验证码类型
telephone	是	电话号码
app_key	是	api的key*/
	printf("callback %x",&callback);
	request.addParam("type",string("telephone_register"));
	request.addParam("telephone",string("13263403367"));
	request.addParam("app_key",string("123456"));
	request.setQueryDuration(15);
	string result;
	request.setCallback(callback,&result);
	request.start();
}

void testCurl()
{
	// TODO: Add your control notification handler code here
	CURLcode res;
	CURL *curl = curl_easy_init();
	if( curl ) {
		string RevBuff;
		curl_easy_setopt(curl,CURLOPT_HTTPGET,1);
		curl_easy_setopt( curl, CURLOPT_URL, "http://api.hsltech.com/verifycode?type=telephone_register&telephone=18758021576");
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, (void *)&RevBuff);    //设置接收数据的缓冲区，此时一定要设置回调函数来对数据进行处理
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, FuncCallBack);  
		printf("start\n");
		res = curl_easy_perform( curl );
		printf("res:%d\n",res);
		curl_easy_cleanup( curl );
	}
	//CDialog::OnOK();
}

void test(){
	//testCurl();
	testRequest();
}