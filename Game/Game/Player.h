#pragma once
#include "Creature.h"


class Player : public Creature
{
public:
	
	Player(Vector2i _pos)
	{
		pos = _pos;
	}

	~Player()
	{}



private:
	
};
