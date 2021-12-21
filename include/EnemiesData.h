#pragma once

#include "Enemy.h"

#include <SFML/System.hpp>
#include <list>
#include <fstream>

class EnemiesData
{
public:
	struct Data
	{
		Data(Enemy::Type t = Enemy::Type::None, sf::Vector2f pos = { 0,0 });

		bool operator() (const Data& d1, const Data& d2);

		Enemy::Type type;
		sf::Vector2f position;
	};

public:

	EnemiesData();
	bool loadFromFile(const std::string& filename);
	std::list<Data>::iterator begin();
	std::list<Data>::iterator end();
	std::list<Data>::iterator erase(std::list<Data>::iterator iter);

private:
	std::list<Data> m_enemies;
};