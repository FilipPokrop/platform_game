#include "Slime.h"
#include <limits>

Slime::Slime(const sf::Texture& texture)
	:Enemy(texture),
	m_current_state(MoveRight),
	m_left_border(std::numeric_limits<float>::lowest()),
	m_right_border(std::numeric_limits<float>::max())
{
	m_velocity.x = 50;
	m_animation.addAnimation(MoveLeft, Animation::AnimationData({ 0,0,44,30 }, sf::milliseconds(50), 10));
	m_animation.addAnimation(MoveRight, Animation::AnimationData({ 44,0,-44,30 }, sf::milliseconds(50), 10));
	m_animation.setAnimation(m_current_state);
}

Slime::Slime(const sf::Texture& texture, const TileMap& tile_map)
	:Slime(texture)
{
	setLeftBorder(tile_map);
	setRightBorder(tile_map);
}

sf::FloatRect Slime::getGlobalBounds() const
{
	return sf::FloatRect(getPosition()+sf::Vector2f(4,3),sf::Vector2f(36,27));
}

void Slime::setState()
{
	if (m_velocity.x > 0 && m_current_state != MoveRight)
	{
		m_current_state = MoveRight;
		m_animation.setAnimation(MoveRight);
	}

	else if(m_velocity.x < 0 && m_current_state != MoveLeft)
	{
		m_current_state = MoveLeft;
		m_animation.setAnimation(MoveLeft);
	}
}

void Slime::colisionWithPlayer(Entity* player, const Collision::ContactData& contact_data)
{
	if (contact_data)
	{
		//std::cout << "aaa";
		if (contact_data.contact_normal.y < 0)
		{
			kill();
			player->setVelocity(sf::Vector2f(player->getVelocity().x, -400.f));
		}


		else
		{
			player->hit(1,contact_data.contact_normal.x);
		}
	}
}

void Slime::setLeftBorder(const TileMap& tile_map)
{
	sf::FloatRect rect_to_check(getGlobalBounds());
	rect_to_check.width += rect_to_check.left;
	rect_to_check.left = 0;

	auto tiles = tile_map.getData().getRectFromArea(rect_to_check);

	sf::Vector2f size(getGlobalBounds().width, getGlobalBounds().height);
	sf::Vector2f half_size(size * 0.5f);
	sf::Vector2f dir(-getCenter().x, 0.f);
	for (auto iter = tiles.begin(); iter != tiles.end(); ++iter)
	{
		sf::FloatRect rect(sf::Vector2f(iter->left, iter->top) - half_size,
			sf::Vector2f(iter->width, iter->height) + size);

		Collision::ContactData data = Collision::rayVsRect(getCenter(), dir, rect);
		data.contact = (data.contact && (data.contact_time >= 0.f && data.contact_time < 1.f));

		if (data && data.contact_normal.x > 0 && data.contact_point.x > m_left_border)
		{
			m_left_border = data.contact_point.x;
		}
	}
	m_left_border -= half_size.x;
	rect_to_check.top += rect_to_check.height;
	rect_to_check.height = 1.f;
	auto tiles_under = tile_map.getData().getRectFromArea(rect_to_check);
	for (auto iter = tiles_under.rbegin(); iter != tiles_under.rend(); ++iter)
	{
		if (iter->left <= m_left_border)
			break;
		if (iter->left > (iter + 1)->left + (iter + 1)->width + 1.f)
		{
			m_left_border = iter->left;
			break;
		}

	}

	m_left_border -= 4.f;

}

void Slime::setRightBorder(const TileMap& tile_map)
{
	sf::FloatRect rect_to_check(getGlobalBounds());
	rect_to_check.width =tile_map.getData().getSize().x*tile_map.getTileSize()-rect_to_check.left;
	//rect_to_check.left = 0;

	auto tiles = tile_map.getData().getRectFromArea(rect_to_check);

	sf::Vector2f size(getGlobalBounds().width, getGlobalBounds().height);
	sf::Vector2f half_size(size * 0.5f);
	sf::Vector2f dir(tile_map.getData().getSize().x*tile_map.getTileSize() -getCenter().x, 0.f);
	for (auto iter = tiles.begin(); iter != tiles.end(); ++iter)
	{
		sf::FloatRect rect(sf::Vector2f(iter->left, iter->top) - half_size,
			sf::Vector2f(iter->width, iter->height) + size);

		Collision::ContactData data = Collision::rayVsRect(getCenter(), dir, rect);
		data.contact = (data.contact && (data.contact_time >= 0.f && data.contact_time < 1.f));

		if (data && data.contact_normal.x < 0 && data.contact_point.x < m_right_border)
		{
			m_right_border = data.contact_point.x;
		}
	}
	m_right_border += half_size.x;
	rect_to_check.top += rect_to_check.height;
	rect_to_check.height = 1.f;
	auto tiles_under = tile_map.getData().getRectFromArea(rect_to_check);
	for (auto iter = tiles_under.begin(); iter != tiles_under.end(); ++iter)
	{
		if (iter->left+iter->width >= m_right_border)
			break;
		if (iter->left + iter->width + 1.f < (iter + 1)->left)
		{
			m_right_border = iter->left + iter->width;
			break;
		}

	}
	m_right_border -= size.x;

	m_right_border -= 4.f;
}

void Slime::update(const sf::Time dt)
{
	
	m_acceleration.y = 0;
	Entity::update(dt);
	if (getPosition().x >= m_right_border || getPosition().x <= m_left_border)
	{
		setPosition(std::max(m_left_border, std::min(m_right_border, getPosition().x)), getPosition().y);
		m_velocity.x = -m_velocity.x;
	}
		
}
