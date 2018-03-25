#pragma once
#include "includes.h"


class Util
{
public:
	Util();
	~Util();
	static void MoveTo( const int& _x, const int& _y );
	static void MoveTo( const Point& _pos );
	static void MoveToCell( const Point& _pos );
	static void MoveWith( const int& _x, const int& _y );



	static HANDLE gOutHandle;

private:
	bool Init();


};

