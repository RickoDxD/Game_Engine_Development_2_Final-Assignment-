#pragma once
#include <string>

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert,
		TitleScreenBackground,
		TitleScreenPrompt,
		MainMenuBackground,
		MainMenuTitle,
		MainMenuStartButton,
		MainMenuQuitButton,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

//typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;


typedef ResourceHolder<std::string, Textures::ID> TextureHolder;