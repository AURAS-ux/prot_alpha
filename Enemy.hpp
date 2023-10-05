#pragma once
#include<SFML/Graphics.hpp>
class Enemy
{
public:
	//Moved this to public ( not ok) //todo fix?
	std::unique_ptr<sf::RectangleShape> enemyShape;
	Enemy() = delete;
	Enemy(sf::Vector2f);
	Enemy(float, float);
	void UpdateEnemy(float);
	void DrawEnemy(sf::RenderTarget*);
	void SetPosition(float, float);
	void SetEnemyTexture(std::string);
	void DrawHitBox(sf::RenderTarget*);
	bool isHit(std::vector<sf::CircleShape>&);
	~Enemy();
private:
	
	std::unique_ptr<sf::Texture> enemyTexture;
	const int speedMultiplyer = 10;
	sf::RectangleShape hitbox;

	void MoveEnemy(float);
};

