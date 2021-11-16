#include "Enemy.h"

#include <iostream>

Enemy::Enemy(const sf::Texture& texture)
	:Entity(texture)
{
}

Enemy::~Enemy()
{
	std::cout << "delete enemy" << std::endl;
}
