// testmfcdll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;

static char *str = new char[1000];
int _tmain(int argc, _TCHAR* argv[])
{
	HINSTANCE hDllInst = LoadLibraryA("mfcdll.dll");

	if(hDllInst)

	{
		typedef void (__cdecl *GenQRCode)(bool ,const char* , const char* , const char* , const char* ,const char*, float , char* );

		GenQRCode function = NULL; // youFuntionNameAlias 函数别名

		function = (GenQRCode)GetProcAddress

			(hDllInst,"GenQRCode");




		// youFuntionName 在DLL中声明的函数名

		if(function)

		{
			char* mchtCode = new char[20];
			do{
				
				//char* operNo=new char[20];
				//char* machineCode=new char[20];
				//char* transactCode=new char[20];
				//float amount=0;
				
				cout<<"输入商户号"<<endl;
				cin.getline(mchtCode,20);
				if(strcmp("",mchtCode)==0){
					break;
				}
				
				/*
				cout<<"输入操作员代码"<<endl;
				cin.getline(operNo,20);
				
				cout<<"输入款机号"<<endl;
				cin.getline(machineCode,20);
				
				cout<<"输入流水号"<<endl;
				cin.getline(transactCode,20);
				
				cout<<"输入金额"<<endl;
				cin>>amount;
				cin.ignore(1);
				*/
				
				char* path=new char[256];
				memset(path,0,256);
				//function(true,mchtCode,operNo,machineCode,transactCode,"",amount,path);
				function(true,mchtCode,"","","","",0,path);
				printf("path:%s\n",path);
				delete[] path;
			}while(true);
		}

		FreeLibrary(hDllInst);



	}


	return 1;
}

