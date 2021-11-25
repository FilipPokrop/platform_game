#pragma once

#include "Enemy.h"
#include "TileMap.h"
#include "Collision.h"

class Slime : public Enemy
{
public:
	enum State
	{
		MoveLeft,
		MoveRight
	};

	Slime(const sf::Texture& texture);
	Slime(const sf::Texture& texture, const TileMap& tile_map);

	virtual sf::FloatRect getGlobalBounds() const;
	virtual void setState();


	virtual void colisionWithPlayer(Entity* player, const Collision::ContactData& contact_data);
	void setLeftBorder(const TileMap& tile_map);
	void setRightBorder(const TileMap& tile_map);

	void update(const sf::Time dt);

private:

	State m_current_state;
	float m_left_border;
	float m_right_border;
};