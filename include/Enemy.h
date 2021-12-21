#pragma once

#include "Entity.h"
#include "Collision.h"

class Enemy : public Entity
{
public:

	enum class Type
	{
		None = -1,
		AngryPig,
		Slime

	};

	Enemy(const sf::Texture& texture);
	~Enemy();
	
	


};

