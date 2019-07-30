#include "LoadTXT.h"
LoadTXT* LoadTXT::instance;


LoadTXT::LoadTXT()
{
}

LoadTXT * LoadTXT::Instance()
{
	if (!instance)
		instance = new LoadTXT();
	return instance;
}

RECT* LoadTXT::LoadRect(char * path)
{
	fstream f;

	f.open(path, ios::in);

	int number_of_rect;
	string data;
	string comment = "";

	getline(f, data);
	stringstream stream_data;
	stream_data << data;
	stream_data >> number_of_rect;
	RECT* arrayRect = new RECT[number_of_rect];
	//top-bottom-left-right
	//int top, bottom, left, right;
	for (int i = 0; i < number_of_rect; i++)
	{
		data = "";
		stream_data.clear();

		getline(f, data);
		stream_data << data;

		RECT* r = new RECT();
		stream_data >> r->left;
		stream_data >> r->top;
		stream_data >> r->right;
		stream_data >> r->bottom;
		stream_data >> comment;

		r->right += r->left;
		r->bottom += r->top;

		RECT rect;
		rect.left = r->left;
		rect.right = r->right;
		rect.top = r->top;
		rect.bottom = r->bottom;

		arrayRect[i] = rect;
	}
	f.close();
	return arrayRect;
}

EnemyLocation* LoadTXT::LoadEnemiesLocation(char * path)
{
	fstream f;

	f.open(path, ios::in);

	int number_of_rect;
	string data;
	string comment = "";

	getline(f, data);
	stringstream stream_data;
	stream_data << data;
	stream_data >> number_of_rect;
	EnemyLocation* arrayLocation = new EnemyLocation[number_of_rect];

	for (int i = 0; i < number_of_rect; i++)
	{
		data = "";
		stream_data.clear();

		getline(f, data);
		stream_data << data;

		EnemyLocation location;
		stream_data >> location.type;
		stream_data >> location.positionX;
		stream_data >> location.positionY;
		stream_data >> comment;

		arrayLocation[i] = location;
	}
	f.close();
	return arrayLocation;
}


LoadTXT::~LoadTXT()
{
}
