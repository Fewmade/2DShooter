#pragma once

#include <SFML/Graphics.hpp>
#include "Creature.h"
#include "GameManager.h"


class State
{
public:
	State()
	{}
	~State()
	{}

	virtual void enter()					//Enter state
	{}
	virtual void execute(float time, Creature* player)					//Execute state
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
