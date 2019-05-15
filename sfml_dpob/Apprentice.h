#pragma once
#include "PlayerClass.h"


class Apprentice : public PlayerClass
{
protected:
	unsigned int stat_MP_max, stat_MP_current;
public:
	virtual bool Attack(EnemyClass &enemy);
	virtual void level_up(PlayerClass **x);
	virtual unsigned int getStats(unsigned int stat) const;
	virtual Apprentice& operator++();
	Apprentice();
	~Apprentice();
};