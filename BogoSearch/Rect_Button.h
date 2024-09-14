#pragma once
#ifndef RECT_BUTTON_H
#define RECT_BUTTON_H
#endif
#include <iostream>
#include <SFML/Graphics.hpp>
//#include "Drawable_calculations.h"
#include "Base_Button.h"

class Rect_Button : public Base_Button
{
private:

public: 
	Rect_Button(int size_x, int size_y, sf::Color colour, sf::Font &fnt, std::string button_str_param, sf::Color txt_colour_param) : Base_Button(size_x, size_y, colour, fnt, button_str_param, txt_colour_param) //when an abscissa or ordinate of Button, is negative, they will default to scaling based on the size of the text 
	{	}
	void draw(sf::RenderTexture& rt, sf::View& view);
};

