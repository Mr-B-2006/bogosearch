#include "Base_Button.h"

bool Base_Button::was_pressed(sf::RenderTexture& rt, sf::RenderWindow &win, sf::Event& event)
{
	int result = drawable_calculations::chk_L_click(rt, win, *this, event, this->getFillColor());
	if (result == mouse_state::click)
	{
		button_txt.setFillColor(txt_colour);
		return true;
	}
	else if (result != mouse_state::untouched)
	{
		button_txt.setFillColor(button_colour);
	}
	else
	{
		button_txt.setFillColor(txt_colour);
	}
	return false;
}
