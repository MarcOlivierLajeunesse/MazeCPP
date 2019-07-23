#include "WinScreen.h"

using namespace godot;

WinScreen::WinScreen() {}
WinScreen::~WinScreen(){}

void WinScreen::_register_methods(){
	register_method("_on_RestartButton_pressed", &WinScreen::_on_RestartButton_pressed);
	register_method("_on_QuitButton_pressed", &WinScreen::_on_QuitButton_pressed);
}

void WinScreen::_init(){}

void WinScreen::_on_RestartButton_pressed(Variant body){
	SceneTree* t = get_tree();
	t->reload_current_scene();
}

void WinScreen::_on_QuitButton_pressed(Variant){
	SceneTree* t = get_tree();
	t->quit();
}