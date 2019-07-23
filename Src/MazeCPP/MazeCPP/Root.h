#ifndef ROOT_H
#define ROOT_H

////Godot includes
#include <core/Godot.hpp>
#include <Node2D.hpp>
#include <Input.hpp>
#include <InputEvent.hpp>
#include <InputEventAction.hpp>
#include <InputEventMouseButton.hpp>
#include <InputEventKey.hpp>
#include <SceneTree.hpp>
#include <GlobalConstants.hpp>
#include <CanvasItem.hpp>

//Debug include
#include <cstdio> //stdio.h
#include <iostream>
#include <string>

//project includes
#include "Player.h"
//#include "MazeHolder.h"

namespace godot {
	class Player;
	class Root : public Node2D {
		GODOT_CLASS(Root, Node2D)
	private:
	public:
		static Node2D* pInnerWallContainerNode;
		static Player* pPlayer;
		//static MazeHolder* pMazeHolder;
		static Vector2 mazeDimensions;
		static CanvasItem* pCanvas;

		Node2D* pExit;
		Node2D* pOuterWalls;

		static void _register_methods();
		void _init();
		void _ready();

		Root();
		~Root();

		void HandleInputEvent(InputEvent* e);
		void ProcessMWheel(InputEventMouseButton* e);

		void SetMazeDimensions(Vector2 v);
		Vector2 GetMazeDimensions();

		static Vector2 GetExitCoordinates();
	};
}

#endif // !ROOT_H
