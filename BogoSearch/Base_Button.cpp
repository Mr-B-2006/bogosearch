#include "Base_Button.h"

bool Base_Button::was_pressed(sf::RenderTexture& rt, sf::RenderWindow &win, sf::Event& event)
{
	int result = drawable_calculations::chk_L_click(rt, win, *this, event, this->getFillColor()); //stores whether our button has been clicked, hovered or not interatced with
	if (result == mouse_state::click) //the statements below handle the button's text colouring when hovering, clicking or not hovering over a button, this implementation may need to be different for other styles of button though.
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
