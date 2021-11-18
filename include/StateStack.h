#pragma once

#include "State.h"
#include "StateIdentifiers.h"

#include <list>
#include <map>
#include <functional>

class StateStack
{
public:

	enum class Action
	{
		Push,
		Pop,
		Clear
	};


	StateStack(State::Context* context);

	template<typename T>
	void registerState(StateID id);

	void pushState(StateID id);
	void popState();
	void clearStates();

	void update(const sf::Time& dt);
	void handleEvent(const sf::Event& event);
	void handleEvents();
	void draw();

	bool isEmpty() const;

private:

	struct PendingChange
	{
		PendingChange(Action _action, StateID _id = StateID::None);

		Action action;
		StateID id;
	};

	State::Ptr createState(StateID id);
	void applyPendingChange();

private:

	std::list<State::Ptr> m_state_stack;
	std::list<PendingChange> m_pending_change_list;

	std::map<StateID, std::function<State::Ptr()> > m_factory;
	
	State::Context& m_conext;
};

template<typename T>
inline void StateStack::registerState(StateID id)
{
	m_factory[id] = [this]() {
		return State::Ptr(new T(this, m_conext));
	};
}
