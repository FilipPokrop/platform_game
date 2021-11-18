#include "GameState.h"

GameState::GameState(StateStack* stack, Context& context)
	:State(stack, context),
	m_world(context.window, *context.texture_holder)
{

}

bool GameState::update(const sf::Time& dt)
{
	m_world.update(dt);
	if (m_world.endGame())
		reqestStackPop();
	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	return m_world.handleEvent(event);
}

bool GameState::handleEvents()
{
	return m_world.handleEvents();
}

void GameState::draw()
{
	m_world.draw();
}
