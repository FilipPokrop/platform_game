#include "Collision.h"
#include <iostream>
#include <iomanip>
Colision::ContactData::ContactData()
	:contact(false),
	contact_point(0.f,0.f),
	contact_normal(0.f,0.f),
	contact_time(0.f)
{
}

Colision::ContactData::operator bool() const
{
	return contact;
}

const Colision::ContactData Colision::rayVsRect(const sf::Vector2f& ray_origin, const sf::Vector2f& ray_dir, const sf::FloatRect& rect)
{
	ContactData contact;

	sf::Vector2f inv_dir(1.f / ray_dir.x, 1.f / ray_dir.y);

	sf::Vector2f t_near = sf::Vector2f((rect.left - ray_origin.x) * inv_dir.x,
		(rect.top - ray_origin.y) * inv_dir.y);

	sf::Vector2f t_far = sf::Vector2f((rect.left + rect.width - ray_origin.x) * inv_dir.x,
		(rect.top + rect.height - ray_origin.y) * inv_dir.y);

	if (std::isnan(t_far.x) || std::isnan(t_far.y)) return contact;
	if (std::isnan(t_near.x) || std::isnan(t_near.y)) return contact;

	if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x) return contact;

	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0) return contact;

	contact.contact_time = std::max(t_near.x, t_near.y);

	contact.contact_point = ray_origin + contact.contact_time * ray_dir;

	if (t_near.x > t_near.y)
	{
		if (inv_dir.x < 0) contact.contact_normal = sf::Vector2f(1, 0);
		else contact.contact_normal = sf::Vector2f(-1, 0);
	}
	else if (t_near.x < t_near.y)
	{
		if (inv_dir.y < 0) contact.contact_normal = sf::Vector2f(0, 1);
		else contact.contact_normal = sf::Vector2f(0, -1);
	}
	contact.contact = true;
	return contact;
}

const Colision::ContactData Colision::dynamicRectvsRect(const Entity& entity, const sf::FloatRect& rect, sf::Time dt)
{
	sf::Vector2f dir = (entity.getVelocity() + entity.getAcceleration() * dt.asSeconds() * 0.5f) * dt.asSeconds();
	if(dir==sf::Vector2f(0.f,0.f))
		return ContactData();
	sf::FloatRect entity_rect = entity.getGlobalBounds();

	sf::FloatRect expand_rect(rect.left - entity_rect.width * 0.5f,
		rect.top - entity_rect.height * 0.5f,
		rect.width + entity_rect.width,
		rect.height + entity_rect.height);

	sf::Vector2f pos(entity_rect.left + entity_rect.width * 0.5f,
		entity_rect.top + entity_rect.height * 0.5f);
	
	ContactData data = rayVsRect(pos, dir, expand_rect);
	data.contact = (data.contact && (data.contact_time >= -0.1f && data.contact_time < 1.f));
	return data;
}

const Colision::ContactData Colision::dynamicRectvsDynamicRect(const Entity& entity, const Entity& player, sf::Time dt)
{
	sf::Vector2f dir = player.getDirection(dt) - entity.getDirection(dt);
	if (dir == sf::Vector2f(0.f, 0.f))
		return ContactData();
	sf::FloatRect e_rect = entity.getGlobalBounds();
	sf::FloatRect p_rect = player.getGlobalBounds();

	sf::FloatRect expand_rect(e_rect.left - p_rect.width * 0.5f,
		e_rect.top - p_rect.height * 0.5f,
		e_rect.width + p_rect.width,
		e_rect.height + p_rect.height);

	sf::Vector2f pos(p_rect.left + p_rect.width * 0.5f,
		p_rect.top + p_rect.height * 0.5f);

	ContactData data = rayVsRect(pos, dir, expand_rect);
	data.contact = (data.contact && (data.contact_time >= -0.1f && data.contact_time < 1.f));
	return data;
}

const bool Colision::resolveDynamicRectvsRect(Entity& entity, const sf::FloatRect& rect, sf::Time dt)
{
	ContactData contact = dynamicRectvsRect(entity, rect, dt);
	if (contact)
	{
		sf::Vector2f vel = entity.getVelocity();
		sf::Vector2f cn = contact.contact_normal;
		sf::Vector2f acc = entity.getAcceleration();

		//std::cout << dt.asSeconds() << " " << vel.y << " " << acc.y << " ";
		vel = (1 - contact.contact_time) * (sf::Vector2f(std::fabs(vel.x) * cn.x, std::fabs(vel.y) * cn.y));
			//- sf::Vector2f(acc.x * fabs(cn.x), acc.y * fabs(cn.y)) * dt.asSeconds() *0.5f);
		acc = -(1-contact.contact_time) *  sf::Vector2f(acc.x * fabs(cn.x), acc.y * fabs(cn.y)) ;
		entity.addVelocity(vel);
		entity.addAcceleration(acc);
		//std::cout << contact.contact_time << ' ' << entity.getVelocity().y << " " << entity.getAcceleration().y<< " ";
		if (contact.contact_normal.y < 0)
			entity.setOnGround(true);
		return true;
	}
	return false;
}
