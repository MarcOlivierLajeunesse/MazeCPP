#include "Root.h"
#include "Player.h"
#include "MazeHolder.h"
#include "Exit.h"
#include "WinScreen.h"
#include "AIAgent.h"
//#include <gdnative_api_struct.gen.h>

// do not use namespace godot here. docs said so... can us it in 3.1??
using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options* o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options* o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);

	register_class<Player>();
	register_class<AIAgent>();
	register_class<Root>();
	register_class<MazeHolder>();
	register_class<Exit>();
	register_class<WinScreen>();
}
