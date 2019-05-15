#include "Rogue.h"
#include "Archer.h"
#include <iostream>


Rogue::Rogue() : PlayerClass()
{
	stat_dex += 5;
	stat_energy_max = 100;
	stat_energy_current = stat_energy_max;
	if (tex_player.loadFromFile("Assets/ranged/Rogue/1_IDLE_000.png"))
	{
		spr_player.setTexture(tex_player);
		spr_player.setScale(sf::Vector2f(0.5f, 0.5f));
	}
}

Rogue::~Rogue()
{
	std::cout << "Rogue destructor\n";
}

bool Rogue::Attack(EnemyClass &enemy)
{
	std::cout << "Throwing knives at " << enemy.getName() << std::endl;
	if (enemy.TakeDamage(this->getStats(DEX)))
	{
		std::cout << enemy.getName() << " died\n";
		delete &enemy;
		return true;
	}
	else
		return false;
}

void Rogue::level_up(PlayerClass **current_char)
{
	std::cout << "Congratulations. You're an archer now.\n";
	PlayerClass *new_char = new Archer(**current_char);
	delete *current_char;
	*current_char = new_char;
}

unsigned int Rogue::getStats(unsigned int stat) const
{
	switch (stat)
	{
	case MP_MAX:
		return stat_energy_max;
	case MP_CUR:
		return stat_energy_current;
	default:
		return PlayerClass::getStats(stat);
	}
}

Rogue& Rogue::operator++()
{
	PlayerClass::operator++();
	stat_energy_max += 25;
	return *this;
}