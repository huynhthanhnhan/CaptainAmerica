#pragma once
#include <vector>
#include <d3dx9.h>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct EnemyLocation
{
	int type;
	int positionX;
	int positionY;
};

class LoadTXT
{
public:
	static LoadTXT* instance;
	LoadTXT();
	static LoadTXT* Instance();
	RECT* LoadRect(char* path);
	EnemyLocation* LoadEnemiesLocation(char* path);
	~LoadTXT();
};

#pragma once
