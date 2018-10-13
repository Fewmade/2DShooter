#pragma once
#include "Creature.h"

class EnemyNPC : public Creature
{
public:
	EnemyNPC()
	{}
	EnemyNPC(Vector2i _pos)
	{
		pos = _pos;
	}

	virtual ~EnemyNPC()
	{}

protected:

};