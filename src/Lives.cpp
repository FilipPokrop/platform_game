#include "Lives.h"

Lives::Lives(const sf::Texture& texture)
	:m_vertex(sf::Quads,40),
	m_texture(texture),
	m_lives(0)
{
	setPosition(952, 8);
	for (size_t i = 0; i < m_vertex.getVertexCount() / 4; i++)
	{
		m_vertex[i * 4 + 0].position = sf::Vector2f((i + 0), 0) * 32.f;
		m_vertex[i * 4 + 1].position = sf::Vector2f((i + 1), 0) * 32.f;
		m_vertex[i * 4 + 2].position = sf::Vector2f((i + 1), 1) * 32.f;
		m_vertex[i * 4 + 3].position = sf::Vector2f((i + 0), 1) * 32.f;

		m_vertex[i * 4 + 0].texCoords = sf::Vector2f(0.f, 0.f) * 16.f;
		m_vertex[i * 4 + 1].texCoords = sf::Vector2f(1.f, 0.f) * 16.f;
		m_vertex[i * 4 + 2].texCoords = sf::Vector2f(1.f, 1.f) * 16.f;
		m_vertex[i * 4 + 3].texCoords = sf::Vector2f(0.f, 1.f) * 16.f;

	}
}

void Lives::update(int lives)
{
	if (m_lives == lives)
		return;

	m_lives = lives;
	if (m_lives < 0)
		return;
	for (size_t i = 0; i < m_vertex.getVertexCount() / 4; i++)
	{
		sf::Color color = i >= m_lives ? sf::Color::Transparent : sf::Color::White;
		m_vertex[i * 4 + 0].color = color;
		m_vertex[i * 4 + 1].color = color;
		m_vertex[i * 4 + 2].color = color;
		m_vertex[i * 4 + 3].color = color;
	}


}

void Lives::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &m_texture;

	target.draw(m_vertex, states);
}
