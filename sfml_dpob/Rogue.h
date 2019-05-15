#pragma once
#include "PlayerClass.h"


class Rogue : public PlayerClass
{
protected:
	unsigned int stat_energy_max, stat_energy_current;
public:
	virtual unsigned int getStats(unsigned int stat) const;
	virtual bool Attack(EnemyClass &enemy);
	virtual void level_up(PlayerClass **current_char);
	virtual Rogue& operator++();
	Rogue();
	~Rogue();
};