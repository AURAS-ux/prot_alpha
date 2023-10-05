#pragma once
#include "SETTINGS.hpp"
#include<SFML/Graphics.hpp>
#include "UI.hpp"
#include "MainGrid.hpp"
#include "Structure.hpp"
#include "TextureManager.hpp"
#include <memory>
#include "Enemy.hpp"
#include "EnemyManager.hpp"

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
	sf::ContextSettings settings;
	UI* resourceUI;
	MainGrid* grid;
	std::vector<std::unique_ptr<Structure>> structures;
	sf::Image iconImage;
	UI* gameUI;
	std::string fontPath;
	float res1Score;
	float scoreMultiplyer;
	std::vector<std::unique_ptr<sf::Texture>> spaceShipTextures;
	UI::SelectedStructure selectedStructure;
	sf::Angle rotationAngle;
	std::unique_ptr<sf::Texture> backgroundTexture;
	std::unique_ptr<sf::Sprite> backgroundSprite;
	std::vector<std::string> spaceShipTexturesNames;
	sf::Clock clock;
	float deltaTime;
	Time time = Time(clock);
	std::vector<sf::CircleShape> structureBullets;
	std::unique_ptr<sf::Texture> bulletTexture;
	std::vector<sf::Vector2f> spawnerPositions;
	int spawnerCount;
	std::unique_ptr<EnemyManager> enemyManager;

	void InitVars();
	void InitWindow(int,int,int,bool);
	bool IsOpen();
	void DrawWindow();
	void PollEvents();
	void BuildStructure();
	void DestroyStructure(std::vector<std::unique_ptr<Structure>>&);
	bool CheckStructureInterection(std::unique_ptr<Structure>& ,std::vector<std::unique_ptr<Structure>>&);
	void IncreaseScore(float&,float&, std::vector<std::unique_ptr<Structure>>&);
	void GetSelectedStructure();
	void CleanBullets();
	void HandleBulletsUpdate();
	void HandleGridDrawing();
	void UpdateEnemies();
};

