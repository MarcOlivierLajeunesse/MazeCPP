#include "Exit.h"

using namespace godot;

Exit::Exit(){}
Exit::~Exit() {}

void Exit::_register_methods() {
	register_method("_on_Area2D_body_entered", &Exit::_on_Area2D_body_entered);
}

void Exit::_init() {}

//void Exit::_ready(){}

void Exit::_on_Area2D_body_entered(Variant body) {
	TextureRect* t = (TextureRect*)Root::pCanvas->get_child(0);
	t->set_visible(true);
}
