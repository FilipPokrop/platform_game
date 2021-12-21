#include "TileMap.h"
#include "..\include\TileMap.h"

TileMap::TileMap(const sf::Texture& texture, sf::Vector2f map_size, float tile_size)
	:m_data(),
	m_texture(texture),
	m_vertex(sf::PrimitiveType::Quads),
	m_size(map_size),
	m_center(map_size*0.5f),
	m_tile_size(tile_size),
	m_size_in_tile(sf::Vector2u((map_size /tile_size + sf::Vector2f(0.5f, 0.5f)))+sf::Vector2u(1,1))
{
	m_data.loadFromFile("media/maps/03.map");
	m_enemies.loadFromFile("media/enemies/03.ene");
	size_t size = m_size_in_tile.x * m_size_in_tile.y * 4;
	m_vertex.resize(size);
}

void TileMap::setTexture(const sf::Texture& texture)
{
	//m_texture = texture;
}

void TileMap::update(const sf::Vector2f& player_pos)
{
	setCenter(player_pos);
	sf::Vector2i begin((m_center - m_size * 0.5f) / m_tile_size);
	//begin+=sf::Vector2i(0, 0);
	uint32_t div = m_size_in_tile.x;
	for (size_t i = 0; i < m_vertex.getVertexCount() / 4; i++)
	{
		m_vertex[i * 4 + 0].position = sf::Vector2f((begin.x + (i % div + 0)) * m_tile_size, (begin.y + (i / div + 0)) * m_tile_size);
		m_vertex[i * 4 + 1].position = sf::Vector2f((begin.x + (i % div + 1)) * m_tile_size, (begin.y + (i / div + 0)) * m_tile_size);
		m_vertex[i * 4 + 2].position = sf::Vector2f((begin.x + (i % div + 1)) * m_tile_size, (begin.y + (i / div + 1)) * m_tile_size);
		m_vertex[i * 4 + 3].position = sf::Vector2f((begin.x + (i % div + 0)) * m_tile_size, (begin.y + (i / div + 1)) * m_tile_size);

		int32_t tile = m_data.get(begin.x + i % div, begin.y + i / div);
		sf::Color color = sf::Color::Transparent;
		if (tile > 0)
		{
			sf::Vector2f cord = sf::Vector2f(tile % (m_texture.getSize().x / (int)m_tile_size), tile / (m_texture.getSize().x / (int)m_tile_size)) * m_tile_size;
			m_vertex[i * 4 + 0].texCoords = cord;
			m_vertex[i * 4 + 1].texCoords = cord+sf::Vector2f(m_tile_size,0);
			m_vertex[i * 4 + 2].texCoords = cord + sf::Vector2f(m_tile_size, m_tile_size);
			m_vertex[i * 4 + 3].texCoords = cord + sf::Vector2f(0, m_tile_size);
			color = sf::Color::White;
		}
		
		m_vertex[i * 4 + 0].color = color;
		m_vertex[i * 4 + 1].color = color;
		m_vertex[i * 4 + 2].color = color;
		m_vertex[i * 4 + 3].color = color;

		
	}
}

const TileMapData& TileMap::getData() const
{
	return m_data;
}

EnemiesData& TileMap::getEnemies()
{
	return m_enemies;
}

sf::Vector2f TileMap::getScreenSize()
{
	return m_size;
}

sf::Vector2f TileMap::getCenter()
{
	

	return m_center;
}

void TileMap::setCenter(const sf::Vector2f& player_pos)
{
	sf::Vector2f half_screen(m_size * 0.5f);

	//m_center = player_pos;
	m_center.x = std::min(m_center.x, player_pos.x + half_screen.x * 0.5f);
	m_center.y = std::min(m_center.y, player_pos.y + half_screen.y * 0.5f);

	m_center.x = std::max(m_center.x, player_pos.x - half_screen.x * 0.5f);
	m_center.y = std::max(m_center.y, player_pos.y - half_screen.y * 0.5f);
				  
	m_center.x = std::min(m_center.x, m_data.getSize().x * m_tile_size - half_screen.x);
	m_center.y = std::min(m_center.y, m_data.getSize().y * m_tile_size - half_screen.y);

	m_center.x = std::max(m_center.x, half_screen.x);
	m_center.y = std::max(m_center.y, half_screen.y);

}

sf::Vector2f TileMap::getWorldSize()
{
	return sf::Vector2f(m_data.getSize())*m_tile_size;
}

float TileMap::getTileSize() const
{
	return m_tile_size;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_texture;

	target.draw(m_vertex, states);
}
