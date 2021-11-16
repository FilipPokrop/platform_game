// ColisionSystem.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <SFML/Graphics.hpp>
#include "World.h"
#include <iostream>

int main()
{
    //std::cout << true;
    uint32_t frame_counter = 0;
    sf::Time frame_time = sf::Time::Zero;
    sf::Font font;
    font.loadFromFile("media/fonts/Sansation.ttf");
    sf::Text frames("FPS: "+std::to_string(frame_counter),font);
    
    sf::RenderWindow window(sf::VideoMode(640*2, 480*2), "SFML works!",sf::Style::None);
    window.setKeyRepeatEnabled(false);
    //window.setFramerateLimit(60);
    //sf::RectangleShape shape(sf::Vector2f(100, 100));
    //shape.setPosition(100, 100);


    TextureHolder texture_holder;
    texture_holder.load(Textures::Player, "media/textures/MainCharacters/NinjaFrog.png");
    texture_holder.load(Textures::Duck, "media/Free/Enemies/Duck/Idle (36x36).png");
    texture_holder.load(Textures::Map, "media/Free/Terrain/Terrain (16x16).png");
    texture_holder.load(Textures::WorldGui, "media/textures/Gui/World.png");
    
    
    World world(&window,texture_holder);

    sf::Clock clock;
    while ( window.isOpen())
    {
        sf::Time delta_time = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (world.handleEvent(event))
                continue;

            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            
            
        }

        world.handleEvents();  
        world.update(delta_time);
       
        frame_time += delta_time;
        frame_counter++;
        if (frame_time >= sf::seconds(1.f))
        {
            frames.setString("FPS: " + std::to_string(frame_counter));
            frame_counter = 0;
            frame_time -= sf::seconds(1.f);
        }

        window.clear(sf::Color::Cyan);
        
        world.draw();
        window.draw(frames);
        window.display();
    }
    
    return 0;
}