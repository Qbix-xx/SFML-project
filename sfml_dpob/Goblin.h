#pragma once
#include "EnemyClass.h"


class Goblin : public EnemyClass
{
private:
	static int goblins_alive;
public:
	static int getCount() { return goblins_alive; };
	virtual std::string getName() const;
	Goblin();
	~Goblin();
};