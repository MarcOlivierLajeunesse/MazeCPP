#ifndef AIAGENT_H
#define AIAGENT_H

//replaces the player class. attach to the player object.

// could inherit from player

#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Camera2D.hpp>

#include <vector>
#include <iostream>
#include <climits>
#include <cmath>

#include "Root.h"
#include "Player.h"
#include "MazeHolder.h"

namespace godot {
	class AIAgent : public Player {
		GODOT_CLASS(AIAgent, Player)
	private:
		MazeGen* pMaze;
		FloodFill* pFlood;

		int lastDirection, currentDirection;
		//int xCoord, yCoord;

		std::vector<std::pair<int, int>> posibleDirections;
	public:
		AIAgent();
		~AIAgent();

		static void _register_methods();
		void _process(float delta);
		void _ready();

		
		int determineDirection();
		void updateMotion(int direction);

		std::pair<int, int> computeTileCoordinates(const Vector2 pixelCoordinates, int tileSize);

		enum DIRECTIONS {LEFT, UP, RIGHT, DOWN};
	};
}

#endif // !AIAGENT_H

