#pragma once

#include "PatrolState.h"

class State
{
public:
	virtual void Enter()					//Enter state
	{}
	virtual void Execute()					//Execute state
	{}
	virtual void Exit()						//Exit from state
	{}
};
