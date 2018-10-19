#pragma once

#include <SFML/Graphics.hpp>
#include "Creature.h"


class State
{
public:
	State()
	{}
	~State()
	{}

	virtual void enter()					//Enter state
	{}
	virtual void execute(float time)					//Execute state
	{}
	virtual void exit()						//Exit from state
	{}

	int getStateID() const
	{
		return stateID;
	}

protected:
	Creature * owner;
	int stateID;
};
