#pragma once
#include "includes.h"
#include "Tile.h"

class Player
{
public:
	Player(const Point& _pos);
	~Player();

	bool FindPath(int** _map, const Point& _size);
	std::vector<Point> GetPath() { return path; };
	void DrawPath();
	void ErasePath();

	void Draw();
	void DrawScore(Info& _info);
	void Erase();
	void Move( const char _direction );

	void GetInfo( Info& _info );
	void EventHandle( Info &_info );

	void RandomMove(Info& _info);

private:
	bool random = false;
	char direction = 'u';
	char skin = 202; 
	Point pos;
	std::vector<Point> path;
	int score = 0;
	int pathOn = false;
};

