#pragma once

//#include "Entity.h"
#include <SFML/Graphics.hpp>

class Entity;

class Collision
{
public:
	struct ContactData
	{
		ContactData();
		operator bool() const;

		bool contact;
		sf::Vector2f contact_point;
		sf::Vector2f contact_normal;
		float contact_time;

	};

	static const ContactData rayVsRect(const sf::Vector2f& ray_origin, const sf::Vector2f& ray_dir, const sf::FloatRect& rect);
	static const ContactData dynamicRectvsRect(const Entity& entity, const sf::FloatRect& rect, sf::Time dt);
	static const ContactData dynamicRectvsDynamicRect(const Entity& entity, const Entity& player, sf::Time dt);
	static const bool resolveDynamicRectvsRect(Entity& entity, const sf::FloatRect& rect, sf::Time dt);
};

