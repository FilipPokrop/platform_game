#pragma once

#include <SFML/Graphics.hpp>

class Lives:public sf::Drawable, public sf::Transformable
{
public:
	Lives(const sf::Texture& texture);

	void update(int lives);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertex;
	const sf::Texture& m_texture;
	int m_lives;
};

