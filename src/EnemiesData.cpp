#include "EnemiesData.h"

EnemiesData::Data::Data(Enemy::Type t, sf::Vector2f pos)
	:type(t),
	position(pos)
{
}

bool EnemiesData::Data::operator()(const Data& d1, const Data& d2)
{
	return d1.position.x < d2.position.x;
}

EnemiesData::EnemiesData()
{
}

bool EnemiesData::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		return false;
	float x, y;
	int type;
	while (file >> type >> x >> y)
	{
		

		Data data((Enemy::Type)type, sf::Vector2f(x, y));
		m_enemies.push_back(data);
	}
	file.close();
	m_enemies.sort(Data());

	return true;
	
}

std::list<EnemiesData::Data>::iterator EnemiesData::begin()
{
	return m_enemies.begin();
}

std::list<EnemiesData::Data>::iterator EnemiesData::end()
{
	return m_enemies.end();
}

std::list<EnemiesData::Data>::iterator EnemiesData::erase(std::list<EnemiesData::Data>::iterator iter)
{
	return m_enemies.erase(iter);
}
