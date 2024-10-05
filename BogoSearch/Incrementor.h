#pragma once
#ifndef INCREMENTOR_H
#define INCREMENTOR_H
#endif
#include <iostream>
#include <limits>
#include <SFML/Graphics.hpp>
#include "Drawable_calculations.h"

//TO DO: create triangular button class and implement triangular buttons
//in incrementors

enum inc_states
{
	not_pressed= 0, down = 1, up = 2
};

class Incrementor : public sf::Text 
{
private:
	sf::ConvexShape tri_left, tri_right;
	int incrementie = 0;
	sf::Text incrementie_txt;
	int initial_val = 0;
	int min_val = 0;
	int max_val = 0;
	std::string min_val_str = "";
	sf::Vector2f offset_from_label;
public: //for this project, offset_from_label should be equal to 4 //int x_offset_from_label, int y_offset_from_label, int x, int y,
	Incrementor(std::string label, sf::Font &fnt, int char_size, sf::Vector2f offset_from_label_param, sf::Vector2f pos, sf::Color colour, int initial_value, std::string minimum_value_string, int minimum_value, int maximum_value, int button_length) //if button_length is less than or equal to zero, make button_length equal to character size of the incrementor object (label text)
	{
		offset_from_label = offset_from_label_param;
		drawable_calculations::initialise_sftext(*this, fnt, char_size, label);
		drawable_calculations::initialise_sftext(incrementie_txt, fnt, char_size, std::to_string(incrementie));
		this->setString(label);
		this->setPosition(pos.x, pos.y); 
		this->setFillColor(colour);
		incrementie_txt.setFillColor(colour);
		if (button_length <= 0)
		{
			button_length = char_size;
		}
		initial_val = initial_value;
		incrementie = initial_val;
		tri_left = drawable_calculations::create_tri(char_size-1, sf::Vector2f(char_size/2, button_length) - sf::Vector2f(1,1));
		tri_right = drawable_calculations::create_tri(char_size-1, sf::Vector2f(char_size / 2, button_length) - sf::Vector2f(1,1));
		tri_left.setOutlineThickness(1);
		tri_right.setOutlineThickness(1);
		
		tri_left.setRotation(-90);
		tri_right.setRotation(90);
		tri_left.setOutlineColor(colour);
		tri_left.setFillColor(colour);
		tri_right.setOutlineColor(colour);
		tri_right.setFillColor(colour);

		tri_left.setPosition(this->getPosition().x + this->getGlobalBounds().width + 6 + offset_from_label_param.x, this->getPosition().y + tri_left.getGlobalBounds().height +  offset_from_label_param.y);
		incrementie_txt.setPosition(tri_left.getPosition().x + tri_left.getGlobalBounds().width + 4, tri_left.getPosition().y - tri_left.getGlobalBounds().height +2);
		min_val = minimum_value;
		max_val = maximum_value;
		min_val_str = minimum_value_string;
		if (!minimum_value_string.empty() && initial_val == min_val)
		{
			min_val_str = minimum_value_string;
			incrementie_txt.setString(min_val_str);
		}
		else
		{
			incrementie_txt.setString(std::to_string(incrementie));
		}
		tri_right.setPosition(incrementie_txt.getPosition().x + incrementie_txt.getGlobalBounds().width + tri_right.getGlobalBounds().width + 4, tri_left.getPosition().y - tri_right.getGlobalBounds().height + 3);
		
		
	}
	void render_incrementor(sf::RenderTexture &rt);
	int handle_buttons(sf::RenderTexture& rt, sf::RenderWindow& win, sf::Event& event);
	void reset();
	void setIncrementie(int new_inc);
	int getIncrementie();
	void change_inc_pos(int x, int y);
};

 