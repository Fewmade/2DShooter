#pragma once
#include "State.h"


class AttackState : public State
{
public:

	AttackState()
	{}
	~AttackState()
	{}

	AttackState(Creature *_owner, int id = ATTACK_STATE)
	{
		owner = _owner;
		stateID = id;
	}

	void enter() override
	{

	}
	void execute(float time, Creature* player) override
	{
		if (player != nullptr)
		{
			if (player->getHP() > 0)
			{
				player->dealDamage(owner->getDamage());
			}
		}
	}
	void exit() override
	{

	}

private:



};
