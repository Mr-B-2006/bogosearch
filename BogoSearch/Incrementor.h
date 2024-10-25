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
//TO DO: allow incrementors to increment/decrement by a given amount on
//each button press
//TO DO: create an incrementie that goes through a "list" of strings 

enum inc_states //these states are for each incrementor button press
{
	not_pressed = 0, down = 1, up = 2
};

class Incrementor : public sf::Text 
{
private:
	sf::ConvexShape tri_left, tri_right; //these are both the down and up buttons of the incrementor respectively, they will soon be replaced by a unique triangular button class
	int incrementie = 0; //the incrementie is the value that we change with the incrementor
	sf::Text incrementie_txt; //this is the sf::Text object used to display the incrementie
	int initial_val = 0; //if we need to reset the incrementie, it will go to this value
	int min_val = 0; //the lowest value the user can change an incrementie to
	int max_val = 0; //the highest value the user can change an incrementie to
	std::string min_val_str = ""; //the string that displays if the incrementie has reached its initial value
	sf::Vector2f offset_from_label; //the distance from the incrementie that the up and down buttons (tri_right and tri_left) and incrementie_txt (obviously with tri_left being distanced leftwards and tri_right being distanced rightwards (i dont care if leftwards and rightwards arent words, deal with it, you know it makes sense))
public:
	Incrementor(std::string label, sf::Font &fnt, int char_size, sf::Vector2f offset_from_label_param, sf::Vector2f pos, sf::Color colour, int initial_value, std::string minimum_value_string, int minimum_value, int maximum_value, int button_height) //if button_length is less than or equal to zero, make button_length equal to character size of the incrementor object (label text)
	{
		offset_from_label = offset_from_label_param;
		drawable_calculations::initialise_sftext(*this, fnt, char_size, label);
		drawable_calculations::initialise_sftext(incrementie_txt, fnt, char_size, std::to_string(incrementie));
		this->setString(label);
		this->setPosition(pos.x, pos.y); 
		this->setFillColor(colour);
		incrementie_txt.setFillColor(colour);
		if (button_height <= 0) //if no custom value is given for the button height, make it equal to the size used for the sf::Text objects
		{
			button_height = char_size;
		}
		initial_val = initial_value;
		incrementie = initial_val;
		tri_left = drawable_calculations::create_tri(char_size-1, sf::Vector2f(char_size/2, button_height) - sf::Vector2f(1,1));
		tri_right = drawable_calculations::create_tri(char_size-1, sf::Vector2f(char_size / 2, button_height) - sf::Vector2f(1,1));
		tri_left.setOutlineThickness(1); //allows outline when hovering
		tri_right.setOutlineThickness(1);
		
		tri_left.setRotation(-90);
		tri_right.setRotation(90);
		tri_left.setOutlineColor(colour);
		tri_left.setFillColor(colour);
		tri_right.setOutlineColor(colour);
		tri_right.setFillColor(colour);

		tri_left.setPosition(this->getPosition().x + this->getGlobalBounds().width + 6 - offset_from_label_param.x, this->getPosition().y + tri_left.getGlobalBounds().height - offset_from_label_param.y); //hardcoded "+ 6" on x, may need to be some kind of modifiable value from within the constructor? Investigate further"
		incrementie_txt.setPosition(tri_left.getPosition().x + tri_left.getGlobalBounds().width + 4, tri_left.getPosition().y - tri_left.getGlobalBounds().height +2);
		min_val = minimum_value;
		max_val = maximum_value;
		min_val_str = minimum_value_string;
		if (!minimum_value_string.empty() && initial_val == min_val) //if there is a minimum value string and we begin at the minimum value, assign the minimum value string to incrementie_txt...
		{
			min_val_str = minimum_value_string;
			incrementie_txt.setString(min_val_str);
		}
		else //...otherwise just set it to the incrementie's value
		{
			incrementie_txt.setString(std::to_string(incrementie));
		}
		tri_right.setPosition(incrementie_txt.getPosition().x + incrementie_txt.getGlobalBounds().width + tri_right.getGlobalBounds().width + 4, tri_left.getPosition().y - tri_right.getGlobalBounds().height + 3); //hardcoded "+ 4" on x and "+ 3" on y, may need to be some kind of modifiable value from within the constructor? Investigate further		
	}
	void render_incrementor(sf::RenderTexture &rt);
	int handle_buttons(sf::RenderTexture& rt, sf::RenderWindow& win, sf::Event& event);
	void reset();
	void setIncrementie(int new_inc);
	int getIncrementie();
	void change_inc_pos(int x, int y);
};

 