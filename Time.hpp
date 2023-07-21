#pragma once
#include <SFML/Graphics.hpp>
class Time
{
private:
	sf::Clock clock;
public:
	Time() = delete;
	Time(sf::Clock&);
	float GetDeltaTime();
};

