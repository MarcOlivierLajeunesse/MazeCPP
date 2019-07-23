#ifndef PLAYER_H
#define PLAYER_H

#include "Root.h"

#include <core/Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <Camera2D.hpp>

#include <iostream>

namespace godot {
	class Player : public KinematicBody2D {
		GODOT_CLASS(Player, KinematicBody2D)
	protected:
		Vector2 motion;
	public:
		Camera2D* pCamera;

		const int SPEED = 300;
		static void _register_methods();

		void _init();
		virtual void _process(float delta);
		void _ready();

		Player();
		virtual ~Player();

		void UpdateMotionFromInput();

		virtual void setMaze(Node2D* mazeHolder);

	};
}

#endif // !PLAYER_H
