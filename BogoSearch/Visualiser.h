#pragma once
#ifndef VISUALISER_H
#define VISUALISER_H
#endif
#include <iostream>
#include <SFML/Graphics.hpp>
#include <limits>
#include <vector>
#include "Rect_Button.h"
#include "Incrementor.h"

enum vis_mode
{
	none = 0,
	select_preview = 1, 
	running = 2
};

class Visualiser
{
private: 
	sf::Sprite index_rt_spr; 
	int last_index_above = 0;
	int first_index_below = 0;
	int set_spd = 0;
	int	set_num = 0;
	sf::Text set_spd_txt, set_num_txt;
	int mode = vis_mode::none;
	Rect_Button back_button;
	Rect_Button start_button;
	std::vector<sf::RectangleShape> indices;
	int index_width = 14; 
	Incrementor page_inc;
	sf::RenderTexture index_rt;
	sf::View index_rt_view;  
	int y_move_to = 0;
	int selected_index = -1;
	bool bogo_searching = false;
	int bogo_selected = 0;
	sf::Clock Bogo_elapsed;
public:
	Visualiser(sf::RenderTexture& rt, sf::View& view, sf::Font& fnt) : back_button(-1, -1, sf::Color(255, 0, 0), fnt, "Back", sf::Color(0, 0, 0)),
		page_inc("Page:", fnt, 16, sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color(255, 0, 0), 1, "", 1, std::numeric_limits<int>::max(), 0),
		start_button(-2, -2,  sf::Color(255, 0, 0), fnt, "Start", sf::Color(0, 0, 0))
	{		//initialise text, incrementors and buttons			
		drawable_calculations::initialise_sftext(set_spd_txt, fnt, 16, "Selection speed limit/fps: ");
		drawable_calculations::initialise_sftext(set_num_txt, fnt, 16, "Number of blocks: ");
		set_spd_txt.setFillColor(sf::Color(255, 0, 0));
		set_num_txt.setFillColor(sf::Color(255, 0, 0));
		set_spd_txt.setPosition(0, 0);
		set_num_txt.setPosition(0, set_spd_txt.getPosition().y + set_spd_txt.getGlobalBounds().height+4);
		back_button.setPosition(rt.getSize().x - back_button.getGlobalBounds().width - 2, rt.getSize().y - back_button.getGlobalBounds().height - 2);
		page_inc.change_inc_pos(0, view.getSize().y - page_inc.getGlobalBounds().height - 4);
		start_button.setPosition(back_button.getPosition().x - start_button.getGlobalBounds().width - 4, back_button.getPosition().y);
	}
	void render_vis(sf::RenderWindow& win, sf::RenderTexture& rt, sf::View& view);
	void display_indices(sf::RenderTexture &rt, sf::View &view); //alligns indices and calculates how far down index_rt_view needs to move
	void set_positions(sf::RenderTexture& rt, sf::View& view);
	void set_mode(int new_mode);
	void display_set_settings(sf::RenderWindow &win, sf::RenderTexture& rt, sf::View& view, int new_spd_lim, int new_indices_num);
	int handle_events(sf::RenderTexture& rt, sf::RenderWindow& win, sf::View &view , sf::Event& event);
	void look_4_1st_index_offscreen_on_y(sf::RenderTexture& rt, sf::View& view);
	void select_index(sf::RenderTexture& rt, sf::RenderWindow& win, sf::View& view, sf::Event& event);
	void start_bogosearch(sf::RenderTexture &rt, sf::RenderWindow &win, sf::Event event); //this method is responsible for getting the bogo searc algorithm ready, and selecting a random index if one hasnt been selected already
	void run_bogosearch(sf::RenderWindow &win); //actual algorithm code
};

