#pragma once
#include "Enemy.h"

class Duck : public Enemy
{
public:
	enum States
	{
		IdleRight,
		IdleLeft
	};

	Duck(const sf::Texture& texture);

	virtual sf::FloatRect getGlobalBounds() const;
	virtual void setState();


	virtual void colisionWithPlayer(Entity* player, const Colision::ContactData& contact_data);

	void update(const sf::Time dt);
	
};

