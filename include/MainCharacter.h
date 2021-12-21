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
		DieRight,
		WallJumpLeft,
		WallJumpRight
	};
	MainCharacter(const sf::Texture& texture);

	void update(sf::Time dt);
	void jump();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void catchWall();

	

	virtual sf::FloatRect getGlobalBounds() const;
	virtual void setState();

	//virtual void hit(int lives);
	virtual void hit(int lives, float dir);
	virtual void reactOnCollision(const Collision::ContactData& contact_data);
	virtual void colisionWithPlayer(Entity* player, const Collision::ContactData& contact_data);

private:
	bool m_try_jump;
	bool m_try_catch_wall;
	bool m_double_jump;
	bool m_is_hited;
	bool m_dir;
	bool m_on_wall;
	States m_current_state;

};
