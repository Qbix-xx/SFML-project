#pragma once
#include <SFML\Graphics.hpp>
#include "EnemyClass.h"
enum stats { STR, INT, DEX, HP_MAX, HP_CUR, MP_MAX, MP_CUR };


//Base, abstract class for player character
class PlayerClass
{
protected:
	unsigned int stat_HP_max, stat_HP_current, stat_str, stat_int, stat_dex, enemies_slain;
	sf::Texture	tex_player;
	sf::Sprite	spr_player;
public:
	//returns true if target dies
	virtual bool Attack(EnemyClass &enemy) = 0;
	virtual void level_up(PlayerClass **x) = 0;
	virtual sf::Sprite getSprite() const;
	void TakeDamage(unsigned int dmg_amount);
	void HealUp(unsigned int heal_amount);
	virtual unsigned int getStats(unsigned int stat) const;
	virtual PlayerClass& operator++();
	PlayerClass();
	virtual ~PlayerClass();
};