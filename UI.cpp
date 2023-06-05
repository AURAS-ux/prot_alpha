#include "UI.hpp"

#include "Logger.hpp"

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
	Logger::Println("Destructor for UI called");
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
		Logger::PrintError("No font at path< "+*path.c_str());
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

