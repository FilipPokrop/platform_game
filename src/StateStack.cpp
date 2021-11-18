#include "StateStack.h"

#include "GameState.h"

#include <cassert>

StateStack::PendingChange::PendingChange(Action _action, StateID _id)
	:action(_action),
	id(_id)
{
}

StateStack::StateStack(State::Context* context)
	:m_state_stack(),
	m_pending_change_list(),
	m_factory(),
	m_conext(*context)
{
	registerState<GameState>(StateID::Game);
	pushState(StateID::Game);
	applyPendingChange();
}

void StateStack::pushState(StateID id)
{
	m_pending_change_list.push_back(PendingChange(Action::Push, id));
}

void StateStack::popState()
{
	m_pending_change_list.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
	m_pending_change_list.push_back(PendingChange(Action::Clear));
}

void StateStack::update(const sf::Time& dt)
{
	for (auto iter = m_state_stack.rbegin(); iter != m_state_stack.rend(); ++iter)
	{
		if (!(*iter)->update(dt))
			break;
	}
	applyPendingChange();
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto iter = m_state_stack.rbegin(); iter != m_state_stack.rend(); ++iter)
	{
		if (!(*iter)->handleEvent(event))
			break;
	}
	applyPendingChange();
}

void StateStack::handleEvents()
{
	for (auto iter = m_state_stack.rbegin(); iter != m_state_stack.rend(); ++iter)
	{
		if (!(*iter)->handleEvents())
			break;
	}
	applyPendingChange();
}

void StateStack::draw()
{
	for (auto iter = m_state_stack.begin(); iter != m_state_stack.end(); ++iter)
	{
		(*iter)->draw();
	}
}

bool StateStack::isEmpty() const
{
	return m_state_stack.empty();
}

//State::Context* StateStack::getContext()
//{
//	return m_conext;
//}

State::Ptr StateStack::createState(StateID id)
{
	auto found = m_factory.find(id);
	assert(found != m_factory.end());

	return found->second();
}

void StateStack::applyPendingChange()
{
	for (auto& i : m_pending_change_list)
	{
		switch (i.action)
		{
		case Action::Push:
			m_state_stack.push_back(createState(i.id));
			break;

		case Action::Pop:
			m_state_stack.pop_back();
			break;
		case Action::Clear:
			m_state_stack.clear();
			break;
		default:
			break;
		}
	}

	m_pending_change_list.clear();
}
