#include "UI.hpp"

#include "Logger.hpp"

UI::UI(std::string path)
{
	this->uiFont = new sf::Font();
	this->text = new sf::Text();
	this->LoadFontResource(path);
	this->LoadSelectionMenu();
}

UI::~UI()
{
	Logger::Println("Destructor for UI called");
	this->text->~Text();
	this->uiFont->~Font();
	for(auto& selMenuCell : selectionMenu)
	{
		selMenuCell->~RectangleShape();
	}
}

sf::Text* UI::getText()
{
	return this->text;
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
		Logger::PrintError(("No font at path< "+path).c_str());
	}
}

void UI::LoadSelectionMenu()
{
	for(int i=0;i<5;i++)
	{
		sf::RectangleShape* selMenuShape = new sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		selMenuShape->setPosition(sf::Vector2f(selectionMenuPosition.x + CELL_SIZE * i, selectionMenuPosition.y));
		/*selMenuShape->setFillColor(sf::Color::Transparent);
		selMenuShape->setOutlineThickness(1.5f);
		selMenuShape->setOutlineColor(sf::Color::White);*/
		selectionMenu.push_back(selMenuShape);
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

void UI::DrawSelectionMenu(sf::RenderTarget& tr)
{
	for(sf::RectangleShape* menuCell : selectionMenu)
	{
		tr.draw(*menuCell);
	}
}

sf::RectangleShape* UI::CheckSelectionMenuClick(sf::Vector2i mouse)
{
	sf::RectangleShape* clickedShape = nullptr;
	for(int i=0;i<selectionMenu.size();i++)
	{
		if(selectionMenu.at(i)->getGlobalBounds().contains(sf::Vector2f(mouse.x,mouse.y)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			clickedShape = selectionMenu.at(i);
		}
	}
	return clickedShape;
}

void UI::SetSelectionIcons(std::vector<std::unique_ptr<sf::Texture>>& iconTexture)
{
	for(int i=0;i<iconTexture.size();i++)
	{
		selectionMenu.at(i)->setTexture(iconTexture.at(i).get());
	}
}
