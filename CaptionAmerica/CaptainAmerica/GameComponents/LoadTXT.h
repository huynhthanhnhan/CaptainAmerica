#pragma once
#include<vector>
#include<d3dx9.h>
#include<fstream>
#include<string>
#include<string.h>
#include<sstream>
#include<map>
#include<vector>

using namespace std;

class LoadTXT
{
public:
	static LoadTXT* instance;
	LoadTXT() {};
	static LoadTXT* Instance() {};
	RECT* LoadRect(char* path) { RECT *result = new RECT(); result->left = 0; result->top; result->right = 0; result->bottom = 0; return result; };
	~LoadTXT() {};
};

#pragma once
