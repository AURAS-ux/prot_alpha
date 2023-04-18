#include "UI.hpp"

UI::UI()
{

}

UI::UI(std::string path)
{
	this->uiFont = new sf::Font();
	this->text = new sf::Text();
	this->LoadFontResource(path);
}

UI::~UI()
{
	std::cout << "Destructor for UI called" << std::endl;
	this->text->~Text();
	this->uiFont->~Font();
}

void UI::DrawText(sf::RenderTarget* tr,sf::Vector2f pos)
{
	this->text->setPosition(pos);
	tr->draw(*this->text);
}

void UI::LoadFontResource(std::string path)
{
	if(!uiFont->loadFromFile(path))
	{
		sf::err();
		std::cerr << "No font at path< " << path;
	}
}

void UI::InnitText(std::string content, int size, sf::Color color)
{
	this->text->setFont(*uiFont);
	this->text->setString(content);
	this->text->setCharacterSize(size);
	this->text->setFillColor(color);
}

void UI::SetText(std::string content)
{
	this->text->setString(content);
}
