#pragma once

#include "Entity.h"
#include "MainCharacter.h"
#include "EnemiesData.h"
#include "TileMap.h"
#include "ResourceIdentifiers.h"

#include <list>
#include <cassert>

class EntityManager :public sf::Drawable
{
public:
	EntityManager(const TextureHolder& textures);
	~EntityManager();

	void checkCollisionWithPlayer(const sf::Time& dt, MainCharacter* player);
	void update(const sf::Time& dt);

	void addEntitiesFromMap(TileMap* map);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addEnemy(const EnemiesData::Data& data, TileMap* map);


private:

	std::list<Entity*> m_entites;
	const TextureHolder& m_textures;

};