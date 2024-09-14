#include "main_menu.h"

void main_menu::set_positions(sf::RenderTexture &rt, sf::View &view)
{
	menu_txt.setPosition(drawable_calculations::center_transformable_return(menu_txt, view).x, 50);

	start_button.setPosition(drawable_calculations::center_n_offset_transformable(start_button, 0, -(5 + (start_button.getGlobalBounds().height/2)), view));
	quit_button.setPosition(drawable_calculations::center_n_offset_transformable(quit_button, 0, (5 + (quit_button.getGlobalBounds().height/2)), view));
	back_button.setPosition(rt.getSize().x - back_button.getGlobalBounds().width - 2, rt.getSize().y - back_button.getGlobalBounds().height - 2);
	submit_button.setPosition(2, rt.getSize().y - submit_button.getGlobalBounds().height - 2);
	select_index.setPosition(submit_button.getPosition().x, submit_button.getPosition().y - 4 - select_index.getGlobalBounds().height);

}

void main_menu::render_menu(sf::RenderTexture& rt, sf::View& view)
{
	if (setting_up)
	{
		select_spd_inc.render_incrementor(rt);
		num_indices_inc.render_incrementor(rt);
		back_button.draw(rt, view);
		submit_button.draw(rt, view);
		select_index.draw(rt, view);
	}
	else
	{
		start_button.draw(rt, view);
		quit_button.draw(rt, view);
		rt.draw(menu_txt);
	}
}

int main_menu::handle_events(sf::RenderTexture &rt, sf::RenderWindow &win, sf::Event &event)
{
	if (setting_up)
	{
		select_spd_inc.handle_buttons(rt, win, event);
		num_indices_inc.handle_buttons(rt, win, event);
		if (submit_button.was_pressed(rt, win, event))
		{

			select_spd = select_spd_inc.getIncrementie();
			num_indices = num_indices_inc.getIncrementie();
			return return_mode::vis_run_mode;
		}
		else if (back_button.was_pressed(rt, win, event))
		{
			setting_up = false;
		}
		else if (select_index.was_pressed(rt, win, event))
		{
			select_spd = select_spd_inc.getIncrementie();
			num_indices = num_indices_inc.getIncrementie();
			return return_mode::vis_preview_mode;
		}
	}
	else
	{
		if (start_button.was_pressed(rt, win, event))
		{
			setting_up = true;
		}
		else if (quit_button.was_pressed(rt, win, event))
		{
			exit(0);
		}
	}
	return return_mode::main_menu_mode;
}
