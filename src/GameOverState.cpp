#include "GameOverState.h"

GemeOverState::GemeOverState(StateStack* stack, Context& context)
	:State(stack, context),
	m_rect(sf::Vector2f(getContext().window->getSize())),
	m_game_over_text("GAME OVER", context.font_holder->get(Fonts::Menu), 130),
	m_info_text("PRESS SPACE TO PLAY AGAIN", context.font_holder->get(Fonts::Menu),39)
{
	m_rect.setFillColor(sf::Color(31, 31, 31, 191));
	m_game_over_text.setOrigin(sf::Vector2f(m_game_over_text.getGlobalBounds().width, m_game_over_text.getGlobalBounds().height) * 0.5f);
	m_info_text.setOrigin(sf::Vector2f(m_info_text.getGlobalBounds().width, m_info_text.getGlobalBounds().height) * 0.5f);

	m_game_over_text.setPosition(sf::Vector2f(context.window->getSize()) * 0.5f + sf::Vector2f(0, -64.f));
	m_info_text.setPosition(sf::Vector2f(context.window->getSize()) * 0.5f + sf::Vector2f(0, 128.f));

}

GemeOverState::~GemeOverState()
{
}

bool GemeOverState::update(const sf::Time& dt)
{
	return false;
}

bool GemeOverState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
	{
		reqestStackClear();
		reqestStackPush(StateID::Game);
		//return true;
	}
	return true;
}

bool GemeOverState::handleEvents()
{
	return true;
}

void GemeOverState::draw()
{
	getContext().window->draw(m_rect);
	getContext().window->draw(m_game_over_text);
	getContext().window->draw(m_info_text);
}
