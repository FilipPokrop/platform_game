#pragma once


#include "ResourceHolder.h"
namespace sf {
	class Texture;
	class Font;
}

enum class Textures
{
	Player,
	Duck,
	Map,
	WorldGui
};

enum class Fonts
{
	Menu
};

typedef ResourceHolder<sf::Texture, Textures> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts> FontHolder;