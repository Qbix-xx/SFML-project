#pragma once
#include "PlayerClass.h"


class Fighter :	public PlayerClass
{
protected:
	unsigned int stat_rage_max, stat_rage_current;
public:
	virtual bool Attack(EnemyClass &enemy);
	virtual void level_up(PlayerClass **current_char);
	virtual unsigned int getStats(unsigned int stat) const;
	virtual Fighter& operator++();
	Fighter();
	~Fighter();
};