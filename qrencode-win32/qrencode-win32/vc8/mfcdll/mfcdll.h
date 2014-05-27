// mfcdll.h : main header file for the mfcdll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CmfcdllApp
// See mfcdll.cpp for the implementation of this class
//

class CmfcdllApp : public CWinApp
{
public:
	CmfcdllApp();

// Overrides
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
extern "C" bool _declspec(dllexport) GenQRCode (bool showPic,const char* mchtCode, const char* operNo, const char* machineCode, const char* transactCode, const char* timestamp, float amount, char* returnPath);