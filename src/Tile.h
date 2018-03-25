#pragma once
#include "includes.h"

class Tile
{
public:
	Tile(const Point& _pos,const char& _char);
	~Tile();		 

	void Draw();

	int GetId();
	void SetId( int _id );
private:
	char insideChar = 255;
	Point pos = { 0,0 };
};

