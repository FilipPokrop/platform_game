#pragma once

#include "State.h"

class GemeOverState : public State
{
public:
	GemeOverState(StateStack* stack, Context& context);

	~GemeOverState();

	virtual bool update(const sf::Time& dt);
	virtual bool handleEvent(const sf::Event& event);
	virtual bool handleEvents();
	virtual void draw();

private:
	sf::RectangleShape m_rect;
	sf::Text m_game_over_text;
	sf::Text m_info_text;

};