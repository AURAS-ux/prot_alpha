#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include"SETTINGS.hpp"
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
private:
	std::vector<sf::RectangleShape*> gridLines;
};

