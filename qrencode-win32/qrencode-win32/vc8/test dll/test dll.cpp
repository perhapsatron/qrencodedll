
// test dll.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "test dll.h"
#include "test dllDlg.h"
#include "curl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestdllApp

BEGIN_MESSAGE_MAP(CtestdllApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CtestdllApp construction

CtestdllApp::CtestdllApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

void test();

// The one and only CtestdllApp object

CtestdllApp theApp;


// CtestdllApp initialization

BOOL CtestdllApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CtestdllDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		test();
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

size_t FuncCallBack(char *data, size_t size, size_t nmemb, string *writerData)
{
	size_t sizes = size * nmemb;
	MessageBoxA(NULL,writerData->c_str(),"",0);
	if (NULL == data)
		return 0;
	writerData->append(data);
	LPWSTR str = new WCHAR[1024];
	MultiByteToWideChar(936,MB_COMPOSITE,writerData->c_str(),-1,str,1024);
	MessageBoxA(NULL,writerData->c_str(),"",0);
	//m_static_label.SetWindowText(str);
	return sizes;
}

void test()
{
	// TODO: Add your control notification handler code here
	CURLcode res;
	CURL *curl = curl_easy_init();
	if( curl ) {
		string RevBuff;

		curl_easy_setopt(curl,CURLOPT_HTTPGET,1);
		curl_easy_setopt( curl, CURLOPT_URL, "www.google.com");
		curl_easy_setopt( curl, CURLOPT_WRITEDATA, (void *)&RevBuff);    //设置接收数据的缓冲区，此时一定要设置回调函数来对数据进行处理
		curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, FuncCallBack);  
		printf("start\n");
		res = curl_easy_perform( curl );
		printf("res:%d\n",res);
		curl_easy_cleanup( curl );
	}
	//CDialog::OnOK();
}

