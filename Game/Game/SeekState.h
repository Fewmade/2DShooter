#pragma once

#include "Consts.h"
#include "State.h"
#include "Player.h"
#include <iostream>

class SeekState : public State
{
public:

	SeekState()
	{}
	SeekState(Creature *_owner, float _predictMult = 1.3f)
	{
		owner = _owner;
		predictMult = _predictMult;
		stateID = SEEK_STATE;
	}
	~SeekState()
	{}

	void enter() override
	{

	}
	void execute(float time)
	{
		Vector2f playerPos = Vector2f(0, 0);

		int dir = 0;

		//Находим направление
		if (playerPos.x - owner->getPos().x >= PATH_OFFSET &&
			playerPos.y - owner->getPos().y >= PATH_OFFSET)
		{
			dir = RIGHT_DOWN;
		}
		else if (playerPos.x - owner->getPos().x <= -PATH_OFFSET &&
			playerPos.y - owner->getPos().y >= PATH_OFFSET)
		{
			dir = DOWN_LEFT;
		}
		else if (playerPos.x - owner->getPos().x >= PATH_OFFSET &&
			playerPos.y - owner->getPos().y <= -PATH_OFFSET)
		{
			dir = UP_RIGHT;
		}
		else if (playerPos.x - owner->getPos().x <= -PATH_OFFSET &&
			playerPos.y - owner->getPos().y <= -PATH_OFFSET)
		{
			dir = LEFT_UP;
		}
		else if (playerPos.x - owner->getPos().x <= -PATH_OFFSET)
		{
			dir = LEFT;
		}
		else if (playerPos.x - owner->getPos().x >= PATH_OFFSET)
		{
			dir = RIGHT;
		}
		else if (playerPos.y - owner->getPos().y >= PATH_OFFSET)
		{
			dir = DOWN;
		}
		else if (playerPos.y - owner->getPos().y <= -PATH_OFFSET)
		{
			dir = UP;
		}

		owner->move(owner->getRoom(), dir, time * owner->getSpeed());
	}
	void exit() override
	{

	}


private:
	float predictMult;
};
