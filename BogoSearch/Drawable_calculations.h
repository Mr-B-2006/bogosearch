#pragma once
#ifndef DRAWABLE_CALCULATIONS
#define DRAWABLE_CALCULATIONS
#define NOMINMAX //used so that windows.h doesnt break std::min() and std::max() (which is used in SFML's library code) https://en.sfml-dev.org/forums/index.php?topic=26401.0 
#endif
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <string>
#include <commdlg.h>
#include <cstring>
#include "SFML/Graphics.hpp"

enum mouse_state //allows us to label a number with a corresponding 'state' of the mouse
{
	untouched = 0, hovering = 1, click = 2
};

//TO DO: not here, but make event loop/main loop functions smaller by decomposing into smaller functions, for example instead of handling logic in the event loop method, handle logic in a seperate method and call the method in the event/main loop method
//TO DO: template functions that take in a sf::RenderWindow parameter to just take anything that derives from sf::RenderTarget
//TO DO: maybe just make all functions inline, as having a mix of inline and not inline functions just makes this look kinda messy :/
//TO DO: make those inline functions actually have the keyword "inline" before them idk, my code is a bit fucked i wanna kms
//TO DO: create function for creating basic rectangle in one line (take in size and color) to reduce code repetition and to make debugging easier
//TO DO: create equalitaral triangle creation function

namespace drawable_calculations //this namespace is intended to be used to easily use common functions that will be required by the program, such as centering sprites or opening file dialogues
{
	const int darkening_factor = 191; //darkening_factor is the amount by which a sprite is darkened by when chk_L_click_spr() or chk_L_click_txt() are called
	const sf::Vector2f initial_win_size = sf::Vector2f(620, 440);
	const sf::Vector2f initial_win_center = sf::Vector2f(initial_win_size / 2.f);

	template<class T>
	inline sf::Vector2f center_transformable_return(T &transformable, sf::View &view)
	{
		return sf::Vector2f(view.getCenter().x - (transformable.getGlobalBounds().width / 2), view.getCenter().y - (transformable.getGlobalBounds().height / 2));
	}
	
	template<class T, class VX, class VY>
	sf::Vector2f center_n_offset_transformable(T& transformable, VX x, VY y, sf::View& view)
	{
		return sf::Vector2f(view.getCenter().x - (transformable.getGlobalBounds().width / 2) + x, view.getCenter().y - (transformable.getGlobalBounds().height / 2) + y);
	}

	template<class T, class VX, class VY>
	sf::Vector2f place_n_center(T &transformable, VX x, VY y, sf::View &view) //DO NOT PUT view.getCenter() IN ANY PARAMETER (use initial values in drawable_calculations instead)
	{
		return sf::Vector2f((view.getCenter().x - drawable_calculations::initial_win_size.x/2) + x, (view.getCenter().y - drawable_calculations::initial_win_size.y/2) + y);
	}

	int chk_L_click_spr(sf::RenderWindow &win, sf::RenderTexture& rt, sf::Sprite& spr, sf::Event &event); //checks if left click is pressed and if the mouse is inbetween the globalbounds of the sprite/text, darkens the sprite when the mouse is hovering over it
	bool chk_L_click_txt(sf::RenderWindow& win, sf::RenderTexture &rt, sf::Text& txt, sf::Event &event); //needs deprecating

