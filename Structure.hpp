#pragma once
#include <SFML/Graphics.hpp>
#include "SETTINGS.hpp"
#include"Logger.hpp"
#include "Time.hpp"
class Structure
{
private:
	sf::RectangleShape* structureShape;
	sf::Vector2f structureSize;
	uint8_t structureType=0;

	void InnitVariables(float,float, uint8_t);
	void InitStructure();
	void Shoot(std::vector<sf::CircleShape>&);
public:
	Structure(float,float, uint8_t);
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
	uint8_t GetStructureType();
	void UpdateBullets(float dt, std::vector<sf::CircleShape>&);
	sf::Color SetBulletColor();
};