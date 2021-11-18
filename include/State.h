#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.h"
#include "StateIdentifiers.h"

class StateStack;

class State
{
public:

	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(TextureHolder& _texture_holder, FontHolder& _font_holder, sf::RenderWindow& _window);

		TextureHolder* texture_holder;
		FontHolder* font_holder;
		sf::RenderWindow* window;

	};

	State(StateStack* stack, Context& context);

	virtual ~State();

	//return true if update/handleEvent next state
	virtual bool handleEvent(const sf::Event& event) = 0;
	virtual bool handleEvents() = 0;
	virtual bool update(const sf::Time& dt) = 0;
	virtual void draw() = 0;

	void reqestStackPush(StateID id);
	void reqestStackPop();
	void reqestStackClear();

	Context& getContext();

private:
	StateStack* m_stack;
	Context* m_context;
};