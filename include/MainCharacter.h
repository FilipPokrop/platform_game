#pragma once

#include "Entity.h"

class MainCharacter : public Entity
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
		HitRight,
		DieLeft,
		DieRight
	};
	MainCharacter(const sf::Texture& texture);

	void update(sf::Time dt);
	void jump();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	

	virtual sf::FloatRect getGlobalBounds() const;
	virtual void setState();

	//virtual void hit(int lives);
	virtual void hit(int lives, float dir);

private:
	bool m_try_jump;
	bool m_is_hited;
	bool m_dir;
	States m_current_state;

};
