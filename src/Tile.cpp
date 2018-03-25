#include "Tile.h"
#include "Util.h"


Tile::Tile( const Point& _pos, const char& _char )
{
	pos = _pos;
	insideChar = _char;
}


Tile::~Tile()
{
}

void Tile::Draw()
{						
	char firstRow[7] = { 201,205,205,205,187,255,0 };
	char midRow[7] = { 186,255,insideChar,255,186,255,0 };
	char lastRow[7] = { 200,205,205,205,188,255,0 };
	if(insideChar=='W')
		for(int i = 0; i < 6; i++)
		{
			firstRow[i] = midRow[i] = lastRow[i] = 219;
		}


	Util::MoveTo(pos);
	LOG( firstRow );
	Util::MoveWith( -6, 1 );
	LOG( midRow );
	Util::MoveWith( -6, 1 );
	LOG( lastRow );

}

int Tile::GetId()
{
	int tmp=0;
	if(insideChar == 'W') tmp = 1;
	if(insideChar == 'M') tmp = -2;
	if(insideChar == 'P') tmp = 0;
	if(insideChar == 'T') tmp = -1;

	return tmp;
}

void Tile::SetId( int _id )
{
	if(_id == 1)
		insideChar = 'W';
	if(_id == 1)
		insideChar = 'M';
	if(_id == 1)
		insideChar = 'T';
	else
		insideChar = ' ';
}

