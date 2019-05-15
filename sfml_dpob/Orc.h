#pragma once
#include "EnemyClass.h"


class Orc : public EnemyClass
{
private:
	static int orcs_alive;
public:
	static int getCount() { return orcs_alive; };
	virtual std::string getName() const;
	Orc();
	~Orc();
};