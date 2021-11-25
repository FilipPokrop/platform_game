#pragma once

#include "Entity.h"
#include "Collision.h"

class Enemy : public Entity
{
public:
	Enemy(const sf::Texture& texture);
	~Enemy();
	
	virtual void colisionWithPlayer(Entity* player,const Collision::ContactData& contact_data) = 0;


};

