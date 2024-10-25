#include "States.h"

void States::state_manager_event(sf::RenderTexture &rt, sf::RenderWindow &win, sf::View &view, sf::Event &event)
{
	int mode = -1; //if the value of mode does not change and is still -1, we know something's gone wrong
	switch (current_state)
	{
	case state_keys::main_menu_key:
		mode = mm.handle_events(rt, win, event);
		set_current_state(mode);
		vis.set_mode(mode);
		mm.set_positions(rt, view);
		if (get_current_state()) //makes changes when switching between main menu and visualiser states
		{
			set.select_spd = mm.select_spd;
			set.num_indices = mm.num_indices;
			vis.display_set_settings(win, rt, view, set.select_spd, set.num_indices);
		}
		break;
	case state_keys::vis_preview:
		mode = vis.handle_events(rt, win, view, event);
		set_current_state(mode);
		vis.set_positions(rt, view);
		break;
	case state_keys::vis_run:
		mode = vis.handle_events(rt, win, view, event);
		set_current_state(mode);
		vis.set_positions(rt, view);
		break;
	}
}

void States::state_manager_rt(sf::RenderWindow &win, sf::RenderTexture &rt, sf::View &view)
{
	switch (current_state)
	{
	case state_keys::main_menu_key:
		mm.render_menu(rt, view);
		break;
	case state_keys::vis_preview:
		vis.render_vis(win, rt, view);
		break;
	case state_keys::vis_run:
		vis.render_vis(win, rt, view);
		break;
	}
}

int States::get_current_state()
{
	return current_state;
}

void States::set_current_state(int new_state)
{
	current_state = new_state;
}
