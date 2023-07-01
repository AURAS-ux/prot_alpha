#include "Game.hpp"

void Game::InitVars()
{
	this->ev = sf::Event();
	//Variable innit Begin
	this->res1Score = 0;
	this->scoreMultiplyer = 0.005f;
	this->fontPath = "assets\\space age.ttf";
	this->resourceUI = new UI(fontPath);
	this->resourceUI->InnitText("Resource1:", RESOURCE_FONT_SIZE, sf::Color::White);
	this->gameUI = new UI(fontPath);
	this->grid = new MainGrid();
	this->structures = std::vector<std::unique_ptr<Structure>>();
	this->spaceShipTextures = std::vector<std::unique_ptr<sf::Texture>>(5);
	TextureManager::GetSpritesVector(std::vector<std::string>{"assets\\images\\Spaceships\\03\\Spaceship_03_NAVY BLUE.png",
		"assets\\images\\Spaceships\\04\\Spaceship_04_RED.png", "assets\\images\\Spaceships\\05\\Spaceship_05_ORANGE.png",
		"assets\\images\\Spaceships\\06\\Spaceship_06_BLUE.png", "assets\\images\\Spaceships\\02\\Spaceship_02_GREEN.png"}, spaceShipTextures);
	this->settings.antialiasingLevel = 8;
	this->rotationAngle = sf::degrees(90);
	this->backgroundTexture = std::make_unique<sf::Texture>();
	this->backgroundSprite = std::make_unique<sf::Sprite>();
	TextureManager::GetSprite("assets\\images\\background\\Space Background.png", backgroundTexture);
 	this->backgroundSprite->setTexture(*backgroundTexture.get());
	//Variable innit End
}

void Game::InitWindow(int width, int height, int bitsPerPixel, bool isFullScreen)
{
	this->window = new sf::RenderWindow();
	this->videoMode = sf::VideoMode(sf::Vector2u(width, height), bitsPerPixel);
	if (isFullScreen)
	{
		this->window->create(this->videoMode, "PR_A", sf::Style::Fullscreen,settings);
	}
	else
	{
		this->window->create(this->videoMode, "PR_A", sf::Style::Titlebar);
	}

	iconImage.loadFromFile("assets\\images\\icons\\icon.png");
	this->window->setIcon(sf::Vector2u(iconImage.getSize().x,iconImage.getSize().y),iconImage.getPixelsPtr());


}

bool Game::IsOpen()
{
	return this->window->isOpen();
}

void Game::Update()
{
	while (this->IsOpen())
	{
		this->DrawWindow();
		this->PollEvents();
		//Costum updates Begin
		this->gameUI->InnitText(std::to_string(static_cast<int>(res1Score)), RESOURCE_FONT_SIZE, sf::Color::White);
		this->IncreaseScore(res1Score, scoreMultiplyer, structures);
		gameUI->SetSelectionIcons(spaceShipTextures);
		this->GetSelectedStructure();
		//Costum updates End
	}
}

Game::Game()
{
	this->InitWindow(WIDTH, HEIGHT, BITSPERPIXEL, FULLSCREEN);
	this->InitVars();
}

Game::Game(int width, int height, int bitsPerPixel, bool isFullScreen)
{
	this->InitWindow(width, height, bitsPerPixel, isFullScreen);
	this->InitVars();
}

void Game::DrawWindow()
{
	this->window->clear();
	//Custom objects to draw Begin
	this->window->draw(*backgroundSprite.get());
	this->resourceUI->DrawText(this->window, sf::Vector2f(20, 20));
	this->gameUI->DrawText(this->window, sf::Vector2f(resourceUI->getText()->getPosition().x + resourceUI->getText()->getGlobalBounds().width, 20));
	this->grid->MainGridDraw(this->window);
	for(auto& temp:structures)
	{
		if(temp != nullptr)
		{
			temp->DrawStructure(*this->window);
		}
	}
	gameUI->DrawSelectionMenu(*this->window);
	//Custom objects to draw End
	this->window->display();
}

void Game::PollEvents()
{
	while (this->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Logger::Println("Window destroyed",0);
			this->window->~RenderWindow();
		}
		//Custom poll for events Begin
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->grid->IsMouseInGrid(sf::Vector2f(sf::Mouse::getPosition())))
			this->BuildStructure();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->grid->IsMouseInGrid(sf::Vector2f(sf::Mouse::getPosition())))
			this->DestroyStructure(this->structures);

		//Custom poll for events End
	}
}

void Game::BuildStructure()
{
	std::unique_ptr<Structure> str = std::make_unique<Structure>(STRUCTURE_SIZE, STRUCTURE_SIZE);
	if(selectedStructure != nullptr)
		str->GetStructureShape()->setTexture(selectedStructure->getTexture());
	else return;
	str->GetStructureShape()->rotate(sf::degrees(90));
	sf::Vector2f structure_position = sf::Vector2f(
		CELL_SIZE * std::round((sf::Mouse::getPosition()                    .x) / CELL_SIZE) + (X_OFFSET * str->GetStructureShape()->
			getGlobalBounds()                                               .width),
		CELL_SIZE * std::round((sf::Mouse::getPosition()                    .y) / CELL_SIZE) + (Y_OFFSET * str->GetStructureShape()->
			getGlobalBounds()                                               .width)
	);
	str->SetStructurePosition(std::clamp(static_cast<int>(structure_position.x),LEFT_OFFSET,
	                                     WIDTH - X_RESTRAIN - GRID_OFFSET - static_cast<int>(str->GetStructureShape()->
		                                     getPosition()                  .x)), 
	                          std::clamp(static_cast<int>(structure_position.y),TOP_OFFSET,
	                                     HEIGHT - Y_RESTRAIN - static_cast<int>(str->GetStructureShape()->
		                                     getGlobalBounds()              .height)));
	if(CheckStructureInterection(str,structures))
	{
		structures.push_back(std::move(str));
	}
	
}

void Game::DestroyStructure(std::vector<std::unique_ptr<Structure>>& objects)
{
	for (std::unique_ptr<Structure>& str : structures)
	{
		if(str != nullptr && Structure::MouseIntersection(str.get(),sf::Mouse::getPosition()) == 1)
		{
			structures.erase(std::ranges::find(structures, str)); 
		}
	}
}

bool Game::CheckStructureInterection(std::unique_ptr<Structure>& object,std::vector<std::unique_ptr<Structure>>& objects)
{
	bool positionAvailable = true;
	for(std::unique_ptr<Structure>& str:objects)
	{
		if(Structure::StrucutreIntersection(object.get(),str.get()))
		{
			positionAvailable = false;
		}
	}

	return  positionAvailable;
}

void Game::IncreaseScore(float& score,float& scoreMultiplayer, std::vector<std::unique_ptr<Structure>>& strs)
{
	score += scoreMultiplayer * strs.size();
}

void Game::GetSelectedStructure()
{
	if (this->gameUI->CheckSelectionMenuClick(sf::Mouse::getPosition()) != nullptr)
	{
		selectedStructure = this->gameUI->CheckSelectionMenuClick(sf::Mouse::getPosition());
	}
}

Game::~Game()
{
	this->grid->~MainGrid();
	this->resourceUI->~UI();
	this->gameUI->~UI();
	if(selectedStructure != nullptr)
	this->selectedStructure->~RectangleShape();
	Logger::Println("Destructor for Game called");
}
