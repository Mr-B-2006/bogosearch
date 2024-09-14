//switching pages shows the bottom row of the last page as the top row of the current page, this was technically a bug, but i may consider it a feature as it can give the user an idea of where the page they are exists in regards to the whole load of indices
#include "Visualiser.h"
/*

TO DO (10/09/2024):
~make it so the index the user wants to be found can be selected by clicking
an index in the preview menu
~work on the visualiser's running state

*/

void Visualiser::render_vis(sf::RenderTexture& rt, sf::View& view)
{
	rt.draw(set_spd_txt);
	rt.draw(set_num_txt);
	back_button.draw(rt, view);
	page_inc.render_incrementor(rt);
	
	index_rt.clear(/*sf::Color(0, 0, 255, 128)*/); //colour parameter is only used for debugging purposes
	
	for (int i= 0; i != indices.size(); i++)
	{
		index_rt.draw(indices[i]); //draws all indices
	}
	index_rt.display();
	sf::Sprite index_rt_s(index_rt.getTexture());
	index_rt_s.setPosition(0, set_num_txt.getPosition().y + set_num_txt.getGlobalBounds().height +10);
	rt.draw(index_rt_s);
}

void Visualiser::display_indices(sf::RenderTexture& rt, sf::View& view) //this could be optimised by making sure that row specific logic/calculations are performed for each row rather than each index (rows + columns)
{
	sf::RectangleShape initial_index(sf::Vector2f(index_width, index_width));
	initial_index.setFillColor(sf::Color(255, 0, 0));
	initial_index.setPosition(5,0);
	indices.push_back(initial_index);
	int row_start_index = 0;
	bool first_off_screen_y = false;
	for (int i = 1; i != set_num; i++)
	{
		sf::RectangleShape new_index(sf::Vector2f(index_width, index_width));
		sf::Vector2f new_index_pos(indices[i - 1].getPosition().x + index_width + 40, indices[i - 1].getPosition().y);
		new_index.setFillColor(sf::Color(255, 0, 0));
		indices.push_back(new_index);
		if (new_index_pos.x > view.getSize().x - index_width)
		{
			new_index_pos = indices[row_start_index].getPosition() + sf::Vector2f(0, 40);			
			row_start_index = i;
			if ((rt.mapCoordsToPixel(new_index_pos, new_v).y + index_width > rt.getSize().y - 3) && first_off_screen_y == false)
			{
				y_move_to = new_index_pos.y - 40;
				first_off_screen_y = true;
			}
		}
		indices[i].setPosition(new_index_pos);
		
	}

}

int Visualiser::look_4_1st_index_offscreen_on_y(sf::RenderTexture& rt, sf::View& view) //i dont think we need the main view (&view) to be here, same possible for display_indices()
{
	int rt_size = rt.getSize().y; //seems redundant but solves an issue where somehow, the condition (rt.mapCoordsToPixel(indices[i].getPosition(), new_v).y + index_width > rt_size - 3) would return true on 2nd page even though LHS was negative, maybe an SFML related issue when calling sf::RenderTexture.getSize() multiple times per frame????
	for (int i = 0; i != set_num; i++)
	{
		if (rt.mapCoordsToPixel(indices[i].getPosition(), new_v).y + index_width > rt_size - 3)
		{
			return indices[i].getPosition().y;
		}
	}
	return 0; //if this is returned, no indices exist below the screen
}

void Visualiser::set_positions(sf::RenderTexture& rt, sf::View& view) //this runs in the event loop when the visualiser mode is active
{
	back_button.setPosition(rt.getSize().x - back_button.getGlobalBounds().width - 2, rt.getSize().y - back_button.getGlobalBounds().height - 2);
	set_num_txt.setPosition(0, set_spd_txt.getPosition().y + set_spd_txt.getGlobalBounds().height+4);
	page_inc.change_inc_pos(0, view.getSize().y - page_inc.getGlobalBounds().height - 4);
}

int Visualiser::handle_events(sf::RenderTexture &rt, sf::RenderWindow &win, sf::View &view ,sf::Event &event)
{
	int page_switch_state = page_inc.handle_buttons(rt, win, event);
	switch (page_switch_state)
	{
	case inc_states::not_pressed:
		look_4_1st_index_offscreen_on_y(rt, view);
		break;
	case inc_states::down:
		look_4_1st_index_offscreen_on_y(rt, view);
		new_v.move(0, -y_move_to);
		index_rt.setView(new_v);
		break;
	case inc_states::up:
		if (look_4_1st_index_offscreen_on_y(rt, view) != 0)
		{
			new_v.move(0, y_move_to);
			index_rt.setView(new_v);
		}
		else //prevents incrementie going up when maximum page has been reached
		{
			page_inc.setIncrementie(page_inc.getIncrementie() - 1);
		}
		break;
	}
	if (back_button.was_pressed(rt, win, event))
	{
		pages_needed = false;
		set_mode(vis_mode::none);
		indices.clear();
		page_inc.reset();
		return vis_mode::none;
	}
	if (event.type == sf::Event::Resized)
	{
		int y_component_temp = (event.size.height - 84) / 1.15; //when possible try, to make this use related variables rather than 84, this still works as intended but needs to be cleaned up 
		index_rt.create((event.size.width)/1.15, y_component_temp);
		new_v = sf::View(sf::FloatRect(0, 0, (event.size.width) / 1.15, y_component_temp));
		page_inc.reset();
		index_rt.setView(new_v);
		indices.clear();
		display_indices(rt, new_v);
	}
	return mode;
}



void Visualiser::set_mode(int new_mode)
{
	mode = new_mode;
}

void Visualiser::display_set_settings(sf::RenderTexture &rt, sf::View &view, int new_spd_lim, int new_indices_num) //runs for one frame when switching from setting up to visualiser
{ //we dont divide by 1.15 here because it is already accounted for by the view size
	int y_component_temp = (view.getSize().y - 84); //when there is time, try to clean up this code :p
	index_rt.create((view.getSize().x), y_component_temp);
	new_v = sf::View(sf::FloatRect(0, 0, (view.getSize().x), y_component_temp));
	index_rt.setView(new_v);
	set_spd = new_spd_lim;
	if (set_spd != 0)
	{
		set_spd_txt.setString("Selection speed/fps: " + std::to_string(set_spd));
	}
	else
	{
		set_spd_txt.setString("Selection speed/fps: No limit");
	}
	set_num = new_indices_num;
	set_num_txt.setString("Number of blocks: " + std::to_string(set_num));
}