#pragma once
#ifndef BASE_BUTTON_H
#define BASE_BUTTON_H
#endif
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Drawable_calculations.h"

class Base_Button : public sf::RectangleShape
{
protected:
	sf::Text button_txt;
	sf::Color button_colour;
	sf::Color txt_colour;
	Base_Button(int size_x, int size_y, sf::Color colour, sf::Font& fnt, std::string button_str_param, sf::Color txt_colour_param)
	{
		drawable_calculations::initialise_sftext(button_txt, fnt, 16, button_str_param);
		button_txt.setFillColor(txt_colour_param);
		txt_colour = txt_colour_param;
		if (size_x < 0)
		{
			size_x = button_txt.getGlobalBounds().width;
		}
		if (size_y < 0)
		{
			size_y = button_txt.getGlobalBounds().height;
		}
		this->setSize(sf::Vector2f(size_x + 6, size_y + 6));
		this->setFillColor(colour);
		button_colour = colour;
		this->setOutlineThickness(1);
		this->setOutlineColor(colour);
		button_txt.setString(button_str_param);
	}
public:
	virtual void draw(sf::RenderTexture &rt, sf::View& view) = 0;
	bool was_pressed(sf::RenderTexture &rt, sf::RenderWindow &win, sf::Event& event);
};

