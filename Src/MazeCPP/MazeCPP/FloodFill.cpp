#include "FloodFill.h"

using namespace std;

//FloodFill FloodFill::instance;

FloodFill::FloodFill() {
	isInitialized = false;
	std::cout << "flood fill constructed" << std::endl;
}

//FloodFill::FloodFill(int w, int h, MazeGen* mazeGen):
//	width(w), height(h){
//	maze = mazeGen;
//	DistanceFromExit.resize(width, vector<int>(height, -1));
//	std::cout << "flood fill constructed" << std::endl;
//}

FloodFill::~FloodFill() {}

void FloodFill::initializeFloodFill(int w, int h, MazeGen* mazeGen) {
	if (isInitialized) {
		std::cout << "flood fill is already initialized. skip it" << std::endl;
		return;
	}
	isInitialized = true;
	width = w;
	height = h;

	maze = mazeGen;
	DistanceFromExit.resize(width, vector<int>(height, -1));
	std::cout << "flood fill initialized" << std::endl;
}

FloodFill& FloodFill::getInstance() {
	//lazy implementation
	std::cout << "retrieving flood fill instance" << std::endl;
	/*if (instance == nullptr) {
		instance = new FloodFill();
	}*/
	static FloodFill instance;
	return instance;
}

void FloodFill::GenerateFloodFill(int x, int y, int distance){

	//std::cout << "generating flood fill" << std::endl;

	//cout << "checking " << x << ", " << y << " which should be at a distance of " << distance << endl;
	if ((x < 0) || (x >= width))  {
		//cout << "x is out of bounds" << endl;
		return; // check x bounds
	}
	if ((y < 0) || (y >= height)) {
		//cout << "y is out of bounds" << endl;
		return; // check y bounds
	}
	if (maze->IsWall(x, y)) {
		//cout << "wall. skip it" << endl;
		return; // wall. can't go through
	}
	//cout << "current idstance is " << DistanceFromExit[x][y] << endl;
	if (DistanceFromExit[x][y] >= 0) return; // already solved

	DistanceFromExit[x][y] = distance; 

	++distance;

	// recursively check each direction

	//left
	GenerateFloodFill(x - 1, y, distance);
	// up
	GenerateFloodFill(x, y - 1, distance);
	// right
	GenerateFloodFill(x + 1, y, distance);
	//down
	GenerateFloodFill(x, y + 1, distance);
}

int FloodFill::getDistance(int x, int y) {
	return DistanceFromExit[x][y];
}

int FloodFill::getWidth() {
	return width;
}

int FloodFill::getHeight() {
	return height;
}

