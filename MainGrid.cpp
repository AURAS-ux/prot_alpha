#include "MainGrid.hpp"
#include "FileManager.hpp"
#include <iostream>
#include "TextureManager.hpp"
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
			cell->setPosition(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)));
			cell->setFillColor(sf::Color::Transparent);
			cell->setOutlineThickness(1.5f);
			cell->setOutlineColor(sf::Color(44, 24, 14, 70));
			gridLines.push_back(cell);
		}
	}

	InitMargins();
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

void MainGrid::DrawMargins(sf::RenderTarget* tr)
{
	tr->draw(*topMargin.get());
	tr->draw(*bottomMargin.get());
}

void MainGrid::InitMargins()
{
	topMargin = std::make_unique<sf::RectangleShape>();
	bottomMargin = std::make_unique<sf::RectangleShape>();
	marginTexture = std::make_unique<sf::Texture>();
	topMargin->setPosition(sf::Vector2f(this->GetGridBounds().find("StartX")->second, this->GetGridBounds().find("StartY")->second));
	topMargin->setSize(sf::Vector2f(this->GetGridBounds().find("Width")->second, 10));
	TextureManager::GetSprite(FileManager::GetFilePath("61.png"), marginTexture);
	marginTexture->setRepeated(true);
	topMargin->setTexture(marginTexture.get());

	bottomMargin->setPosition(sf::Vector2f(this->GetGridBounds().find("StartX")->second, this->GetGridBounds().find("StartY")->second + this->GetGridBounds().find("Height")->second + CELL_SIZE));
	bottomMargin->setSize(topMargin.get()->getSize());
	bottomMargin->setTexture(marginTexture.get());
}

bool MainGrid::CheckContent(sf::RectangleShape* cell, std::vector<std::unique_ptr<Structure>>& structures)
{
	bool foundCollision = false;
	for(const std::unique_ptr<Structure>& str: structures)
	{
		if (cell->getGlobalBounds().findIntersection(str->GetStructureShape()->getGlobalBounds()))
		{
			foundCollision = true; 
		}
	}
	return foundCollision;
}

std::vector<sf::RectangleShape*> MainGrid::GetGridLines()
{
	return this->gridLines;
}

bool MainGrid::HighlightCurrentCell(sf::RectangleShape* cell,sf::Vector2f mousePos)
{
	if (cell->getGlobalBounds().contains(mousePos))
	{
		return true;
	}
	else return false;
}
