#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class UI
{
public:
	UI();
	UI(std::string);
	~UI();
	sf::Text* getText();
	void DrawText(sf::RenderTarget*,sf::Vector2f);
	void InnitText(std::string, int, sf::Color);
	void SetText(std::string);
private:
	sf::Font* uiFont;
	sf::Text* text;
	void LoadFontResource(std::string path);
};

