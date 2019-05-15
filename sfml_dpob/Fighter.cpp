#include "Fighter.h"
#include <iostream>


Fighter::Fighter() : PlayerClass()
{
	stat_str += 5;
	stat_rage_max = 100;
	stat_rage_current = 0;
	if (tex_player.loadFromFile("Assets/melee/fighter/1_IDLE_000.png"))
	{
		spr_player.setTexture(tex_player);
		spr_player.setScale(sf::Vector2f(0.5f, 0.5f));
	}
}

Fighter::~Fighter()
{
	std::cout << "Fighter destructor\n";
}

bool Fighter::Attack(EnemyClass &enemy)
{
	std::cout << "Slashing " << enemy.getName() << " with a sword\n";
	if (enemy.TakeDamage(this->getStats(STR)))
	{
		std::cout << enemy.getName() << " died\n";
		delete &enemy;
		return true;
	}
	else
		return false;
}

void Fighter::level_up(PlayerClass **current_char)
{
	std::cout << "already max level\n";
}

unsigned int Fighter::getStats(unsigned int stat) const
{
	switch (stat)
	{
	case MP_MAX:
		return stat_rage_max;
	case MP_CUR:
		return stat_rage_current;
	default:
		return PlayerClass::getStats(stat);
	}
}

Fighter& Fighter::operator++()
{
	PlayerClass::operator++();
	stat_rage_max += 25;
	return *this;
}