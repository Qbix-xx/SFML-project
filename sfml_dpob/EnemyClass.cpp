#include "EnemyClass.h"

#include <iostream>

EnemyClass::EnemyClass()
{
	stat_HP_max = 100;
	stat_HP_current = stat_HP_max;
	stat_armor = 10;
}

EnemyClass::~EnemyClass()
{

}

bool EnemyClass::TakeDamage(unsigned int dmg_amount)
{
	int temp = stat_HP_current;
	if( dmg_amount > stat_armor )
		stat_HP_current -= (dmg_amount - stat_armor);
	else
	{
		std::cout << "You didn't break through the armor. Get stronger\n";
		return false;
	}
	if (stat_HP_current <= 0)
	{
		stat_HP_current = 0;
		temp -= stat_HP_current;
		std::cout << getName() << ": " << temp << " damage taken\n";
		return true;
	}
	else
	{
		temp -= stat_HP_current;
		std::cout << getName() << ": " << temp << " damage taken\n";
		return false;
	}
}