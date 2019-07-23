#ifndef MAZEGEN_H
#define MAZEGEN_H
//
//#include <random>
//#include <cstdlib> // <stdlib.h>

#include <vector>
#include <iostream>
#include "NodeTracker.h"

//SINGLETON

class MazeGen {
private:
	//int mazeWidth, mazeHeight;
	//bool** mazeData;
	//std::mt19937 rng;

	//static MazeGen instance;

	bool isInitialized;

	int width, height;
	NodeTracker* pVisited;
	std::vector<std::vector<bool>> wall;
	MazeGen();
public:
	//MazeGen(int width, int height, uint32_t seed = 0);
	
	~MazeGen();
	MazeGen(const MazeGen& rhs) = delete; // disable copy constructor
	//MazeGen& operator= (const MazeGen& rhs) = delete; // disable assignement operator

	void initializeMaze(int width, int height, uint32_t seed = 0);
	static MazeGen& getInstance();

	void generaMaze();
	//void InitializeRandom32(uint32_t seed);
	bool IsWall(int column, int row);
	int getWidth();
	int getHeight();
};

#endif // !MAZEGEN_H

