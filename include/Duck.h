#pragma once
#include "Enemy.h"
#include <iostream>

class Duck : public Enemy
{
public:
	enum States
	{
		IdleRight,
		IdleLeft
	};

	Duck(const sf::Texture& texture);
	//~Duck() { std::cout << "Duck"; }

	virtual sf::FloatRect getGlobalBounds() const;
	virtual void setState();


	virtual void colisionWithPlayer(Entity* player, const Collision::ContactData& contact_data);

	void update(const sf::Time dt);
	
};

