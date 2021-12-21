#include "EntityManager.h"

#include "Slime.h"

EntityManager::EntityManager(const TextureHolder& textures)
	:m_entites(),
	m_textures(textures)
{
}

EntityManager::~EntityManager()
{
	for (auto iter = m_entites.begin(); iter != m_entites.end(); ++iter)
	{
		delete* iter;
	}
}

void EntityManager::checkCollisionWithPlayer(const sf::Time& dt, MainCharacter* player)
{
	for (auto iter = m_entites.begin(); iter != m_entites.end(); ++iter)
	{
		Collision::ContactData data = Collision::dynamicRectvsDynamicRect(**iter, *player, dt);
		(*iter)->colisionWithPlayer(player, data);
	}
	
}

void EntityManager::update(const sf::Time& dt)
{
	for (auto iter = m_entites.begin(); iter != m_entites.end();)
	{
		(*iter)->update(dt);
		if (!(*iter)->isAlive())
		{
			delete* iter;
			iter = m_entites.erase(iter);
		}

		else
			++iter;
	}
}

void EntityManager::addEntitiesFromMap(TileMap* map)
{
	EnemiesData& enemies = map->getEnemies();
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		addEnemy(*iter, map);
		iter = enemies.erase(iter);
	}
}

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto iter = m_entites.begin(); iter != m_entites.end(); ++iter)
	{
		target.draw(**iter, states);
	}
}

void EntityManager::addEnemy(const EnemiesData::Data& data, TileMap* map)
{
	Entity* entity = nullptr;
	if (data.type == Enemy::Type::Slime)
	{
		Slime* slime = new Slime(m_textures.get(Textures::Slime));
		slime->setPosition(data.position);
		slime->setLeftBorder(*map);
		slime->setRightBorder(*map);
		entity = slime;
	}

	

	assert(entity != nullptr);
	m_entites.push_back(entity);
}
