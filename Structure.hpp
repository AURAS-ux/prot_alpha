#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Structure
{
private:
	sf::RectangleShape* structureShape;
	sf::Vector2f structureSize;

	void InnitVariables(float,float);
	void InitStructure();
public:
	Structure(float,float);
	~Structure();
	Structure(const Structure& structure);

	void SetStructurePosition(float x, float y);
	void DrawStructure(sf::RenderTarget& tr);
	void SetStructureColor(sf::Color);
	sf::Color GetStructureColor();
	sf::RectangleShape* GetStructureShape();
	void RenderStructure(sf::RenderTarget*);
};

