#include "Structure.hpp"
#include "FileManager.hpp"
#include "TextureManager.hpp"

void Structure::InnitVariables(float width, float height, uint8_t type)
{
	this->structureSize = sf::Vector2f(width, height);
	this->structureType = type;
}

void Structure::InitStructure()
{
	this->structureShape = new sf::RectangleShape(this->structureSize);
	this->structureShape->setFillColor(sf::Color::White);
	this->structureShape->setOrigin(sf::Vector2f(this->structureShape->getGlobalBounds().top, this->structureShape->getGlobalBounds().height));
}


void Structure::Shoot(std::vector<sf::CircleShape>& bullets)
{
	sf::CircleShape bullet =  sf::CircleShape(40.f);
	bullet.setFillColor(SetBulletColor());
	float centerPosX = this->structureShape->getGlobalBounds().left + this->structureShape->getGlobalBounds().width/2;
	float centerPosY = this->structureShape->getGlobalBounds().top + this->structureShape->getGlobalBounds().height/2 - 25;
	bullet.setPosition(sf::Vector2f(centerPosX,centerPosY));
	bullets.push_back(bullet);
}

Structure::Structure(float width, float height, uint8_t type = 0)
{
	this->InnitVariables(width, height,type);
	this->InitStructure();
}

Structure::~Structure()
{
	Logger::Println("Structure destructor called");
	if(this != nullptr)
	delete this->structureShape;
}

Structure::Structure(const Structure& structure)
{
	this->structureShape = structure.structureShape;
	this->structureSize = structure.structureSize;
}

void Structure::SetStructurePosition(float x, float y)
{
	this->structureShape->setPosition(sf::Vector2f(x, y));
}

void Structure::DrawStructure(sf::RenderTarget& tr)
{
	tr.draw(*this->structureShape);
}

void Structure::SetStructureColor(sf::Color colorParam)
{
	this->structureShape->setFillColor(colorParam);
}

sf::Color Structure::GetStructureColor()
{
	return this->structureShape->getFillColor();
}

sf::RectangleShape* Structure::GetStructureShape()
{
	return this->structureShape;
}

void Structure::RenderStructure(sf::RenderTarget* tr)
{
	tr->draw(*this->structureShape);
}

bool Structure::MouseIntersection(Structure* str,sf::Vector2i mousePosition)
{
	return str->structureShape->getGlobalBounds().contains(sf::Vector2f(mousePosition.x,mousePosition.y));
}

bool Structure::StrucutreIntersection(Structure* str1, Structure* str2)
{
	return (str1->GetStructureShape()->getGlobalBounds().findIntersection(str2->GetStructureShape()->getGlobalBounds())) != std::nullopt;
}

uint8_t Structure::GetStructureType()
{
	return this->structureType;
}

void Structure::UpdateBullets(float dt, std::vector<sf::CircleShape>& bullets)
{
	if(rand()%SHOT_PROBABILITY == 1 && structureType != 0) this->Shoot(bullets);
}

sf::Color Structure::SetBulletColor()
{
	switch (structureType)
	{
	case 1:
		return sf::Color(238, 137, 0, 255);
	case 2:
		return sf::Color(69, 191, 85, 255);
	case 3:
		return sf::Color(155, 17, 41, 255);
	case 4:
		return sf::Color(145, 201, 232, 255);
	default: sf::Color::White;
	}
}
