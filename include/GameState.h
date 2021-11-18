#pragma once

#include "State.h"
#include "World.h"

class GameState : public State
{
public:
	GameState(StateStack* stack, Context& context);

	virtual bool update(const sf::Time& dt);
	virtual bool handleEvent(const sf::Event& event);
	virtual bool handleEvents();
	virtual void draw();

private:
	World m_world;

	
};