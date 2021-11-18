#include "Entity.h"

#include<iostream>
#include <iomanip>
Entity::Entity(const sf::Texture& texture, int lives)
	:m_velocity(0,0),
	m_acceleration(0,0),
	m_animation(texture),
	m_on_ground(false),
	m_is_alive(true),
	//m_is_right(true),
	m_lives(lives)
{
	setPosition(sf::Vector2f(33.f, 33.f));

}

void Entity::update(const sf::Time dt)
{
	m_animation.update(dt);
	sf::Vector2f pos = getPosition();
	//std::cout<< std::setprecision(10) << "(" << pos.x << ", " << pos.y << ")" << std::endl;
	pos += (m_acceleration * dt.asSeconds() * 0.5f + m_velocity) * dt.asSeconds();
	m_velocity += m_acceleration * dt.asSeconds();

	m_state_time += dt;
	setState();
		
	if (m_on_ground)
	{
		//m_on_ground = true;
		m_acceleration.y = 0.f;
		m_velocity.y = 0.f;
		//pos.y = 480.f - 32.f;
	}
	
	setPosition(pos);


	m_acceleration.y = gravity;
	//m_velocity.x = 0.f;

}

sf::FloatRect Entity::getGlobalBounds() const
{
	return sf::FloatRect(getPosition(),sf::Vector2f(32.f,32.f));
}

bool Entity::getOnGround() const
{
	return m_on_ground;
}

void Entity::setOnGround(bool on_ground)
{
	m_on_ground = on_ground;
}

sf::Vector2f Entity::getVelocity() const
{
	return m_velocity;
}

void Entity::setVelocity(const sf::Vector2f& vel)
{
	m_velocity = vel;
}

void Entity::addVelocity(const sf::Vector2f& vel)
{
	m_velocity += vel;
}

sf::Vector2f Entity::getAcceleration() const
{
	return m_acceleration;
}

void Entity::setAcceleration(const sf::Vector2f& acc)
{
	m_acceleration = acc;
}

void Entity::addAcceleration(const sf::Vector2f& acc)
{
	m_acceleration += acc;
}

sf::Vector2f Entity::getDirection(const sf::Time& dt) const
{
	return (m_acceleration * dt.asSeconds() * 0.5f + m_velocity)* dt.asSeconds();
}

bool Entity::isAlive() const
{
	return m_is_alive;
}

void Entity::kill()
{
	m_is_alive = false;
}

void Entity::getAtack(int lives)
{
	m_lives -= lives;
	if (m_lives < 0)
		kill();
}

int Entity::getLives() const
{
	return m_lives;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

#ifdef DEB
	sf::FloatRect rect = getGlobalBounds();
	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Red);
	target.draw(shape);

#endif // DEB


	target.draw(m_animation, states);
}

const float Entity::gravity = 600.f;