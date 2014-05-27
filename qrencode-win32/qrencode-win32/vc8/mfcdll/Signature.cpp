#include "Signature.h"
#include <list>
#include "sha1.h"
#include "Base64.h"
bool compare(string s1, string s2){
	return s1.compare(s2)<0;
}

void sign(map<string,string>params, string key,  string& signature){
	sign(NULL,params,key,signature);
}

void sign(string *header,map<string,string>params, string key,  string& signature){
	map<string,string>::iterator mIterator ;
	string clearText;
	if(header!=NULL){
		clearText.append(*header);
		clearText.append("&");
	}
	list<string> lst;
	for(mIterator = params.begin();mIterator!=params.end();mIterator++){
		//printf("%s\n",mIterator->first);
		lst.push_back(mIterator->first);
	}
	lst.sort(compare);
	int count = lst.size();
	for(list<string>::iterator it = lst.begin();it!=lst.end();it++){
		count--;
		string s  = *it;
		clearText.append(s);
		clearText.append("%3D");
		clearText.append(params[s]);
		if(count>0)
			clearText.append("%26");
	}
	
	
	unsigned char *sign = new unsigned char[20];
	memset(sign,0,20);
	printf("clear text %s\n",clearText.c_str());
	sha1_hmac((unsigned char*)key.c_str(),key.length(),(unsigned char*)clearText.c_str(),clearText.length(),sign);
	printf("sign:%s\n",sign);
	string sign1 = ZBase64::Encode(sign,20);
	printf("sign0:%s\n",sign1.c_str());
	signature.clear();
	signature.append(sign1);
}

