#include "Animation.h"

Animation::Animation(const sf::Texture& texture)
	:m_sprite(texture)
{
}

void Animation::update(const sf::Time& dt)
{
	m_time += dt;
	while (m_time>=m_current_animation.frame_time)
	{
		if (++m_current_frame >= m_current_animation.frames)
			//m_current_frame++;
			
			m_current_frame = m_current_animation.repeat ? 0 : m_current_frame - 1;
			
		m_time -= m_current_animation.frame_time;
		sf::IntRect rect = m_current_animation.rect;
		rect.left = rect.left + abs(rect.width) * m_current_frame;

		m_sprite.setTextureRect(rect);
	}
}

void Animation::addAnimation(uint32_t id, const AnimationData& data)
{
	std::unique_ptr<AnimationData> data_ptr(new AnimationData(data));
	auto inserted = m_animations_data.insert(std::make_pair(id, std::move(data_ptr)));
	assert(inserted.second);
}

void Animation::setAnimation(uint32_t id)
{
	m_current_animation = get(id);
	reset();
}

const Animation::AnimationData& Animation::get(uint32_t id) const
{
	auto found = m_animations_data.find(id);
	assert(found != m_animations_data.end());

	return *found->second;
	// TODO: tu wstawić instrukcję return
}

void Animation::reset()
{
	m_time = sf::Time::Zero;
	m_current_frame = 0;
	m_sprite.setTextureRect(m_current_animation.rect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(m_sprite, states);
}

Animation::AnimationData::AnimationData(const sf::IntRect& _rect, const sf::Time& _time, uint16_t _frames, bool _repeat)
	:rect(_rect),
	frame_time(_time),
	frames(_frames),
	repeat(_repeat)
{
}
