#pragma once
#include <SFML/Graphics.hpp>
#include "SETTINGS.hpp"
class UI
{
public:
	UI(std::string);
	~UI();
	sf::Text* getText();
	void DrawText(sf::RenderTarget*,sf::Vector2f);
	void InnitText(std::string, int, sf::Color);
	void SetText(std::string);
	void DrawSelectionMenu(sf::RenderTarget&);
	sf::RectangleShape* CheckSelectionMenuClick(sf::Vector2i);
	void SetSelectionIcons(std::vector<std::unique_ptr<sf::Texture>>&);
private:
	sf::Font* uiFont;
	sf::Text* text;
	std::vector<sf::RectangleShape*> selectionMenu;
	sf::Vector2f selectionMenuPosition{ 1100,10 };
	void LoadFontResource(std::string path);
	void LoadSelectionMenu();
};

