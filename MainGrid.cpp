#include "MainGrid.hpp"

MainGrid::MainGrid()
{
	gridLines = std::vector<sf::RectangleShape*>();

	for(int i=5;i<WIDTH-GRID_OFFSET;i+=CELL_SIZE)
	{
		for(int j=140;j<HEIGHT-GRID_OFFSET;j+=CELL_SIZE)
		{
			sf::RectangleShape* cell;
			cell = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			cell->setFillColor(sf::Color::Transparent);
			cell->setOutlineThickness(1.5f);
			cell->setOutlineColor(sf::Color::White);
			cell->setPosition(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)));
			gridLines.push_back(cell);
		}
	}
}

MainGrid::~MainGrid()
{
	std::cout << "Called the Grid destructor" << std::endl;
	for(const sf::RectangleShape* cell:gridLines)
	{
		delete cell;
	}
}

void MainGrid::MainGridDraw(sf::RenderTarget* tr) const
{
	for(const sf::RectangleShape* cell:gridLines)
	{
		tr->draw(*cell);
	}
}
