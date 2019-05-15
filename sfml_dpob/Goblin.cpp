#include "Goblin.h"
#include <iostream>


int Goblin::goblins_alive = 0;

Goblin::Goblin()
{
	++goblins_alive;
	std::cout << "New enemy: a goblin #" << goblins_alive << std::endl;
	stat_HP_max += 50;
	stat_HP_current = stat_HP_max;
	stat_armor += 5;
}

Goblin::~Goblin()
{
	--goblins_alive;
}

std::string Goblin::getName() const
{
	return "Goblin";
}