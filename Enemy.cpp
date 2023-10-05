#include "Enemy.hpp"
#include "TextureManager.hpp"
#include "FileManager.hpp"
#include "Logger.hpp"

Enemy::Enemy(sf::Vector2f size)
{
	this->enemyShape = std::make_unique<sf::RectangleShape>(size);
	this->enemyShape->setScale(sf::Vector2f(enemyShape->getScale().x * -1, enemyShape->getScale().y));
	hitbox = sf::RectangleShape(sf::Vector2f(90,90));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(1.5);
	hitbox.setOutlineColor(sf::Color::Red);
}

Enemy::Enemy(float width, float height)
{
	this->enemyShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
	this->enemyShape->setScale(sf::Vector2f(enemyShape->getScale().x * -1, enemyShape->getScale().y));
	hitbox = sf::RectangleShape(sf::Vector2f(60,60));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(1.5);
	hitbox.setOutlineColor(sf::Color::Red);
}

void Enemy::UpdateEnemy(float deltaTime)
{
	this->hitbox.setPosition(sf::Vector2f(enemyShape->getPosition().x - ENEMYHITBOX_XOFFSET,enemyShape->getPosition().y + ENEMYHITBOX_YOFFSET));
	MoveEnemy(deltaTime);
}

void Enemy::DrawEnemy(sf::RenderTarget* tr)
{
	tr->draw(*this->enemyShape.get());
}

void Enemy::SetPosition(float x, float y)
{
	this->enemyShape->setPosition(sf::Vector2f(x, y));
}

Enemy::~Enemy()
{
	Logger::Println("Enemy destructor called", SNOOZE);
	this->enemyShape.reset();
	this->enemyTexture.reset();
}

void Enemy::MoveEnemy(float dt)
{
	this->enemyShape->move(sf::Vector2f(speedMultiplyer * -12.f *dt, 0));
}

void Enemy::SetEnemyTexture(std::string textureName)
{
	TextureManager::GetSprite(FileManager::GetFilePath(textureName), this->enemyTexture);
	this->enemyShape->setTexture(enemyTexture.get());

}

void Enemy::DrawHitBox(sf::RenderTarget* tr)
{
	/*enemyShape->setOutlineThickness(2);
	enemyShape->setOutlineColor(sf::Color::Red);*/
	tr->draw(hitbox);
}

bool Enemy::isHit(std::vector<sf::CircleShape>& bullets)
{
	return true;
	//Impractical causes bug 
	//sf::Vector2f rectPosition = enemyShape->getPosition();
	//sf::Vector2f rectHalfSize = enemyShape->getSize() / 2.0f;
	//for(auto& bullet:bullets)
	//{
	//	sf::Vector2f circlePosition = bullet.getPosition();

	//	float distanceX = std::abs(circlePosition.x - rectPosition.x);
	//	float distanceY = std::abs(circlePosition.y - rectPosition.y);
	//	
	//	float circleRadius = bullet.getRadius();
	//	if (distanceX > (rectHalfSize.x + circleRadius)) {
	//		return false; // No collision along X-axis
	//	}
	//	if (distanceY > (rectHalfSize.y + circleRadius)) {
	//		return false; // No collision along Y-axis
	//	}
	//	return true;
	//}
}


//todo better deleteion of hit enemies
