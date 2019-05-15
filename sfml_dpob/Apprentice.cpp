#include "Apprentice.h"
#include "Sorcerer.h"

#include <iostream>


Apprentice::Apprentice() : PlayerClass()
{
	stat_int += 5;
	stat_MP_max = 100;
	stat_MP_current = stat_MP_max;
	tex_player.loadFromFile("Assets/magic/Apprentice/idle_1.png");
	spr_player.setTexture(tex_player);
	spr_player.setScale(sf::Vector2f(0.5f, 0.5f));
}

Apprentice::~Apprentice()
{
	std::cout << "Apprentice destructor" << std::endl;
}

bool Apprentice::Attack(EnemyClass &enemy)
{
	std::cout << "Casting fireball against " << enemy.getName() << std::endl;
	if (enemy.TakeDamage(this->getStats(INT)))
	{
		std::cout << enemy.getName() << " died\n";
		delete &enemy;
		return true;
	}
	else
		return false;
}

void Apprentice::level_up(PlayerClass **current_char)
{
	std::cout << "Congratulations. You're a sorcerer now.\n";
	PlayerClass *new_char = new Sorcerer(**current_char);
	delete *current_char;
	*current_char = new_char;

}

unsigned int Apprentice::getStats(unsigned int stat) const
{
	switch (stat)
	{
	case MP_MAX:
		return stat_MP_max;
	case MP_CUR:
		return stat_MP_current;
	default:
		return PlayerClass::getStats(stat);
	}
}

Apprentice& Apprentice::operator++()
{
	PlayerClass::operator++();
	stat_MP_max += 25;
	return *this;
}