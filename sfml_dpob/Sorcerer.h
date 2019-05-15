#pragma once
#include "Apprentice.h"


class Sorcerer : public Apprentice
{
public:
	virtual bool Attack(EnemyClass &enemy);
	virtual void level_up(PlayerClass **x);
	Sorcerer();
	Sorcerer(PlayerClass &old);
	~Sorcerer();
};