#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <cassert>

class Animation: public sf::Drawable, public sf::Transformable
{
public:
	struct AnimationData
	{
		AnimationData(const sf::IntRect& _rect=sf::IntRect(0,0,0,0), const sf::Time& _time=sf::Time::Zero, uint16_t _frames = 0, bool _repeat = true);
		sf::IntRect rect;
		sf::Time frame_time;
		uint16_t frames;
		bool repeat;
	};

	Animation(const sf::Texture& texture);

	void update(const sf::Time& dt);
	void addAnimation(uint32_t id, const AnimationData& data);

	void setAnimation(uint32_t id);
	const AnimationData& get(uint32_t id) const;

	void reset();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	sf::Sprite m_sprite;
	AnimationData m_current_animation;
	std::map<uint32_t, std::shared_ptr<AnimationData>> m_animations_data;
	sf::Time m_time;
	uint16_t m_current_frame;
};

