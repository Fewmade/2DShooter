#pragma once
#include "State.h"


class AttackState : public State
{
public:

	AttackState()
	{}
	~AttackState()
	{}

	AttackState(Creature *_owner, int id = 0)
	{
		owner = _owner;
		stateID = id;
	}

	void enter() override
	{

	}
	void execute(float time, Creature* player) override
	{

	}
	void exit() override
	{

	}

private:



};
