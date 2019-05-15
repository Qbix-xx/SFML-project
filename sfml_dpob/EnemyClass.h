#pragma once
#include <SFML\Graphics.hpp>
#include <string>


//base, abstract class for non-player hostile character
class EnemyClass
{
protected:
	unsigned int death_count;
	int stat_HP_max, stat_HP_current, stat_armor;
public:
	virtual std::string getName() const = 0;
	//returns true when killed, false otherwise
	bool TakeDamage(unsigned int dmg_amount);
	EnemyClass();
	virtual ~EnemyClass();
};