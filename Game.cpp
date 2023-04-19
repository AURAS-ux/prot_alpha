#include "Game.hpp"

void Game::InitVars()
{
	this->ev = sf::Event();
	//Variable innit Begin
	this->resourceUI = new UI("assets\\space age.ttf");
	this->resourceUI->InnitText("Resource1:", RESOURCE_FONT_SIZE, sf::Color::White);
	grid = new MainGrid();
	temp = nullptr;
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
	if(temp != nullptr)
	this->temp->DrawStructure(*this->window);
	//Custom objects to draw End
	this->window->display();
}

void Game::PollEvents()
{
	while (this->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			std::cout << "Window destroyed" << std::endl;
			this->window->~RenderWindow();
		}
		//Custom poll for events Begin

		this->BuildStructure();

		//Custom poll for events End
	}
}

void Game::BuildStructure()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		std::unique_ptr<Structure> str = std::make_unique<Structure>(STRUCTURE_SIZE, STRUCTURE_SIZE);
		str->SetStructurePosition(
			CELL_SIZE * std::round((sf::Mouse::getPosition().x) / CELL_SIZE) + (X_OFFSET * str->GetStructureShape()->getGlobalBounds().width),
			CELL_SIZE * std::round((sf::Mouse::getPosition().y) / CELL_SIZE) + (Y_OFFSET * str->GetStructureShape()->getGlobalBounds().width)
		);

		temp = std::move(str);
	}

}

Game::~Game()
{
	this->grid->~MainGrid();
	this->resourceUI->~UI();
	std::cout << "Destructor for Game called" << std::endl;
}
