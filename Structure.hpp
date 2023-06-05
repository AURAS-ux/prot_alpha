#pragma once
#include <SFML/Graphics.hpp>
#include "SETTINGS.hpp"
#include"Logger.hpp"
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

	void SetStructurePosition(float, float);
	void DrawStructure(sf::RenderTarget&);
	void SetStructureColor(sf::Color);
	sf::Color GetStructureColor();
	sf::RectangleShape* GetStructureShape();
	void RenderStructure(sf::RenderTarget*);
	static bool MouseIntersection(Structure* ,sf::Vector2i);
	static bool StrucutreIntersection(Structure* str1, Structure* str2);
};