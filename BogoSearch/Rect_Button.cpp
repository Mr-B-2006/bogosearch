#include "Rect_Button.h"

void Rect_Button::draw(sf::RenderTexture& rt, sf::View& view)
{
	rt.draw(*this);
	button_txt.setPosition(drawable_calculations::center_two_transformables(*this, button_txt) + sf::Vector2f(-3, -3)); //centers text relative to the button shape
	rt.draw(button_txt);
}