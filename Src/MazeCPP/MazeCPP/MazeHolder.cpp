#include "MazeHolder.h"

using namespace godot;

void MazeHolder::_register_methods() {
	register_method("_ready", &MazeHolder::_ready);
}

void MazeHolder::_init() {}

void MazeHolder::_ready(){
	mazeWidth = (int)Root::mazeDimensions.x - 2; // take outside walls into account
	mazeHeight = (int)Root::mazeDimensions.y - 2;
	int debugSeed = 0; // constant seed for debugging

	//pMaze = new MazeGen(mazeWidth, mazeHeight, debugSeed); 
	pMaze = &MazeGen::getInstance();
	std::cout << "init maze" << std::endl;
	pMaze->initializeMaze(mazeWidth, mazeHeight, debugSeed);
	std::cout << "generate maze" << std::endl;
	pMaze->generaMaze();

	Vector2 exitCoord = Root::GetExitCoordinates();
	
	//pFlood = new FloodFill(mazeWidth, mazeHeight, pMaze);
	pFlood = &FloodFill::getInstance();
	std::cout << "init fill" << std::endl;
	pFlood->initializeFloodFill(mazeWidth, mazeHeight, pMaze);
	std::cout << "generating flood fill" << std::endl;
	pFlood->GenerateFloodFill(exitCoord.x, exitCoord.y, 0);

	mazeNodes = new Node2D**[mazeWidth];
	for (int i = 0; i < mazeWidth; ++i) {
		mazeNodes[i] = new Node2D*[mazeHeight];
	}

	AddWallsToMaze();
	//DisplayDistances();

	//Root::pMazeHolder = this;
	std::cout << "Maze holder is ready" << std::endl;
}

MazeHolder::MazeHolder() {
	ResourceLoader* rl = ResourceLoader::get_singleton();
	wallScene = rl->load("res://Scenes/Wall.tscn");
	distanceScene = rl->load("res://Scenes/DistanceFromExit.tscn");
}

MazeHolder::~MazeHolder() {
	//delete pMaze;
	pMaze = nullptr;
	if (mazeNodes) {
		for (int i = 0; i < mazeWidth; ++i) {
			delete mazeNodes[i];
		}
		delete mazeNodes;
		mazeNodes = nullptr;
	}
}


void MazeHolder::AddWallsToMaze(){
	for (int i = 0; i < mazeWidth; ++i) {
		for(int j = 0; j < mazeHeight; ++j){
			if (pMaze->IsWall(i, j)) {
				const int bufferSize = 256;
				char name[bufferSize];
				sprintf_s(name, bufferSize, "Wall%d_%d", i, j);
				Node2D* n = mazeNodes[i][j] = (Node2D*)wallScene->instance();
				n->set_name(name);
				n->set_position(Vector2(i * 128.0f, j * 128.0f));
				add_child(n);
			}
			else if (!pMaze->IsWall(i, j)) {
				//std::cout << i << ", " << j << " is not a wall" << std::endl;
				const int bufferSize = 256;
				char name[bufferSize];
				sprintf_s(name, bufferSize, "Distace%d_%d", i, j);
				Node2D* node = mazeNodes[i][j] = (Node2D*)distanceScene->instance();
				Label* label = (Label*)node->get_child(0)->get_child(0);
				int distance = pFlood->getDistance(i, j);
				//std::cout << "distace of " << i << ", " << j << " is " << distance << std::endl;

				char distanceStr[bufferSize];
				sprintf_s(distanceStr, bufferSize, "%d", distance);

				//label->set_text(String(distance));
				//label->set_text("A");
				label->set_text(distanceStr);
				node->set_name(name);
				node->set_position(Vector2(i * 128.0f, j * 128.0f));
				add_child(node);
			}
		}
	}
}
//
//void MazeHolder::DisplayDistances() {
//	//instanciates nodes to display the distance from the exit
//	for (int i = 0; i < mazeWidth; ++i) {
//		for (int j = 0; j < mazeHeight; ++j) {
//			if (!pMaze->IsWall(i, j)) {
//
//				Node2D* n = mazeNodes[i][j] = (Node2D*)distanceScene->instance();
//				Label* label = (Label*)n->get_child(0);
//				int distance = pFlood->getDistance(i, j);
//				//label->set_text(String(distance));
//				n->set_name(String(distance));
//				n->set_position(Vector2(i * 128.0f, j * 128.0f));
//				add_child(n);
//			}
//		}
//	}
//}

MazeGen* MazeHolder::getMaze() {
	return pMaze;
}

FloodFill* MazeHolder::getFloodFill() {
	return pFlood;
}

int MazeHolder::getWidth() {
	return mazeWidth;
}

int MazeHolder::getHeight() {
	return mazeHeight;
}
