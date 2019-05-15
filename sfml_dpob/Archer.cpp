#include "Archer.h"
#include <iostream>


Archer::Archer()
{
	stat_str += 5;
	stat_energy_max = 100;
	stat_energy_current = 0;
	tex_player.loadFromFile("Assets/ranged/Archer/1_IDLE_000.png");
	spr_player.setTexture(tex_player);
	spr_player.setScale(sf::Vector2f(0.5f, 0.5f));
}

Archer::Archer(PlayerClass &old)
{
	stat_str = old.getStats(STR);
	stat_int = old.getStats(INT) + 10;
	stat_dex = old.getStats(DEX);
	stat_HP_max = old.getStats(HP_MAX) + 25;
	stat_HP_current = stat_HP_max;
	stat_energy_max = old.getStats(MP_MAX) + 50;
	stat_energy_current = stat_energy_max;
	if (tex_player.loadFromFile("Assets/ranged/Archer/1_IDLE_000.png"))
		spr_player.setTexture(tex_player);
}

Archer::~Archer()
{
}

bool Archer::Attack(EnemyClass &enemy)
{
	std::cout << "Shooting arrows at " << enemy.getName() << std::endl;
	if (enemy.TakeDamage(this->getStats(DEX)))
	{
		std::cout << enemy.getName() << " died\n";
		delete &enemy;
		return true;
	}
	else
		return false;
}
void Archer::level_up(PlayerClass **current_char)
{
	std::cout << "already max level\n";
}