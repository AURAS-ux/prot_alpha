#pragma once
#include<SFML/Graphics.hpp>
#include<memory>

class TextureManager
{
public:
	TextureManager() = delete;
	~TextureManager() = delete;
	static void GetSprite(std::string, std::unique_ptr<sf::Texture>&);
	static void GetSpritesVector(std::vector<std::string>, std::vector<std::unique_ptr<sf::Texture>>&);
};

