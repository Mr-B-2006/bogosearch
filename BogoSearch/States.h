#pragma once
#ifndef STATES_H
#define STATES_H
#endif
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rect_Button.h"
#include "main_menu.h"
#include "Visualiser.h"

enum state_keys //these enums tell us what state the program is in
{
	main_menu_key = 0, vis_preview = 1, vis_run = 2
};

class States
{
private:
	int current_state = state_keys::main_menu_key;
	main_menu mm;
	Visualiser vis;
	struct settings
	{
		int select_spd = 0;
		int num_indices = 0;
	};
	settings set;
public:
	States(sf::RenderTexture &rt, sf::View &view, sf::Font &fnt) : mm(rt, view, fnt),
		vis(rt, view, fnt)
	{

	}
	void state_manager_event(sf::RenderTexture &rt, sf::RenderWindow &win, sf::View &view, sf::Event &event);
	void state_manager_rt(sf::RenderWindow &win, sf::RenderTexture &rt, sf::View &view);
	int get_current_state();
	void set_current_state(int new_state);
	
};