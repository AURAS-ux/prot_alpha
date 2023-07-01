#include "MainGrid.hpp"

#include <iostream>

#include "Logger.hpp"

MainGrid::MainGrid()
{
	gridLines = std::vector<sf::RectangleShape*>();

	for(int i=LEFT_OFFSET;i<WIDTH-GRID_OFFSET;i+=CELL_SIZE)
	{
		for(int j=TOP_OFFSET;j<HEIGHT-GRID_OFFSET;j+=CELL_SIZE)
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
	Logger::Println("Called the Grid destructor");
	for(const sf::RectangleShape* cell:gridLines)
	{
		delete cell;
	}
}

void MainGrid::MainGridDraw(sf::RenderTarget* tr) const
{
	if(SHOW_GRID)
	{
		for(const sf::RectangleShape* cell:gridLines)
		{
			tr->draw(*cell);
		}
	}
}

std::map<std::string, float> MainGrid::GetGridBounds()
{
	float startX = 0;
	float startY = 0;
	float gridWidth = 0;
	float gridHeight = 0;
	std::map<std::string, float> bounds;

	startX = (gridLines.size() != 0) ? gridLines.at(0)->getGlobalBounds().getPosition().x  : 0;
	startY = (gridLines.size() != 0) ? gridLines.at(0)->getGlobalBounds().getPosition().y : 0;
	gridWidth = (gridLines.size() != 0) ? gridLines.back()->getPosition().x - gridLines.front()->getPosition().x : 0;
	gridHeight = (gridLines.size() != 0) ? gridLines.back()->getPosition().y - gridLines.front()->getPosition().y : 0;

	bounds["StartX"] = startX;
	bounds["StartY"] = startY;
	bounds["Width"] = gridWidth +CELL_SIZE;
	bounds["Height"] = gridHeight;

	return bounds;
}

void MainGrid::PrintGridBounds()
{
	std::map < std::string, float> bounds = this->GetGridBounds();
	std::map<std::string, float>::iterator it = bounds.begin();

	for(auto& bound:bounds)
	{
		std::cout << bound.first << " " << bound.second << std::endl;
	}
}

bool MainGrid::IsMouseInGrid(sf::Vector2f pos)
{
	std::map < std::string, float> bounds = this->GetGridBounds();
	float X = bounds.find("StartX")->second + bounds.find("Width")->second;
	float Y = bounds.find("StartY")->second + bounds.find("Height")->second;

	sf::FloatRect gridRect = sf::FloatRect(sf::Vector2<float>(bounds.find("StartX")->second, bounds.find("StartY")->second), sf::Vector2<float>(X,Y));

	if (gridRect.contains(pos))
	{
		return true;
	}
	else return false;
}
