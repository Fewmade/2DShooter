#pragma once


#include "Consts.h"
#include "State.h"
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
	}
	~SeekState()
	{}

	void enter() override
	{
		std::cerr << "Enter in seek state";
	}
	void execute(float time) override
	{

	}
	void exit() override
	{

	}


private:
	float predictMult;
};
