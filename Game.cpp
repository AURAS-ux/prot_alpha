#include "Game.hpp"

#include "FileManager.hpp"

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
	spaceShipTexturesNames.push_back(FileManager::GetFilePath("Spaceship_03_NAVY BLUE.png"));
	spaceShipTexturesNames.push_back(FileManager::GetFilePath("Spaceship_05_ORANGE.png"));
	spaceShipTexturesNames.push_back(FileManager::GetFilePath("Spaceship_02_GREEN.png"));
	spaceShipTexturesNames.push_back(FileManager::GetFilePath("Spaceship_04_RED.png"));
	spaceShipTexturesNames.push_back(FileManager::GetFilePath("Spaceship_06_BLUE.png"));
	TextureManager::GetSpritesVector(spaceShipTexturesNames, spaceShipTextures);
	this->settings.antialiasingLevel = 8;
	this->rotationAngle = sf::degrees(90);
	this->backgroundTexture = std::make_unique<sf::Texture>();
	this->backgroundSprite = std::make_unique<sf::Sprite>();
	TextureManager::GetSprite(FileManager::GetFilePath("Space Background.png"), backgroundTexture);
 	this->backgroundSprite->setTexture(*backgroundTexture.get());
	this->deltaTime = time.GetDeltaTime();
	srand(deltaTime);
	this->structureBullets = std::vector<sf::CircleShape>();
	this->bulletTexture = std::make_unique<sf::Texture>();
	TextureManager::GetSprite(FileManager::GetFilePath("laser_01.png"), bulletTexture);
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

	if (!iconImage.loadFromFile(FileManager::GetFilePath("icon.png")))
		Logger::PrintError("error loading icon", 0);
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

		this->deltaTime = time.GetDeltaTime();
		this->HandleBulletsUpdate();
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
	for(sf::CircleShape bullet:structureBullets)
	{
		this->window->draw(bullet);
	}
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
	std::unique_ptr<Structure> str = std::make_unique<Structure>(STRUCTURE_SIZE, STRUCTURE_SIZE,selectedStructure.structureType);
	if(selectedStructure.selectedShape != nullptr)
		str->GetStructureShape()->setTexture(selectedStructure.selectedShape->getTexture());
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
		                                     getPosition().x)), 
	                          std::clamp(static_cast<int>(structure_position.y),TOP_OFFSET,
	                                     HEIGHT - Y_RESTRAIN - static_cast<int>(str->GetStructureShape()->
		                                     getGlobalBounds().height)));
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
	int nrOfStructures = 0;
	for(auto& str : strs)
	{
		if(str.get()->GetStructureType() == 0)
		{
			nrOfStructures++;
		}
	}
	score += scoreMultiplayer * nrOfStructures;
}

void Game::GetSelectedStructure()
{
	if (this->gameUI->CheckSelectionMenuClick(sf::Mouse::getPosition()).selectedShape != nullptr)
	{
		selectedStructure = this->gameUI->CheckSelectionMenuClick(sf::Mouse::getPosition());
	}
}

bool OutScreenBullet(sf::CircleShape bullet)
{
	return bullet.getPosition().x > WIDTH;
}

void Game::CleanBullets()
{
	for(sf::CircleShape& bullet : structureBullets)
	{
		structureBullets.erase(
			std::remove_if(structureBullets.begin(), structureBullets.end(), OutScreenBullet),
			structureBullets.end());
	}
}

void Game::HandleBulletsUpdate()
{
	for (auto& str : structures)
		str.get()->UpdateBullets(deltaTime, structureBullets);
	for (auto& bullet : structureBullets)
	{
		bullet.setTexture(bulletTexture.get());
		bullet.move(sf::Vector2f(1000 * deltaTime, 0));
	}
	this->CleanBullets();
}

Game::~Game()
{
	this->grid->~MainGrid();
	this->resourceUI->~UI();
	this->gameUI->~UI();
	if(selectedStructure.selectedShape != nullptr)
	this->selectedStructure.selectedShape->~RectangleShape();
	Logger::Println("Destructor for Game called");
}
