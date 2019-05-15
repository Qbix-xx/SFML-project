#pragma once
#include "EnemyClass.h"


class Lizard : public EnemyClass
{
private:
	static int lizards_alive;
public:
	static int getCount() { return lizards_alive; };
	virtual std::string getName() const;
	Lizard();
	~Lizard();
};