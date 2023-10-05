#include "EnemyManager.hpp"
#include <algorithm>

EnemyManager::EnemyManager(int count, std::vector<sf::Vector2f> spawnerpositions)
{
	if(count != spawnerpositions.size())
	{
		Logger::PrintError("Differnt number of positions and spawners");
	}

	for(int i=0;i<count;i++)
	{
		std::unique_ptr<EnemySpawner> enemySpawner = std::make_unique<EnemySpawner>();
		enemySpawner->spawnPosition = spawnerpositions.at(i);
		spawners.push_back(std::move(enemySpawner));
	}
}

std::vector<std::unique_ptr<EnemyManager::EnemySpawner>>& EnemyManager::GetSpawners()
{
	return this->spawners;
}

void EnemyManager::SpawnEnemies(int rate)
{
	for (auto& spawner : spawners)
	{
		if(random_engine.GetRandomInt() == 0)
		{
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(STRUCTURE_SIZE, STRUCTURE_SIZE);
			enemy->SetPosition(spawner->spawnPosition.x, spawner->spawnPosition.y);
			enemy->SetEnemyTexture("Variant3.png");
			spawner->enemies.push_back(std::move(enemy));
		}
	}
}

void EnemyManager::CheckEnemiesHit(std::vector<sf::CircleShape>& bullets,MainGrid& grid)
{
	std::vector<sf::RectangleShape*> gridLines = grid.GetGridLines();
	for(auto& spawner:this->spawners)
	{
		for(auto& enemy : spawner->enemies)
		{
			//OBSOLETE because too slow and causing werird bug //todo fix
			//if( enemy != nullptr && enemy->isHit(bullets))
			//{
			//	auto enemyHit = std::find(spawner->enemies.begin(), spawner->enemies.end(), enemy);
			//	spawner->enemies.erase(enemyHit);
			//	/*Logger::Println("HIT");
			//	Logger::Println(spawner->enemies.size());*/
			//}
			for(sf::RectangleShape* gridCell : gridLines)
			{
				if (enemy.get()->enemyShape->getGlobalBounds().findIntersection(gridCell->getGlobalBounds()) != std::nullopt)
				{
					auto it = std::find(gridLines.begin(), gridLines.end(), gridCell);
					if(it != gridLines.end())
					{
						int index = std::distance(gridLines.begin(), it);
						Logger::Print("enemy at grid nr "); Logger::Print(index);
						Logger::Println("");
					}
				}
				
			}
		}
	}
}

void EnemyManager::DrawEnemies(sf::RenderTarget* tr)
{
	for(auto& spawner:spawners)
	{
		for(auto& enemy:spawner->enemies)
		{
			if(enemy != nullptr)
			{
				enemy->DrawEnemy(tr);
				enemy->DrawHitBox(tr);
			}
		}
	}
}

void EnemyManager::UpdateEnemyManager(int rate,std::vector<sf::CircleShape>& bullets,MainGrid& grid)
{
	SpawnEnemies(rate);
	CheckEnemiesHit(bullets,grid);
}

void EnemyManager::MoveEnemies(float deltaTime)
{
	for(auto& spawner:spawners)
	{
		for(auto& enemy: spawner->enemies)
		{
			if(enemy != nullptr)
			enemy->UpdateEnemy(deltaTime);
		}
	}
}