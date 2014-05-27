#ifndef ZPREQUEST_H
#define ZPREQUEST_H
#include <string>
#include <map>
#include "jansson.h"
#include "curl.h"
using namespace std;
typedef void (*RequestCallback)(bool success,string* result);
typedef enum {
	RequestMethodGet,RequestMethodPost
}ZPRequestMethod;

class ZPRequest{
public:
	void addParam(string key, string value);
	void addParam(string key, int value);
	void addParam(string key, float value);
	void addParam(string key, bool value);
	void testParams();
	void setMethod(ZPRequestMethod method);
	void setCallback(RequestCallback callbackFunc, string *result);
	ZPRequestMethod getMethod();
	virtual string url();
	map<string,string> getParams();
	void start();
	ZPRequest();
	void setQueryDuration(long timeInSeconds);
private:
	bool perform(CURL *curl, string& result);
	map<string,string> params;
	bool running;
	ZPRequestMethod method;
	RequestCallback callback;
	string *result;
	long duration;
	long startTime;
};

#endif