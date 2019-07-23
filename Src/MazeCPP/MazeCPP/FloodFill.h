#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <vector>
#include <iostream>
#include "MazeGen.h"

//SINGLETON

class FloodFill {
private:

	//static FloodFill instance;

	bool isInitialized;

	int width;
	int height;
	MazeGen* maze;
	std::vector<std::vector<int>> DistanceFromExit;

	FloodFill();
public:
	
	~FloodFill();
	//FloodFill(int w, int h, MazeGen* mazeGen); 

	FloodFill(const FloodFill& rhs) = delete;// disable copy constructor
	//FloodFill& operator= (const FloodFill& rhs) = delete; // disable assignement operator

	void initializeFloodFill(int w, int h, MazeGen* mazeGen);
	static FloodFill& getInstance();

	void GenerateFloodFill(int x, int y, int distance);

	int getDistance(int x, int y);

	int getWidth();
	int getHeight();
};

#endif // !FLOODFILL_H

