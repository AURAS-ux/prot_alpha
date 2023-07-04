#include "Structure.hpp"

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
