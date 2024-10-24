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
private: //some of these variables seem to be unused, get rid of unused ones
	sf::Sprite index_rt_s; //rename to index_rt_spr
	int index_selected = 0;
	int last_index_above = 0;
	int first_index_below = 0;
	int set_spd = 0, set_num = 0;
	sf::Text set_spd_txt, set_num_txt;
	int mode = vis_mode::none;
	Rect_Button back_button;
	Rect_Button start_button;
	std::vector<sf::RectangleShape> indices;
	int draw_from_index = 0;
	std::vector<int> start_from_on_page;
	int index_width = 14; //here to make it easier to understand and edit how display_indices() works, in a future version, i may make this customisable for the user
	bool pages_needed = false;
	int start_page_at = 1;
	Incrementor page_inc;
	sf::RenderTexture index_rt;
	sf::View new_v; //rename to something more appropriate 
	int y_move_to = 0;
	int selected_index = -1;
	bool bogo_searching = false;
	int bogo_selected = 0;
	sf::Clock Bogo_elapsed;
public:
	Visualiser(sf::RenderTexture& rt, sf::View& view, sf::Font& fnt) : back_button(-1, -1, sf::Color(255, 0, 0), fnt, "Back", sf::Color(0, 0, 0)),
		page_inc("Page:", fnt, 16, sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color(255, 0, 0), 1, "", 1, std::numeric_limits<int>::max(), 0),
		start_button(-2, -2,  sf::Color(255, 0, 0), fnt, "Start", sf::Color(0, 0, 0))
	{					
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
	void display_indices(sf::RenderTexture &rt, sf::View &view);
	void set_positions(sf::RenderTexture& rt, sf::View& view);
	void set_mode(int new_mode);
	void display_set_settings(sf::RenderWindow &win, sf::RenderTexture& rt, sf::View& view, int new_spd_lim, int new_indices_num);
	int handle_events(sf::RenderTexture& rt, sf::RenderWindow& win, sf::View &view , sf::Event& event);
	void look_4_1st_index_offscreen_on_y(sf::RenderTexture& rt, sf::View& view);
	void select_index(sf::RenderTexture& rt, sf::RenderWindow& win, sf::View& view, sf::Event& event);
	void start_bogosearch(sf::RenderTexture &rt, sf::RenderWindow &win, sf::Event event);
	void run_bogosearch(sf::RenderWindow &win);
};

