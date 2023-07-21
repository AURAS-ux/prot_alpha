#include "Time.hpp"


Time::Time(sf::Clock& clock)
{
	this->clock = clock;
}

float Time::GetDeltaTime()
{
	return clock.restart().asSeconds();
}
