#pragma once

#include <vector>
#include <fstream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
class TileMapData
{
public:
	TileMapData();
	int32_t get(sf::Vector2u pos) const;
	int32_t get(uint32_t x, uint32_t y) const;

	sf::Vector2u getSize() const;

	const std::vector<sf::FloatRect> getRectFromArea(const sf::FloatRect& area, float tile_size = 16.f) const;

	bool loadFromFile(std::string filename);

private:
	std::vector<int32_t> m_data;
	sf::Vector2u m_size;


};

