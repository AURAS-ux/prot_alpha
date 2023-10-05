#include "RandomEngine.hpp"

RandomEngine::RandomEngine(int rate)
{
	this->rate = rate;
	this->gen = std::mt19937(rd());
	this->distrib = std::uniform_int_distribution<>(0, rate);
}

int RandomEngine::GetRandomInt()
{
	return this->distrib(gen);
}
