#include "TileMapData.h"

#include <iostream>

TileMapData::TileMapData()
	:m_data(),
	m_size(0,0)
{
}

int32_t TileMapData::get(sf::Vector2u pos) const
{
	if (pos.x >= m_size.x || pos.y >= m_size.y)
		return -1;
	return m_data.at(pos.y * m_size.x + pos.x);
}

int32_t TileMapData::get(uint32_t x, uint32_t y) const
{
	return get(sf::Vector2u(x, y));
}

sf::Vector2u TileMapData::getSize() const
{
	return m_size;
}

const std::vector<sf::FloatRect> TileMapData::getRectFromArea(const sf::FloatRect& area, float tile_size) const
{
	std::vector<sf::FloatRect> rects;
	uint32_t x_begin = static_cast<uint32_t>(area.left / tile_size);
	uint32_t y_begin = static_cast<uint32_t>(area.top / tile_size);
	uint32_t x_end = static_cast<uint32_t>((area.left + area.width) / tile_size) + 1;
	uint32_t y_end = static_cast<uint32_t>((area.top + area.height) / tile_size) + 1;

	for (uint32_t y= y_begin; y < y_end; y++)
	{
		for (uint32_t x= x_begin; x < x_end; x++)
		{
			if (get(x, y) >= 0)
			{
				sf::FloatRect rect(tile_size * x, tile_size * y, tile_size, tile_size);
				rects.push_back(rect);
			}
		}
	}

	return rects;
}

bool TileMapData::loadFromFile(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		return false;

	file >> m_size.x >> m_size.y;
	m_data.resize(m_size.x * m_size.y);
	for (auto iter = m_data.begin(); iter != m_data.end(); iter++)
	{
		file >> *iter;
	}

	return true;
}
