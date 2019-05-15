#pragma once
#include "Rogue.h"
class Archer : public Rogue
{
public:
	virtual bool Attack(EnemyClass &enemy);
	virtual void level_up(PlayerClass **current_char);
	Archer();
	Archer(PlayerClass &old);
	~Archer();
};

