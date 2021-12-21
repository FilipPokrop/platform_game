#pragma once

#include "MainCharacter.h"

#include <map>
#include <fstream>
#include <functional>
#include <cassert>
#include <SFML/Window.hpp>



class Player
{
	enum class Action
	{
		MoveLeft,
		MoveRight,
		Jump,
		CatchWall
	};
public:
	Player(const std::string& filename = "");

	void loadFromFile(const std::string& filename = "");

	void bindActions();

	void assignKey(sf::Keyboard::Key key, Action action);

	bool isRealtimeAction(Action action);

	void handleEvent(const sf::Event& event, MainCharacter* character);
	void handleEvents(MainCharacter* character);



private:

	std::map<sf::Keyboard::Key, Action> m_key_binding;
	std::map<Action, std::function<void(MainCharacter*)>> m_action_binding;

};