	template<class T>
	inline int chk_L_click(sf::RenderTexture& rt, sf::RenderWindow& win, T& transformable, sf::Event& event, sf::Color fill_color) //cant template this for each transformable as getGlobalBounds() is not an inherited function between transformables, furthermore, we will want different implementations for shapes and sprites (we want to darken their sprites)
	{
		if (transformable.getGlobalBounds().contains(win.mapPixelToCoords(sf::Mouse::getPosition(win))))
		{
			transformable.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, 0));
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					transformable.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, 255)); //prevents the button looking like its being hovered over when changing between states
					return mouse_state::click;
				}
			}
			return mouse_state::hovering;
		}
		else if (transformable.getFillColor().a == 0)
		{
			transformable.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, 255));
		}
		return mouse_state::untouched;
	}

	//make functions for getting positions of different corners of a view
	//using sf::View::getCenter (yes it works and can be used to get view
	//displacement from the world origin)

	inline sf::Vector2f get_view_TopLeft_corner(sf::View &view)
	{
		float x_component = view.getCenter().x - (view.getSize().x / 2); //for functions like this, I intend to show each vector component explicitly for readability
		float y_component = view.getCenter().y - (view.getSize().y / 2); //TO DO: refactor similar functions to look like this
		return sf::Vector2f(x_component, y_component);
	}

	inline sf::Vector2f get_view_BottomLeft_corner(sf::View &view)
	{
		float x_component = view.getCenter().x - (view.getSize().x / 2); //for functions like this, I intend to show each vector component explicitly for readability
		float y_component = view.getCenter().y + (view.getSize().y / 2); //TO DO: refactor similar functions to look like this
		return sf::Vector2f(x_component, y_component);
	}

	inline sf::Vector2f get_view_TopRight_corner(sf::View& view)
	{
		float x_component = view.getCenter().x + (view.getSize().x / 2); //for functions like this, I intend to show each vector component explicitly for readability
		float y_component = view.getCenter().y - (view.getSize().y / 2); //TO DO: refactor similar functions to look like this
		return sf::Vector2f(x_component, y_component);
	}
	
	inline sf::Vector2f get_view_BottomRight_corner(sf::View& view)
	{
		float x_component = view.getCenter().x + (view.getSize().x / 2); //for functions like this, I intend to show each vector component explicitly for readability
		float y_component = view.getCenter().y + (view.getSize().y / 2); //TO DO: refactor similar functions to look like this
		return sf::Vector2f(x_component, y_component);
	}

	template<class T>
	//using functions above (when they are implemented), account for view 
	//displacement in this function below
	inline int chk_L_click_4_offset_rt(sf::RenderTexture& rt, sf::View& rt_v, sf::RenderWindow& win, T& transformable, sf::Event& event, sf::Color fill_color, sf::Sprite& rt_spr)
	{
		sf::Vector2i mapped_mouse_pos(sf::Vector2i(win.mapPixelToCoords(sf::Mouse::getPosition(win))));

		if (transformable.getGlobalBounds().contains(sf::Vector2f(mapped_mouse_pos.x - rt_spr.getPosition().x, mapped_mouse_pos.y - rt_spr.getPosition().y) + get_view_TopLeft_corner(rt_v)))
		{
			transformable.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, 0));
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					transformable.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, 255)); //prevents the button looking like its being hovered over when changing between states
					return mouse_state::click;
				}
			}
			return mouse_state::hovering;
		}
		else if (transformable.getFillColor().a == 0)
		{
			transformable.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, 255));
		}
		return mouse_state::untouched;
	}

	bool load_n_check_spr(sf::Texture &texture, sf::Sprite& spr, std::string path); //loads a texture and sets a sprite the given texture, also handles errors if the sprite cannot be loaded

	inline bool load_n_check_fnt(sf::Font& font, std::string path)
	{
		if (!(font.loadFromFile(path)))
		{
			MessageBoxA(NULL, ("Unable to locate font file in " + path).c_str(), "Unable to find font file.", MB_OK | MB_ICONSTOP);
			return false;
		}
		return true;
	}
	std::string file_dialogue(); //opens a windows file explorer dialogue and returns the directory of the selected file
	bool chk_4_digit(std::string str); //checks for a digit in an std::string

	template<class T, class U> 
	sf::Vector2f center_two_transformables(T& primary, U& secondary) //secondary is the transformable we want to center relative to primary (think of primary as 'the screen')
	{ //do this in order to make certain functions that arent currently using templates more elegant
		static_assert(std::is_base_of<sf::Transformable, T>::value, "Parameter in drawable_calculations::center_two_drawables must derive from sf::Transformable"); //enforce that parameters derive from sf::Transformable
		static_assert(std::is_base_of<sf::Transformable, U>::value, "Parameter in drawable_calculations::center_two_drawables must derive from sf::Transformable"); //static_assert is NEEDED but it is probably better added than not added

		return sf::Vector2f(primary.getPosition().x + (0.5 * primary.getGlobalBounds().width) - (0.5 * secondary.getGlobalBounds().width),
			primary.getPosition().y + (0.5 * primary.getGlobalBounds().height) - (0.5 * secondary.getGlobalBounds().height));
	}

	inline void initialise_sftext(sf::Text &txt, sf::Font &fnt, int char_size, std::string str) //char size does not need to be automatically multiplied by 10 (as we need to scale character size down to avoid blurred text), this will be handled automatically in this function
	{
		txt.setFont(fnt);
		txt.setCharacterSize(char_size * 10);
		txt.setScale(0.1, 0.1);
		txt.setString(str);
	}

	inline sf::ConvexShape create_tri(int width, sf::Vector2f h) //a simpler way to create flat-based triangles (width -> width of the triangle base (determines the length of the triangle), h -> the coordinates of the highest vertex of the triangle (h.x -> x-coord offset from 0 for the highest vertex, h.y -> y-coord offset from the base of the triangle (determines the height of the triangle)))
	{
		sf::ConvexShape tri;
		tri.setPointCount(3);
		tri.setPoint(0, sf::Vector2f(h.x, 0));
		tri.setPoint(1, sf::Vector2f(width, h.y));
		tri.setPoint(2, sf::Vector2f(0, h.y));
		return tri;
	}

	//DEPRECATED FUNCTIONS:
	[[deprecated("center_n_offset_text has been deprecated and replaced with center_n_offset_transformable")]] void center_n_offset_text(sf::Text& txt, int x, int y, sf::View& view); //centres and applies an offset to a sf::Sprite or sf::Text
	[[deprecated("center_n_offset_sprite has been deprecated and replaced with center_n_offset_transformable")]] void center_n_offset_sprite(sf::Sprite& spr, int x, int y, sf::View& view);
	[[deprecated("center_text has been deprecated and replaced with center_transformable")]] void center_text(sf::Text& txt, sf::View& view); //centers the sprite to the window's view
	[[deprecated("center_sprite has been deprecated and replaced with center_transformable")]] void center_sprite(sf::Sprite& spr, sf::View& view);

}