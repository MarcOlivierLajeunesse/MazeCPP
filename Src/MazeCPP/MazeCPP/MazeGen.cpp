#include "MazeGen.h"

using namespace std;

//MazeGen* MazeGen::instance = nullptr;

MazeGen::MazeGen(){
	isInitialized = false;
	std::cout << "maze gen constructed" << std::endl;
}

//MazeGen::MazeGen(int w, int h, uint32_t seed):
//	//mazeWidth(w), mazeHeight(h) {
//	width(w), height(h) {
//	//InitializeRandom32(seed);
//	//mazeData = new bool* [w];
//	//for (int i = 0; i < w; ++i) {
//	//	mazeData[i] = new bool[h];
//	//	for (int j = 0; j < h; ++j) {
//	//		if ((i % 2 == 0) && (j % 2 == 0)) {
//	//			mazeData[i][j] = false;
//	//		}
//	//		else {
//	//			mazeData[i][j] = true;
//	//		}
//	//	}
//	//}
//
//	pVisited = new NodeTracker(w, h, seed);
//	wall.resize(width, vector<bool>(height, true));
//	std::cout << "maze gen constructed" << std::endl;
//}

MazeGen::~MazeGen() {
//	if (mazeData) { // clear maze matrix
//		for (int i = 0; i < mazeWidth; ++i) {
//			delete mazeData[i];
//;		}
//		delete mazeData;
//	}
//	mazeData = nullptr;
	delete pVisited;
}

void MazeGen::initializeMaze(int w, int h, uint32_t seed) {
	if (isInitialized) {
		std::cout << "maze gen is already initialized. skip it" << std::endl;
		return;
	}
	isInitialized = true;
	width = w;
	height = h;
	pVisited = new NodeTracker(w, h, seed);
	wall.resize(width, vector<bool>(height, true));
	std::cout << "maze gen initialized" << std::endl;
}

MazeGen& MazeGen::getInstance() {
	std::cout << "retrieving maze gen instance" << std::endl;
	/*if (instance == nullptr) {
		instance = new MazeGen();
	}*/
	static MazeGen instance;
	return instance;
}

//void MazeGen::InitializeRandom32(uint32_t seed) {
//	if (seed == 0) { // default seed
//		std::random_device rd; // machine entropy to create a non-determienistic number
//		seed = rd();
//	}
//	rng.seed(seed);
//}

bool MazeGen::IsWall(int x, int y) {
	//return mazeData[x][y];
	return wall[x][y];
}

void MazeGen::generaMaze() {
	//for (int col = 0; col < mazeWidth; col += 2) {
	//	for (int row = 0; row < mazeHeight; row += 2) {
	//		if ((row == mazeHeight - 1) && (col == mazeWidth - 1)) {
	//			// bottom corner, leave it for exit
	//		}
	//		else if (row == mazeHeight - 1) {
	//			// bottom row, so force col + 1 open
	//			mazeData[col + 1][row] = false;
	//		}
	//		else if (col == mazeWidth - 1) {
	//			// right most column, for force row + 1 open
	//			mazeData[col][row + 1] = false;
	//		}
	//		else {
	//			if (rng() % 2 == 0) {
	//				mazeData[col + 1][row] = false;
	//			}
	//			else {
	//				mazeData[col][row + 1] = false;
	//			}
	//		}
	//	}
	//}

	std::cout << "generating maze..." << endl;
	vector<pair<int, int>> nodeStack;
	for (int currX = 0; currX < width; currX += 2) {
		for (int currY = 0; currY < height; currY += 2) {
			if (pVisited->IsVisited(currX, currY)) continue;
			pVisited->setVisited(currX, currY);
			wall[currX][currY] = false;
			//we are at an unvisited node, and have an empty stack
			// maze algorithm:
			// 1. pick an unvisted neighbour. if none, pop current from stack
			// 2. add current to stack
			// 3. remove wall between current and pick
			// 4. make pick current. mark visited
			int x = currX;
			int y = currY;
			//cout << "currX = " << currX << ", currY = " << currY << endl;
			while (x > -1 && y > -1) {
				unsigned char unvisited = pVisited->GetUnvisitedNeighbour(x, y);
				//cout << "unvisited = " << unvisited << endl;
				if (unvisited == 0) {
					//no unvistited neightbour. pop
					//cout << "no unvisited neighbours, node stack size is " << nodeStack.size() << endl;
					if (nodeStack.size() == 0) {
						break;
					}
					else {
						pair<int, int> p = nodeStack.back();
						nodeStack.pop_back();
						x = p.first;
						y = p.second;
						//cout << "popping new node at " << x << ", " << y << endl;
						continue;
					}
				}
				else {
					//cout << "adding " << x << ", " << y << " to stack" << endl;
					nodeStack.push_back(pair<int, int>(x, y)); // add current to stack
					if (unvisited == 1) {
						//left
						wall[x - 1][y] = false;
						x -= 2;
					}
					else if (unvisited == 2) {
						//up
						wall[x][y - 1] = false;
						y -= 2;
					}
					else if (unvisited == 4) {
						//right
						wall[x+1][y] = false;
						x += 2;
					}
					else{ // unvistied == 8
						// down
						wall[x][y+1] = false;
						y += 2;
					}
					//cout<<"now visiting " << x << ", " << y << endl;
					pVisited->setVisited(x, y);
					wall[x][y] = false;
				}
			}
		}
	}
}


int MazeGen::getWidth() {
	return width;
}

int MazeGen::getHeight() {
	return height;
}
