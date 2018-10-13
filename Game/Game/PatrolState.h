#pragma once

#include "State.h"
#include <vector>

using namespace sf;

class PatrolState : public State
{
public:

	void Enter() override
	{

	}

	void Execute() override
	{

	}

	void Exit() override
	{

	}

private:
	std::vector<Vector2i> patrolPoints;
};
