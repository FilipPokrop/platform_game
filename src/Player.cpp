#include "Player.h"

Player::Player(const std::string& filename)
{
	if (filename != "")
	{
		loadFromFile(filename);
	}
	//m_key_binding[sf::Keyboard::Space] = Action::Jump;
	//m_key_binding[sf::Keyboard::Left] = Action::MoveLeft;
	//m_key_binding[sf::Keyboard::Right] = Action::MoveRight;

	//assignKey(sf::Keyboard::Up, Action::Jump);

	bindActions();
}

void Player::loadFromFile(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);

	if(file.fail())
		throw std::runtime_error("Player::loadFromFile - Failed to load " + filename);
	
	while (file)
	{
		int action, key;
		file >> action >> key;
		assignKey((sf::Keyboard::Key)key, (Player::Action)action);
	}

	file.close();

}

void Player::bindActions()
{
	m_action_binding[Action::Jump] = &MainCharacter::jump;
	m_action_binding[Action::MoveLeft] = &MainCharacter::moveLeft;
	m_action_binding[Action::MoveRight] = &MainCharacter::moveRight;
	m_action_binding[Action::CatchWall] = &MainCharacter::catchWall;
}

void Player::assignKey(sf::Keyboard::Key key, Action action)
{
	for (auto iter = m_key_binding.begin(); iter != m_key_binding.end();)
	{
		if (iter->second == action)
			iter = m_key_binding.erase(iter);
		else
			iter++;
	}
	m_key_binding[key] = action;
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case Action::Jump:
	case Action::MoveLeft:
	case Action::MoveRight:
	case Action::CatchWall:
		return true;
		break;
	default:
		return false;
		break;
	}
	//return false;
}

void Player::handleEvent(const sf::Event& event, MainCharacter* character)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto action = m_key_binding.find(event.key.code);
		if (action != m_key_binding.end() && !isRealtimeAction(action->second))
		{
			auto found = m_action_binding.find(action->second);
			assert(found != m_action_binding.end());
			found->second(character);
		}
	}
}

void Player::handleEvents(MainCharacter* character)
{
	for (auto iter = m_key_binding.begin(); iter != m_key_binding.end(); ++iter)
	{
		if (isRealtimeAction(iter->second) && sf::Keyboard::isKeyPressed(iter->first))
		{
			auto found = m_action_binding.find(iter->second);
			assert(found != m_action_binding.end());

			found->second(character);
		}
			
	}
}
