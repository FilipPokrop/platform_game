#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	enum States
	{
		IdleLeft,
		IdleRight,
		MoveLeft,
		MoveRight,
		JumpLeft,
		JumpRight,
		FallLeft,
		FallRight,
		HitLeft,
		HitRight
	};
	Player(const sf::Texture& texture);

	void update(sf::Time dt);
	void jump();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	sf::Vector2f getCenter() const;

	virtual sf::FloatRect getGlobalBounds() const;
	virtual void setState();

	virtual void getAtack(int lives);

private:
	bool m_try_jump;
	bool m_is_hited;
	States m_current_state;
	
};

