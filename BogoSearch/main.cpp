#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Rect_Button.h"
#include "States.h"

//rt -> renderTexture
//el -> event loop
//ml -> main loop
//probably going to reuse the GUI for this 

int main()
{
        sf::Font main_font; //this font has to be accessed everywhere, as we dont need/want multiple duplicates of the same font as that would be wasteful
        drawable_calculations::load_n_check_fnt(main_font, "Assets/Fonts/prstartk.ttf");
        sf::RenderWindow window(sf::VideoMode(drawable_calculations::initial_win_size.x, drawable_calculations::initial_win_size.y), "BogoSearch!");
        sf::View main_view(sf::FloatRect(0, 0, drawable_calculations::initial_win_size.x / 1.15, drawable_calculations::initial_win_size.y / 1.15));

        sf::RenderTexture renderTexture;
        if (!renderTexture.create(drawable_calculations::initial_win_size.x / 1.15, drawable_calculations::initial_win_size.y / 1.15)) // Set this to your desired resolution
            return -1;
        sf::View render_view(sf::FloatRect(0, 0, drawable_calculations::initial_win_size.x / 1.15, drawable_calculations::initial_win_size.y / 1.15));
        renderTexture.setSmooth(false); // Disable smoothing for the render texture

        //window.setFramerateLimit(60);

        States st(renderTexture, main_view, main_font);
        window.setView(main_view);
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::Resized)
                {
                    main_view = sf::View(sf::FloatRect(0, 0, event.size.width / 1.15, event.size.height / 1.15));
                    render_view = sf::View(sf::FloatRect(0, 0, event.size.width / 1.15, event.size.height / 1.15));
                    renderTexture.create(event.size.width / 1.15, event.size.height / 1.15);

                    window.setView(main_view);
                }
                st.state_manager_event(renderTexture, window, main_view, event);
            }

            renderTexture.clear();
            st.state_manager_rt(renderTexture, main_view);
            renderTexture.display(); // Display the render texture

            sf::Sprite renderSprite(renderTexture.getTexture());

            window.clear();
            window.draw(renderSprite);
            window.display();
        }

       // return 0;
}