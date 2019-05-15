#include "Sorcerer.h"
#include "Warlock.h"
#include <iostream>


Sorcerer::Sorcerer() : Apprentice()
{
	stat_int += 10;
	stat_MP_max += 50;
	stat_MP_current = stat_MP_max;
	tex_player.loadFromFile("Assets/magic/Sorcerer/idle_1.png");
	spr_player.setTexture(tex_player);
	spr_player.setScale(sf::Vector2f(0.5f, 0.5f));
}

Sorcerer::Sorcerer(PlayerClass &old)
{
	stat_str		= old.getStats(STR);
	stat_int		= old.getStats(INT) + 10;
	stat_dex		= old.getStats(DEX);
	stat_HP_max		= old.getStats(HP_MAX) + 25;
	stat_HP_current	= stat_HP_max;
	stat_MP_max		= old.getStats(MP_MAX) + 50;
	stat_MP_current	= stat_MP_max;
	if (tex_player.loadFromFile("Assets/magic/Sorcerer/idle_1.png"))
		spr_player.setTexture(tex_player);
}

void Sorcerer::level_up(PlayerClass **current_char)
{
	std::cout << "Congratulations. You're a warlock now.\n";
	PlayerClass *new_char = new Warlock(**current_char);
	delete *current_char;
	*current_char = new_char;
}

Sorcerer::~Sorcerer()
{
	std::cout << "Sorcerer destructor\n";
}

bool Sorcerer::Attack(EnemyClass &enemy)
{
	std::cout << "Casting lighting bolt against " << enemy.getName() << std::endl;
	if (enemy.TakeDamage(this->getStats(INT)))
	{
		std::cout << enemy.getName() << " died\n";
		delete &enemy;
		return true;
	}
	else
		return false;
}