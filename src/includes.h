#pragma once
#include <iostream>
#include <vector>	
#include <time.h>
#include <queue>
#include <deque>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <random>



typedef struct {
	int x;
	int y;
}Point;

typedef struct {
	bool needUpdate = false;
	int** map;
	Point mapSize;
	Point playerPos;
	std::vector<Point> path;
	bool pathState = false;
	bool stop = false;
}Info;


typedef struct Node {
	Point point;
	int id;
	bool visited;
	bool looking;
	Point parent;
}Node;

#define LOG(info) std::cout<<info
#define LOGLN(info) std::cout<<info<<"\n"


#define CELL_W 6
#define CELL_H 3

#define MONSTER_SCORE -1000
#define TREASURE_SCORE +100
#define SHOT_SCORE -25
#define KLL_SCORE +50
#define MOVE_SCORE -1