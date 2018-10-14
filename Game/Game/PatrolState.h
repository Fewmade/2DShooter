#pragma once

#include "State.h"
#include <vector>

using namespace sf;

class PatrolState : public State
{
public:

	PatrolState() : currentPoint(0)
	{}
	PatrolState(std::vector<Vector2i> points, int currPoint)
	{
		patrolPoints = points;
		currentPoint = currPoint;
	}
	~PatrolState()
	{}

	void Enter() override
	{

	}

	void Execute() override
	{
		//Patrolling
		if (currentPoint < patrolPoints.size() - 1)
		{
			//Move to the next point
		}
		else
		{
			//Move to the first point
		}
	}

	void Exit() override
	{

	}

private:
	std::vector<Vector2i>	patrolPoints;
	int						currentPoint;
};
