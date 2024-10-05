#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#endif
#include <iostream>
#include <SFML/Graphics.hpp>
#include <limits>
#include "Rect_Button.h"
#include "Incrementor.h"

enum return_mode
{
	main_menu_mode = 0, vis_preview_mode = 1, vis_run_mode = 2
};

class main_menu
{
private:
	//Do not make "BogoSearch!" title text's position scale with how the window is resized, it should be a flat sort of win.top - x (or + but i keep forgetting what tf the y-axis is like in SFML :waltuh:)
	//make functions for changing state, maybe similar to NEA project
	//add an incrememntor class that has up and down buttons which increase a number, also make this behave like a textbox as well (where the number is displayed), you may want to do this by recycling code from NEA project
	Rect_Button start_button, quit_button, submit_button, back_button, select_index;
	sf::Text menu_txt;
	bool setting_up = false; //a kind of a sub-state of the main menu state, i thought of making this its own state, but i feel like setting up is more of a "main menu"
	Incrementor select_spd_inc, num_indices_inc;
public:
	int select_spd=0, num_indices=0;

	main_menu(sf::RenderTexture& rt, sf::View& view, sf::Font& fnt) : start_button(-1, -1, sf::Color(255, 0, 0), fnt, "Start", sf::Color(0, 0, 0)),
		quit_button(-1, -1, sf::Color(255, 0, 0), fnt, "Quit", sf::Color(0, 0, 0)),
		select_spd_inc("Selection speed (fps):", fnt, 16, sf::Vector2f(0, 0), sf::Vector2f(0, 20), sf::Color(255, 0, 0), 0, "No limit", 0, std::numeric_limits<int>::max(), 0),
		num_indices_inc("Number of indices (blocks):", fnt, 16, sf::Vector2f(0, 0), sf::Vector2f(0, 20 + 16 * 2), sf::Color(255, 0, 0), 820, "", 1, std::numeric_limits<int>::max(), 0),
		back_button(-1, -1, sf::Color(255, 0, 0), fnt, "Back", sf::Color(0, 0, 0)),//													^change back to 1
		submit_button(-1, -1, sf::Color(255, 0, 0), fnt, "Submit", sf::Color(0, 0, 0)),
		select_index(-1, -1, sf::Color(255, 0, 0), fnt, "Select index to find", sf::Color(0,0,0))
	{
		drawable_calculations::initialise_sftext(menu_txt, fnt, 16, "BogoSearch!");
		menu_txt.setFillColor(sf::Color(255, 0, 0));
		menu_txt.setPosition(drawable_calculations::center_transformable_return(menu_txt, view).x, 50);
		start_button.setPosition(drawable_calculations::center_n_offset_transformable(start_button, 0, -(5 + (start_button.getGlobalBounds().height / 2)), view));
		quit_button.setPosition(drawable_calculations::center_n_offset_transformable(quit_button, 0, (5 + (quit_button.getGlobalBounds().height / 2)), view));
		back_button.setPosition(rt.getSize().x - back_button.getGlobalBounds().width - 2, rt.getSize().y - back_button.getGlobalBounds().height - 2);
		submit_button.setPosition(2, rt.getSize().y - submit_button.getGlobalBounds().height - 2);
		select_index.setPosition(submit_button.getPosition().x, submit_button.getPosition().y - 1 - select_index.getGlobalBounds().height);
	}
	void set_positions(sf::RenderTexture &rt, sf::View &view); //this will go in the event loop me thinks
	void render_menu(sf::RenderTexture &rt, sf::View &view);
	int handle_events(sf::RenderTexture& rt, sf::RenderWindow &win, sf::Event &event);
};

