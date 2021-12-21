#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collision.h"

//#define DEB


class Entity: public sf::Drawable, public sf::Transformable
{
public:
	Entity(const sf::Texture& texture, int lives = 1);
	virtual void update(const sf::Time dt);
	virtual void setState() = 0;
	virtual sf::FloatRect getGlobalBounds() const;

	bool getOnGround() const;
	void setOnGround(bool on_ground);

	sf::Vector2f getVelocity() const;
	void setVelocity(const sf::Vector2f& vel);
	void addVelocity(const sf::Vector2f& vel);

	sf::Vector2f getAcceleration() const;
	void setAcceleration(const sf::Vector2f& acc);
	void addAcceleration(const sf::Vector2f& acc);

	sf::Vector2f getDirection(const sf::Time& dt) const;

	bool isAlive() const;
	void kill();
	virtual void hit(int lives, float dir=0);

	sf::Vector2f getCenter() const;
	
	int getLives() const;

	virtual void reactOnCollision(const Collision::ContactData& contact_data);
	virtual void colisionWithPlayer(Entity* player, const Collision::ContactData& contact_data) = 0;

	static const float gravity;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	Animation m_animation;
	sf::Time m_state_time;
private:
	
	bool m_on_ground;
	bool m_is_alive;
	//bool m_is_right;
	int m_lives;
};

