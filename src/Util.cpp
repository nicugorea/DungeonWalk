#include "Util.h"

HANDLE Util::gOutHandle;

Util::Util()
{
	Init();
}


Util::~Util()
{
}

void Util::MoveTo( const int & _x, const int & _y )
{
	COORD pos = { _x,_y };
	SetConsoleCursorPosition( gOutHandle, pos );
}

void Util::MoveTo( const Point & _pos )
{
	COORD pos = { _pos.x,_pos.y };
	SetConsoleCursorPosition( gOutHandle, pos );
}

void Util::MoveToCell( const Point & _pos )
{
	Point pos = _pos;
	pos.x = pos.x*CELL_W + 2;
	pos.y = pos.y* CELL_H + 1;
	MoveTo( pos );
}

void Util::MoveWith( const int & _x, const int & _y )
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo( gOutHandle, &info );
	MoveTo( info.dwCursorPosition.X + _x, info.dwCursorPosition.Y + _y );

}

bool Util::Init()
{
	gOutHandle = GetStdHandle( STD_OUTPUT_HANDLE );
	srand( time( NULL ) );
	return true;
}
