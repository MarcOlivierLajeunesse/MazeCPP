#include "Player.h"

using namespace godot;

void Player::_register_methods() {
	/*register_method((char*)"_process", &Player::_process);*/
	register_method("_process", &Player::_process);
	register_method("_ready", &Player::_ready);
}

void Player::_init() {}

Player::Player() {
	motion = Vector2(0, 0);
	pCamera = nullptr;
}

Player::~Player() {
	
}

void Player::_process(float delta) {

	const Vector2 currPosition = this->get_position();

	std::cout << "current position is (" << currPosition.x << ", " << currPosition.y << ")" << std::endl;

	UpdateMotionFromInput();
	move_and_slide(motion);
}

void Player::_ready() {
	const godot::String gsCamera2D = "Camera2D";
	Node* node;
	Array child_array = get_children();
	int64_t childCount = get_child_count();
	for (int64_t i = 0; i < childCount; ++i) {
		node = get_child(i);
		if (gsCamera2D == node->get_name()) {
			pCamera = (Camera2D*)node;
		}
	}
	Root::pPlayer = this;

	std::cout << "Player is ready" << std::endl;
}

void Player::UpdateMotionFromInput() {
	motion = Vector2(0, 0);
	Input* input = Input::get_singleton();

	if (input->is_action_pressed("ui_up")) {
		std::cout << "moving UP from input" << std::endl;
		motion.y -= SPEED;
	}
	if (input->is_action_pressed("ui_down")) {
		std::cout << "moving DOWN from input" << std::endl;
		motion.y += SPEED;
	}
	if (input->is_action_pressed("ui_left")) {
		std::cout << "moving LEFT from input" << std::endl;
		motion.x -= SPEED;
	}
	if (input->is_action_pressed("ui_right")) {
		std::cout << "moving RIGHT from input" << std::endl;
		motion.x += SPEED;
	}

	std::cout << "move in direction (" << motion.x << " ," << motion.y << ") /   ////////////////////////////////////" << std::endl;
}

void Player::setMaze(Node2D* mazeHolder){} // do nothing
