#pragma once

#include <SFML/Graphics.hpp>

#include <list>

#include "Player.h"
#include "TileMap.h"
#include "Collision.h"
#include "Duck.h"
#include "ResourceIdentifiers.h"
#include "Lives.h"
#include "MainCharacter.h"
#include "Slime.h"

class World
{
public:
	World(sf::RenderWindow* window, const TextureHolder& texture_holder);
	~World();

	void update(const sf::Time& dt);
	void draw();
	bool handleEvent(const sf::Event& evrnt);
	bool handleEvents();

	bool endGame();

private:
	void checkCollisionPlayerVsMap(const sf::Time& dt);
	void checkCollisionPlayerVsEnemy(const sf::Time& dt);

	

private:
	sf::RenderWindow* m_window;

	const TextureHolder& m_texture_holder;

	MainCharacter* m_main_character;
	Player m_player;
	TileMap* m_map;
	Lives m_lives;

	std::list<Enemy*> m_enemis;

	sf::View m_view;
};

