#include "Duck.h"

#include <iostream>

Duck::Duck(const sf::Texture& texture)
	:Enemy(texture)
{
	m_animation.addAnimation(IdleLeft, Animation::AnimationData({ 36,0,-36,36 }, sf::milliseconds(50), 10));
	m_animation.addAnimation(IdleRight, Animation::AnimationData({ 0,0,36,36 }, sf::milliseconds(50), 10));
	m_animation.setAnimation(IdleRight);
}

sf::FloatRect Duck::getGlobalBounds() const
{
	return sf::FloatRect(getPosition()+sf::Vector2f(6.f,6.f), sf::Vector2f(24.f, 30.f));
}

void Duck::setState()
{
}

void Duck::colisionWithPlayer(Entity* player, const Colision::ContactData& contact_data)
{
	if (contact_data)
	{
		//std::cout << "aaa";
		if (contact_data.contact_normal.y < 0)
			kill();
		else
		{
			player->getAtack(1);
		}
	}
}

void Duck::update(const sf::Time dt)
{
	m_acceleration.y = 0;
	Entity::update(dt);
	
}
