#pragma once

#include <SFML/Graphics.hpp>

#include "TileMapData.h"

class TileMap:public sf::Drawable, sf::Transformable
{
public:
	TileMap(const sf::Texture& texture, sf::Vector2f map_size = sf::Vector2f(640,480), float tile_size = 16.f);
	void setTexture(const sf::Texture& texture);
	void update(const sf::Vector2f& player_pos);
	const TileMapData& getData();

	sf::Vector2f getScreenSize();

	sf::Vector2f getCenter();
	void setCenter(const sf::Vector2f& player_pos);

	sf::Vector2f getWorldSize();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	TileMapData m_data;
	const sf::Texture& m_texture;
	sf::VertexArray m_vertex;
	sf::Vector2f m_size;
	sf::Vector2f m_center;
	float m_tile_size;
	sf::Vector2u m_size_in_tile;

};

