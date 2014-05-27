// testcurl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "curl.h"
#include <string>
using namespace std;


size_t FuncCallBack1(char *data, size_t size, size_t nmemb, string *writerData)
{
	size_t sizes = size * nmemb;
	if (NULL == data)
		return 0;
	writerData->append(data);
	LPWSTR str = new WCHAR[1024];
	MultiByteToWideChar(936,MB_COMPOSITE,writerData->c_str(),-1,str,1024);
	printf("%s\n",writerData->c_str());
	//m_static_label.SetWindowText(str);
	return sizes;
}




void test()
{
	// TODO: Add your control notification handler code here
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if( curl ) {
		string RevBuff;
		printf("init");
		curl_easy_setopt(curl,CURLOPT_HTTPGET,1);
		//curl_easy_setopt(curl,CURLOPT_VERBOSE,1);
		curl_easy_setopt( curl, CURLOPT_URL, "http://www.hsltech.com");
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&RevBuff);    //设置接收数据的缓冲区，此时一定要设置回调函数来对数据进行处理
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, FuncCallBack1);  
		res = curl_easy_perform( curl );
		curl_easy_cleanup( curl );

	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	test();
	scanf("%c");
	return 0;
}

