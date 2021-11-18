#include "State.h"

#include "StateStack.h"

State::Context::Context(TextureHolder& _texture_holder, FontHolder& _font_holder, sf::RenderWindow& _window)
	:texture_holder(&_texture_holder),
	font_holder(&_font_holder),
	window(&_window)
{

}

State::State(StateStack* stack, Context& context)
	:m_stack(stack),
	m_context(&context)
{
}

void State::reqestStackPush(StateID id)
{
	m_stack->pushState(id);
}

void State::reqestStackPop()
{
	m_stack->popState();
}

void State::reqestStackClear()
{
	m_stack->clearStates();
}

State::Context& State::getContext()
{
	return *m_context;
}
