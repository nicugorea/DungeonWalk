#pragma once

#include "includes.h"
#include "Tile.h"

class Map
{
public:
	Map();
	~Map();

	bool LoadFromFile( const char* _path );
	void Draw();

	Point GetPlayerPosition() { return playerPos; };
	Point GetMapSize() { return { width,height }; };
	int** GetMap();
	void GetInfo( Info& _info );

	void DrawPath( std::vector<Point> _path );
	void ErasePath( std::vector<Point> _path );
	void EventHandle( Info& _info );

	void Update( Info& _info );

private:
	std::vector<Tile> map;
	int width;
	int height;
	Point playerPos;
	

	bool pathDisplayed;
};

