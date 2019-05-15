#include "PlayerClass.h"
#include <iostream>


PlayerClass::PlayerClass()
{
	stat_HP_max = 100;
	stat_HP_current = 100;
	stat_str = 10;
	stat_int = 10;
	stat_dex = 10;
}

PlayerClass::~PlayerClass()
{
	std::cout << "Base destructor: deleting texture\n";
	tex_player.~Texture();
}

unsigned int PlayerClass::getStats(unsigned int stat) const
{
	switch (stat)
	{
	case STR:
		return stat_str;
	case INT:
		return stat_int;
	case DEX:
		return stat_dex;
	case HP_MAX:
		return stat_HP_max;
	case HP_CUR:
		return stat_HP_current;
	default:
		return 0;
	}
}

sf::Sprite PlayerClass::getSprite() const
{
	return spr_player;
}

PlayerClass& PlayerClass::operator++()
{
	stat_str += 5;
	stat_int += 5;
	stat_dex += 5;
	stat_HP_max += 25;
	return *this;
}

void PlayerClass::TakeDamage(unsigned int dmg_amount)
{
	if (stat_HP_current < dmg_amount)
		stat_HP_current = 0;
	else
		stat_HP_current -= dmg_amount;
		
}

void PlayerClass::HealUp(unsigned int heal_amount)
{
	stat_HP_current += heal_amount;
	if (stat_HP_current > stat_HP_max)
		stat_HP_current = stat_HP_max;
}