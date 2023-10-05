#pragma once
#include <random>

class RandomEngine
{
private:
	int rate = 0;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> distrib;
public:
	RandomEngine(int);
	int GetRandomInt();

};

