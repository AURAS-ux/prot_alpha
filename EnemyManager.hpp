#pragma once
#include <SFML/Graphics.hpp>
#include "Logger.hpp"
#include "Enemy.hpp"
#include "RandomEngine.hpp"
#include "MainGrid.hpp"

class EnemyManager
{
private:
	struct  EnemySpawner
	{
		std::vector<std::unique_ptr<Enemy>> enemies;
		sf::Vector2f spawnPosition;
	};
	std::vector<std::unique_ptr<EnemySpawner>> spawners;
	RandomEngine random_engine = RandomEngine(ENEMY_SPAWNRATE);

	void SpawnEnemies(int);
	void CheckEnemiesHit(std::vector<sf::CircleShape>&,MainGrid&);
public:
	EnemyManager() = delete;
	EnemyManager(int, std::vector<sf::Vector2f>);
	std::vector<std::unique_ptr<EnemySpawner>>& GetSpawners();
	void DrawEnemies(sf::RenderTarget*);
	void UpdateEnemyManager(int,std::vector<sf::CircleShape>&,MainGrid&);
	void MoveEnemies(float);
};

