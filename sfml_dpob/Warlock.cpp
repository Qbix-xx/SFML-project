#include "Warlock.h"
#include <iostream>


Warlock::Warlock() : Sorcerer()
{
	stat_int += 10;
	stat_MP_max += 50;
	stat_MP_current = stat_MP_max;
	tex_player.loadFromFile("Assets/magic/Warlock/idle_1.png");
	spr_player.setTexture(tex_player);
	spr_player.setScale(sf::Vector2f(0.5f, 0.5f));
}

Warlock::Warlock(PlayerClass &old)
{
	stat_str		= old.getStats(STR);
	stat_int		= old.getStats(INT) + 10;
	stat_dex		= old.getStats(DEX);
	stat_HP_max		= old.getStats(HP_MAX) + 25;
	stat_HP_current = stat_HP_max;
	stat_MP_max		= old.getStats(MP_MAX) + 50;
	stat_MP_current = stat_MP_max;
	if (tex_player.loadFromFile("Assets/magic/Warlock/idle_1.png"))
		spr_player.setTexture(tex_player);
	else
		std::cout << "error loading warlock texture :(";
}

Warlock::~Warlock()
{
	std::cout << "Warlock destructor\n";
}

bool Warlock::Attack(EnemyClass &enemy)
{
	std::cout << "Casting curse against " << enemy.getName() << std::endl;
	if (enemy.TakeDamage(this->getStats(INT)))
	{
		std::cout << enemy.getName() << " died\n";
		delete &enemy;
		return true;
	}
	else
		return false;
}

void Warlock::level_up(PlayerClass **x)
{
	std::cout << "already max level\n";
}