#include "Root.h"

using namespace godot;

Player* Root::pPlayer;
//MazeHolder* Root::pMazeHolder;
Node2D* Root::pInnerWallContainerNode;
Vector2 Root::mazeDimensions = Vector2(11,7);
CanvasItem* Root::pCanvas;

void Root::_register_methods() {
	//register_method((char*)"_input", &Root::HandleInputEvent);
	register_method("_input", &Root::HandleInputEvent);
	register_method("_ready", &Root::_ready);
	register_property<Root, Vector2>("MazeDimensions", &Root::SetMazeDimensions, &Root::GetMazeDimensions, mazeDimensions);
}

void Root::_init() {}

Root::Root() {
	pExit = nullptr;
	pOuterWalls = nullptr;
}
Root::~Root() {}

void Root::HandleInputEvent(InputEvent* e) {
	const String gsIEMB = "InputEventMouseButton"; // godot::String, not std::string. gsIEM is godot string input event mouse button
	String gsClass = e->get_class(); //godot string class
	if (gsClass == gsIEMB) {
		ProcessMWheel((InputEventMouseButton*)e);
	}
	//quit on escape
	const String gsIEK = "InputEventKey"; // gsIEK is godot string input key
	if (gsClass == gsIEK) {
		InputEventKey* k = (InputEventKey*) e;
		if (k->get_scancode() == GlobalConstants::KEY_ESCAPE) {
			get_tree()->quit();
		}
	}
}

void Root::ProcessMWheel(InputEventMouseButton* e) {
	//handle mouse wheel input
	int64_t buttonIndex = e->get_button_index();
	if (e->is_pressed()) {
		if (buttonIndex == GlobalConstants::BUTTON_WHEEL_DOWN) {
			// zoom out
			Vector2 v = pPlayer->pCamera->get_zoom();
			v.x = v.y = (v.x * 10.0f / 9.0f);
			if (v.x > 1.25f) {
				//why not use clamp?
				v.x = v.y = 1.25f;
			}
			pPlayer->pCamera->set_zoom(v);
		}
		else if (buttonIndex == GlobalConstants::BUTTON_WHEEL_UP) {
			//zoom in
			Vector2 v = pPlayer->pCamera->get_zoom();
			v.x = v.y = (v.x * 0.9f);
			if (v.x < 0.5f) {
				//why not use clamp?
				v.x = v.y = 0.5f;
			}
			pPlayer->pCamera->set_zoom(v);
		}
	}
}

void Root::SetMazeDimensions(Vector2 v) {
	//ensure that v.x and v.y are odd
	if (fmod(v.x, 2) < 0.001) v.x--;
	if (fmod(v.y, 2) < 0.001) v.y--;

	mazeDimensions = v;
}

Vector2 Root::GetMazeDimensions() {
	return mazeDimensions;
}

void Root::_ready() {
	const String gsExit = "Exit";
	const String gsOuterWalls = "OuterWalls";
	const String gsCanvas = "CanvasLayer";
	//const String gsPlayer = "Player";
	const String gsInnerWalls = "InnerWalls";
	Node* node;
	String gsName;
	Array child_array = get_children();
	int64_t childCount = get_child_count();
	for (int64_t i = 0; i < childCount; ++i) {
		node = get_child(i);
		gsName = node->get_name();
		//godot::Godot::print(gsName);
		if (gsExit == gsName) {
			pExit = (Node2D*)node;
		}
		else if (gsOuterWalls == gsName) {
			pOuterWalls = (Node2D*)node;
		}
		else if (gsCanvas == gsName) {
			pCanvas = (CanvasItem*)node;
		}
		else if (gsInnerWalls == gsName) {
			//MazeHolder* mazeHolder = (MazeHolder*)node;
			pInnerWallContainerNode = (Node2D*)node;
			
		}
	
	}

	pExit->set_position(Vector2(128 * (mazeDimensions.x - 3), 128 * (mazeDimensions.y - 3))); // -1 cause the origin is 1,1, and -2 for maze walls

	//set walls
	const String gsNorth = "NorthWall";
	const String gsSouth = "SouthWall";
	const String gsEast = "EastWall";
	const String gsWest = "WestWall";
	const String gsBackground = "Background";
	child_array = pOuterWalls->get_children();
	childCount = pOuterWalls->get_child_count();
	std::cout << "child count for outer walls is " << std::to_string(childCount) << std::endl;
	std::cout << "maze dimensions are (" << std::to_string(mazeDimensions.x) << ", " << std::to_string(mazeDimensions.y) << ") " << std::endl;
	for (int64_t i = 0; i < childCount; ++i) {
		node = pOuterWalls->get_child(i);
		gsName = node->get_name();
		if (gsNorth == gsName) {
			Node2D* wall = (Node2D*)node;
			wall->set_scale(Vector2(mazeDimensions.x, 1));
		}
		else if (gsSouth == gsName) {
			Node2D* wall = (Node2D*)node;
			wall->set_scale(Vector2(mazeDimensions.x, 1));
			wall->set_position(Vector2(-128, 128 * (mazeDimensions.y - 2)));
		}
		else if (gsEast == gsName) {
			Node2D* wall = (Node2D*)node;
			wall->set_scale(Vector2(1, mazeDimensions.y));
			wall->set_position(Vector2(128 * (mazeDimensions.x - 2), -128));
		}
		else if (gsWest == gsName) {
			Node2D* wall = (Node2D*)node;
			wall->set_scale(Vector2(1, mazeDimensions.y));
		}
		else if (gsBackground == gsName) {
			Node2D* background = (Node2D*)node;
			background->set_scale(Vector2(4*mazeDimensions.x, 4*mazeDimensions.y));
			background->set_position(Vector2(-128*mazeDimensions.x, -128*mazeDimensions.y));
		}
	}

	pPlayer->setMaze(pInnerWallContainerNode);

	std::cout << "Root is ready" << std::endl;

}

 Vector2 Root::GetExitCoordinates() {
	// returns the position of the exit (x,y) coodinates
	return Vector2(mazeDimensions.x - 3.0f, mazeDimensions.y - 3.0f);
}

