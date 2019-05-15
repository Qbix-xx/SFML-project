#pragma once
#include "Sorcerer.h"


class Warlock :	public Sorcerer
{
public:
	virtual void level_up(PlayerClass **x);
	virtual bool Attack(EnemyClass &enemy);
	Warlock();
	Warlock(PlayerClass &old);
	~Warlock();
};