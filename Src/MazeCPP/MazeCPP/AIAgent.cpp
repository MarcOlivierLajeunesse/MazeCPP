#include "AIAgent.h"

using namespace godot;

AIAgent::AIAgent(){
	AIAgent::Player(); // call base calss constructor


	//initialize vector of pairs of positible directions
	std::pair<int, int> left(-1, 0);
	std::pair<int, int> up(0, -1);
	std::pair<int, int> right(1, 0);
	std::pair<int, int> down(0, 1);
	posibleDirections.push_back(left);
	posibleDirections.push_back(up);
	posibleDirections.push_back(right);
	posibleDirections.push_back(down);

	std::cout << "AI Agent constructor" << std::endl;
	for (int i = 0; i < posibleDirections.size(); ++i) {
		std::cout << "psoible direction "<< i <<": " << posibleDirections[i].first << ", " << posibleDirections[i].second << std::endl;
	}
	
	currentDirection = DOWN;
	lastDirection = DOWN; // default move down

	

	//init pointers
	pMaze = nullptr;
	pFlood = nullptr;
}

AIAgent::~AIAgent(){}

void AIAgent::_register_methods() {
	register_method("_ready", &AIAgent::_ready);
	register_method("_process", &AIAgent::_process);
}



void AIAgent::_process(float delta){
	int direction = determineDirection();
	if (direction >= 0) {
		//-1 if at exit, or no valid direction
		
		updateMotion(direction);
		move_and_slide(motion * SPEED);
		std::cout << "should be moving" << std::endl;
	}
	
}

void AIAgent::_ready() {
	
	Player::_ready();// call base class ready
	
	pMaze = &MazeGen::getInstance();
	pFlood = &FloodFill::getInstance();


	std::cout << "AI is ready" << std::endl;

}

int AIAgent::determineDirection(){
	std::cout << "determine direction" << std::endl;
	const Vector2 currPosition = this->get_position();

	std::cout << "current position is (" << currPosition.x << ", " << currPosition.y <<")" << std::endl;

	int bestDirection = -1; // enum{LEFT, UP, RIGHT, DOWN};

	std::cout << "last direction was " << lastDirection << " and now moving " << currentDirection << std::endl;

	// get the tile coordinates from pixel  coordinates. assume fixed tile size
	std::pair<int, int> tileCoord = computeTileCoordinates(currPosition, 128);
	int xCoord = tileCoord.first;
	int yCoord = tileCoord.second;

	std::cout << "coordinates of agent is (" << xCoord << ", " << yCoord << ")" << std::endl;

	int currentShortestDistance;
	if (pFlood != nullptr) {
		std::cout << "pFlood is not null" << std::endl;
		std::cout << "pFlood is not null. proof: " << pFlood->getWidth() << std::endl;
		currentShortestDistance = pFlood->getDistance(xCoord, yCoord);
	}
	else {
		std::cout << "pFlood is null" << std::endl;
		currentShortestDistance = INT_MAX;
	}

	if (currentShortestDistance == 0) {
		// arrived at exit;
		return -1;
	}
	
	std::cout << "distance from player to exit is " << currentShortestDistance << std::endl;
	
	for(int i = 0; i < posibleDirections.size(); ++i) {
		std::cout << "checking direction " << i << std::endl;

		int currentX = xCoord + posibleDirections[i].first;
		int currentY = yCoord + posibleDirections[i].second;

		std::cout << "checking direction " << i << ": (" << currentX << ", " << currentY <<")"<< std::endl;

		//check bounds
		if ((currentX < 0) || currentY < 0) { 
			std::cout<<"x or y are less than 0. out of bounds"<<std::endl;
			continue; 
		}
		if ((currentX >= pFlood->getWidth()) || currentY >= pFlood->getHeight()) { 
			std::cout << "x or y are greater than width or heigh. out of bounds" << std::endl;
			continue; 
		}

		if (pMaze->IsWall(currentX, currentY)) { 
			std::cout << "wall" << std::endl;
			continue;
		} // wall. can't go through


		if (pFlood->getDistance(currentX, currentY) < currentShortestDistance) {
			currentShortestDistance = pFlood->getDistance(currentX, currentY);
			bestDirection = i;
		}
	}

	std::cout << "best direction is " << bestDirection <<" which is at a distance of "<< currentShortestDistance << std::endl;
	if (bestDirection >= 0) {
		if (bestDirection != currentDirection) {
			//update last direction when direction changes
			lastDirection = currentDirection;
		}
		currentDirection = bestDirection;// update last direction
		return bestDirection;
	}
	else {
		return -1; // default do nothing
	}
	
}

