#include "ZPRequest.h"
#include "Signature.h"
#include "curl.h"
#include <list>
#include "jansson.h"
#include "ZPRequest.h"
#include "localconfig.h"

using namespace std;

void ZPRequest::addParam(string key, string value){
	params[key] = value;
}
void ZPRequest::addParam(string key, int value){
	params[key] = string(itoa(value,NULL,10));
}
void ZPRequest::addParam(string key, float value){
	int length = _snprintf(NULL,0,"%f",value);
	char* sVal = new char[length+1];
	_snprintf(sVal,length+1,"%f",value);
	params[key]=string(sVal);
}
void ZPRequest::addParam(string key, bool value){
	params[key] = value? "1":"0";
}

map<string,string> ZPRequest::getParams(){
	map<string,string> newmap;
	newmap = params;
	return newmap;
}

ZPRequest::ZPRequest(){
	running = false;
	method = RequestMethodGet;
	startTime = 0;
}

void ZPRequest::setMethod(ZPRequestMethod amethod){
	method = amethod;
}
ZPRequestMethod ZPRequest::getMethod(){
	return method;
}

void ZPRequest::setCallback(RequestCallback callbackFunc, string *inresult){
	callback = callbackFunc;
	result = inresult;
}

void ZPRequest::setQueryDuration(long time){
	duration = time;
}

int writerFunction(char *data, size_t size, size_t nmemb, string *buffer)
{
    int result = 0;
    if (buffer != NULL)
    {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

void ZPRequest::start(){
	if(running)
		return;
	if(startTime==0)
		startTime = time(NULL);
	running = true;
	CURL *curl = curl_easy_init();
	if(method==RequestMethodGet)
		curl_easy_setopt(curl,CURLOPT_HTTPGET,1);
	else
		curl_easy_setopt(curl,CURLOPT_HTTPPOST,1);
	string baseUrl(HOST);
	baseUrl.append(url());
	string signature;
	string header = method==RequestMethodGet?"GET":"POST";
	header.append("&");
	char* escapedUrl = curl_escape(baseUrl.c_str(),baseUrl.length());
	header.append(escapedUrl);
	//header.append(url());
	//sign(&header,params,APPKEY,signature);
	switch(method){

	case RequestMethodGet:
		{
			if(baseUrl.find("?",0)!= string::npos)
				baseUrl.append("&");
			else
				baseUrl.append("?");
			list<string> lst;
			map<string,string>::iterator iter;
			for(iter = params.begin();iter!=params.end();iter++){
				baseUrl.append(iter->first);
				baseUrl.append("=");
				baseUrl.append(iter->second);
				baseUrl.append("&");
			}
			baseUrl.append("signature=");
			baseUrl.append(signature);
		}
		break;
	case RequestMethodPost:
		{
			curl_slist *header = curl_slist_append(NULL,"Content-Type:application/json;charset=UTF-8");
			curl_easy_setopt(curl,CURLOPT_HEADER,header);
			json_t *json = json_object();
			list<string> lst;
			map<string,string>::iterator iter;
			for(iter = params.begin();iter!=params.end();iter++){
				baseUrl.append(iter->first);
				baseUrl.append("=");
				baseUrl.append(iter->second);
				baseUrl.append("&");
			}
			for(iter = params.begin();iter!=params.end();iter++){
				json_object_set(json,iter->first.c_str(),json_string(iter->second.c_str()));
			}
			json_object_set(json,"signature",json_string(signature.c_str()));
			curl_easy_setopt(curl,CURLOPT_POSTFIELDS,json_string_value(json));

		}
		break;
	}
	
	//printf("url:%s",baseUrl.c_str());
	string writerData;
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,&writerData);
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writerFunction);
	curl_easy_setopt(curl,CURLOPT_URL,baseUrl.c_str());
	//curl_easy_setopt(curl,CURLOPT_VERBOSE,1);//TODO: remove this line
	bool success = perform(curl,writerData);
	time_t t = time(NULL) - startTime;
	while(!success&&t<duration){
		Sleep(2000);
		printf("\ntrying another time...\n");
		writerData.clear();
		success = perform(curl,writerData);
		t = time(NULL) - startTime;
	}
	curl_easy_cleanup(curl);
	result->clear();
	result->append(writerData);
	if(callback)
		callback(success,result);
	callback = NULL;
}

bool ZPRequest::perform(CURL *curl, string& result){
	CURLcode code = curl_easy_perform(curl);
	long http_code = 0;
	curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
	if(code!=CURLE_OK){
		return false;
	}
	if(http_code!=200)
		return false;
	json_error_t error;
	json_t *json = json_loads(result.c_str(),JSON_DECODE_ANY,&error);
	json_t *t = json_object_get(json,"status");
	json_int_t lt = json_integer_value(t);
	json_delete(json);
	if(lt!=1)
		return false;
	return true;
}


