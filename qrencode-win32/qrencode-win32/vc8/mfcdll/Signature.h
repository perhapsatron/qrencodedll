#ifndef SIGNATURE_H
#define SIGNATURE_H
#include <map>
#include <stdlib.h>
using namespace std;
void sign(map<string,string>params, string key,  string& signature);
void sign(string *header,map<string,string>params, string key,  string& signature);
#endif