#ifndef MAZEHOLDER_H
#define MAZEHOLDER_H

#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <Label.hpp>
#include <Resource.hpp>
#include <ResourceLoader.hpp>
#include <core/Ref.hpp>
#include <PackedScene.hpp>
#include <String.hpp>
#include <iostream>

#include "Root.h"
#include "MazeGen.h"
#include "FloodFill.h"

namespace godot {
	class MazeHolder : public Node2D {
		GODOT_CLASS(MazeHolder, Node2D)
	private:
		MazeGen* pMaze;
		FloodFill* pFlood;
		Node2D*** mazeNodes; // matrix of Node2D*
		godot::Ref<PackedScene> wallScene;
		//Node2D*** distanceLabelNodes;
		godot::Ref<PackedScene> distanceScene;
		int mazeWidth, mazeHeight;
	public:
		static void _register_methods();
		void _ready();
		void _init();

		MazeHolder();
		~MazeHolder();

		void AddWallsToMaze();
		//void DisplayDistances();
		MazeGen* getMaze();
		FloodFill* getFloodFill();

		int getWidth();
		int getHeight();
	};
}

#endif // !MAZEHOLDER_H