void AIAgent::updateMotion(int direction){
	motion = Vector2(0, 0);

	if (direction == LEFT) {
		std::cout << "moving LEFT" << std::endl;
		motion.x -= 1;
	}if (direction == UP) {
		std::cout << "moving UP" << std::endl;
		motion.y -= 1;
	}if (direction == RIGHT) {
		std::cout << "moving RIGHT" << std::endl;
		motion.x += 1;
	}if (direction == DOWN) {
		std::cout << "moving DOWN" << std::endl;
		motion.y += 1;
	}
	std::cout << "move in direction (" << motion.x << " ," << motion.y<< ")" << std::endl;
}

std::pair<int, int> AIAgent::computeTileCoordinates(const Vector2 pixelCoordinates, int tileSize) {
	int xCoord, yCoord;


	// get the tile coordinates from pixel  coordinates. assume fixed tile size
	if (currentDirection == DOWN) {
		if (lastDirection == DOWN || lastDirection == RIGHT) {
			std::cout << "moving DOWN, from either DOWN or RIGHT" << std::endl;
			xCoord = (int) std::floor(pixelCoordinates.x / tileSize); // casting to int will round down to 0. same as floor, which still requires a cast to int, but floor is safer
			yCoord = (int) std::floor(pixelCoordinates.y / tileSize);
		}
		//Won't go DOWN after going UP
		else if(lastDirection == LEFT) { // LEFT
			std::cout << "moving DOWN, from LEFT" << std::endl;
			xCoord = (int)std::ceil(pixelCoordinates.x / tileSize); 
			yCoord = (int)std::floor(pixelCoordinates.y / tileSize);
		}
		
	}
	else if ( currentDirection == RIGHT) {
		if (lastDirection == DOWN || lastDirection == RIGHT) {
			std::cout << "moving RIGHT, from either DOWN or RIGHT" << std::endl;
			xCoord = (int)std::floor(pixelCoordinates.x / tileSize);
			yCoord = (int)std::floor(pixelCoordinates.y / tileSize);
		}
		else if (lastDirection == UP) { // UP
			std::cout << "moving RIGHT, from UP" << std::endl;
			xCoord = (int)std::floor(pixelCoordinates.x / tileSize);
			yCoord = (int)std::ceil(pixelCoordinates.y / tileSize);
		}
		//won't got RIGHT after going LEFT
		
	}
	else if (currentDirection == UP) {
		//wont' go UP after going DOWN
		if (lastDirection == RIGHT) {
			std::cout << "moving UP, from RIGHT" << std::endl;
			xCoord = (int)std::floor(pixelCoordinates.x / tileSize);
			yCoord = (int)std::ceil(pixelCoordinates.y / tileSize);
		}
		else if (lastDirection == UP) {
			std::cout << "moving UP, from UP" << std::endl;
			xCoord = (int)std::floor(pixelCoordinates.x / tileSize);
			yCoord = (int)std::ceil(pixelCoordinates.y / tileSize);
		} 
		else if (lastDirection == LEFT){ // LEFT
			std::cout << "moving UP, from LEFT" << std::endl;
			xCoord = (int)std::ceil(pixelCoordinates.x / tileSize);
			yCoord = (int)std::ceil(pixelCoordinates.y / tileSize);

		}
		
	}
	else if (currentDirection == LEFT) {
		if (lastDirection == DOWN) {
			std::cout << "moving LEFT, from DOWN" << std::endl;
			xCoord = (int)std::ceil(pixelCoordinates.x / tileSize);
			yCoord = (int)std::floor(pixelCoordinates.y / tileSize);
		}
		//won't go LEFT after going RIGHT
		else if (lastDirection == UP) {
			std::cout << "moving LEFT, from UP" << std::endl;
			xCoord = (int)std::ceil(pixelCoordinates.x / tileSize);
			yCoord = (int)std::ceil(pixelCoordinates.y / tileSize);
		}
		else if (lastDirection == LEFT) { // LEFT
			std::cout << "moving LEFT, from LEFT" << std::endl;
			xCoord = (int)std::ceil(pixelCoordinates.x / tileSize);
			yCoord = (int)std::floor(pixelCoordinates.y / tileSize);
		}
		
	}
	else{ 
		std::cout << "!!!!!!!!!!!!!!!!!!!!SHOULDN'T BE MOVING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
		// throw error?
		
	}



	return std::pair<int, int>(xCoord, yCoord);
}

