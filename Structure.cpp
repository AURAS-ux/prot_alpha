#include "Structure.hpp"

void Structure::InnitVariables(float width, float height)
{
	this->structureSize = sf::Vector2f(width, height);
}

void Structure::InitStructure()
{
	this->structureShape = new sf::RectangleShape(this->structureSize);
	this->structureShape->setFillColor(sf::Color::Red);
}

Structure::Structure(float width, float height)
{
	this->InnitVariables(width, height);
	this->InitStructure();
}

Structure::~Structure()
{
	if(!SNOOZE)
	std::cout << "Structure destructor called"<<std::endl;
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
