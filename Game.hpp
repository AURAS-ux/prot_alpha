#pragma once
#include "SETTINGS.hpp"
#include<SFML/Graphics.hpp>
#include "UI.hpp"
#include "MainGrid.hpp"
#include "Structure.hpp"
#include <memory>

class Game
{
public:
	Game();
	Game(int,int,int,bool);
	Game(const Game& game) = delete;
	~Game();
	void Update();
private:
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	UI* resourceUI;
	MainGrid* grid;
	std::vector<std::unique_ptr<Structure>> structures;
	sf::Image iconImage;

	void InitVars();
	void InitWindow(int,int,int,bool);
	bool IsOpen();
	void DrawWindow();
	void PollEvents();
	void BuildStructure();
	void DestroyStructure(std::vector<std::unique_ptr<Structure>>&);
	bool CheckStructureInterection(std::unique_ptr<Structure>& ,std::vector<std::unique_ptr<Structure>>&);
};

