#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include"SETTINGS.hpp"
/**
 * \brief Grid Gnereator
 */
class MainGrid
{
public:
	MainGrid();
	~MainGrid();
	void MainGridDraw(sf::RenderTarget*) const;
private:
	std::vector<sf::RectangleShape*> gridLines;
};

