#include "Orc.h"
#include <iostream>


int Orc::orcs_alive = 0;

Orc::Orc()
{
	++orcs_alive;
	std::cout << "New enemy: an orc #" << orcs_alive << std::endl;
	stat_HP_max += 150;
	stat_HP_current = stat_HP_max;
	stat_armor += 15;
}


Orc::~Orc()
{
	--orcs_alive;
}

std::string Orc::getName() const
{
	return "Orc";
}