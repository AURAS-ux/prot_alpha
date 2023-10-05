#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include"SETTINGS.hpp"
#include"Structure.hpp"
#include<map>
/**
 * \brief Grid Gnereator
 */
class MainGrid
{
public:
	MainGrid();
	~MainGrid();
	void MainGridDraw(sf::RenderTarget*) const;
	std::map<std::string,float> GetGridBounds();
	void PrintGridBounds();
	bool IsMouseInGrid(sf::Vector2f);
	void DrawMargins(sf::RenderTarget*);
	bool CheckContent(sf::RectangleShape* ,std::vector<std::unique_ptr<Structure>>&);
	std::vector<sf::RectangleShape*> GetGridLines();
	bool HighlightCurrentCell(sf::RectangleShape*,sf::Vector2f);
private:
	std::vector<sf::RectangleShape*> gridLines;
	std::unique_ptr<sf::RectangleShape> topMargin;
	std::unique_ptr<sf::RectangleShape> bottomMargin;
	std::unique_ptr<sf::Texture> marginTexture;
	void InitMargins();
};

