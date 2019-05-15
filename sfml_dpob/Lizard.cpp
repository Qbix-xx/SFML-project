#include "Lizard.h"
#include <iostream>


int Lizard::lizards_alive = 0;

Lizard::Lizard()
{
	++lizards_alive;
	std::cout << "New enemy: a lizard #" << lizards_alive << std::endl;
	stat_HP_max += 100;
	stat_HP_current = stat_HP_max;
	stat_armor += 10;
}

Lizard::~Lizard()
{
	--lizards_alive;
}

std::string Lizard::getName() const
{
	return "Lizard";
}