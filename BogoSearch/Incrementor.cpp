#include "Incrementor.h"

void Incrementor::render_incrementor(sf::RenderTexture& rt)
{
	rt.draw(*this);
	rt.draw(tri_left);
	rt.draw(incrementie_txt);
	rt.draw(tri_right);
}

int Incrementor::handle_buttons(sf::RenderTexture& rt, sf::RenderWindow& win, sf::Event& event) //this function could definetely use some cleaning up (mainly for when "down" button is pressed)
{
	if (drawable_calculations::chk_L_click(rt, win, tri_right, event, this->getFillColor()) == mouse_state::click)
	{
		if (incrementie < max_val)
		{
			incrementie++;
			incrementie_txt.setString(std::to_string(incrementie));
			tri_right.setPosition(incrementie_txt.getPosition().x + incrementie_txt.getGlobalBounds().width + tri_right.getGlobalBounds().width + 5, tri_right.getPosition().y);
			return inc_states::up;
		}
	}
	else if (drawable_calculations::chk_L_click(rt, win, tri_left, event, this->getFillColor()) == mouse_state::click)
	{
		if (incrementie > min_val)
		{
			incrementie--;
			if (!min_val_str.empty() && incrementie == min_val) //we need to check if we need to assign a minimum value string to incrementie_txt, if there is one
			{
				incrementie_txt.setString(min_val_str);
			}
			else
			{
				incrementie_txt.setString(std::to_string(incrementie));
			}
			tri_right.setPosition(incrementie_txt.getPosition().x + incrementie_txt.getGlobalBounds().width + tri_right.getGlobalBounds().width + 5, tri_right.getPosition().y);
			return inc_states::down;
		}
	}
	return inc_states::not_pressed;
}

void Incrementor::reset()
{
	incrementie = initial_val;
	incrementie_txt.setString(std::to_string(initial_val));
	tri_right.setPosition(incrementie_txt.getPosition().x + incrementie_txt.getGlobalBounds().width + tri_right.getGlobalBounds().width + 5, tri_right.getPosition().y);
}

void Incrementor::setIncrementie(int new_inc)
{
	incrementie = new_inc;
	incrementie_txt.setString(std::to_string(incrementie));
}

int Incrementor::getIncrementie()
{
	return incrementie;
}

void Incrementor::change_inc_pos(int x, int y)
{
	this->setPosition(x, y);
	tri_left.setPosition(this->getPosition().x + this->getGlobalBounds().width + 6 + offset_from_label.x, this->getPosition().y + tri_left.getGlobalBounds().height + offset_from_label.y);
	incrementie_txt.setPosition(tri_left.getPosition().x + tri_left.getGlobalBounds().width + 4, tri_left.getPosition().y - tri_left.getGlobalBounds().height + 2);
	tri_right.setPosition(incrementie_txt.getPosition().x + incrementie_txt.getGlobalBounds().width + tri_right.getGlobalBounds().width + 4, tri_left.getPosition().y - tri_right.getGlobalBounds().height + 3);
}
