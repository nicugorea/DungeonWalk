#include "Map.h"
#include "Util.h"



Map::Map()
{
}


Map::~Map()
{
}

bool Map::LoadFromFile( const char * _path )
{
	std::ifstream input( _path );
	if(!input.is_open()) return false;
	input >> width;
	input >> height;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			char tmpChar;
			input >> tmpChar;
			if(tmpChar == '0') tmpChar = 255;
			if(tmpChar == 'P') playerPos = { j,i };

			Tile tmpTile( { j*CELL_W,i*CELL_H }, tmpChar );
			map.push_back( tmpTile );

		}

	}
	input.close();

	return true;
}

void Map::Draw()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			map[i*width + j].Draw();
		}

	}
}

int** Map::GetMap()
{
	int** idMap = new int*[height];
	for(int i = 0; i < height; i++)
	{
		idMap[i] = new int[width];
	}
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			idMap[i][j] = map[i*width + j].GetId();

		}


	return idMap;
}

void Map::GetInfo( Info & _info )
{
	_info.map = GetMap();
	_info.mapSize = { width,height };
}

void Map::DrawPath( std::vector<Point> _path )
{
	for(int i = _path.size() - 1; i >= 0; i--)
	{
		Util::MoveToCell( _path[i] );
		Util::MoveWith( -1, 0 );
		LOG( "C" );
	}


}

void Map::ErasePath( std::vector<Point> _path )
{
	for(int i = _path.size() - 1; i >= 0; i--)
	{
		Util::MoveToCell( _path[i] );
		Util::MoveWith( -1, 0 );
		LOG( " " );
	}

}

void Map::EventHandle( Info & _info )
{

	

}

void Map::Update( Info & _info )
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			map[i*width + j].SetId( _info.map[i][j] );
		}
	}


}
