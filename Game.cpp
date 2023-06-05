#include "Game.hpp"

void Game::InitVars()
{
	this->ev = sf::Event();
	//Variable innit Begin
	this->resourceUI = new UI("assets\\space age.ttf");
	this->resourceUI->InnitText("Resource1:", RESOURCE_FONT_SIZE, sf::Color::White);
	grid = new MainGrid();
	structures = std::vector<std::unique_ptr<Structure>>();
	//Variable innit End
}

void Game::InitWindow(int width, int height, int bitsPerPixel, bool isFullScreen)
{
	this->window = new sf::RenderWindow();
	this->videoMode = sf::VideoMode(sf::Vector2u(width, height), bitsPerPixel);
	if (isFullScreen)
	{
		this->window->create(this->videoMode, "PR_A", sf::Style::Fullscreen);
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
	this->resourceUI->DrawText(this->window, sf::Vector2f(20, 20));
	this->grid->MainGridDraw(this->window);
	for(auto& temp:structures)
	{
		if(temp != nullptr)
		temp->DrawStructure(*this->window);
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->BuildStructure();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			this->DestroyStructure(this->structures);

		//Custom poll for events End
	}
}

void Game::BuildStructure()
{
	std::unique_ptr<Structure> str = std::make_unique<Structure>(STRUCTURE_SIZE, STRUCTURE_SIZE);
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

Game::~Game()
{
	this->grid->~MainGrid();
	this->resourceUI->~UI();
	Logger::Println("Destructor for Game called");
}
