#pragma once

#include "State.h"
#include "Consts.h"
#include <vector>
#include <iostream>

using namespace sf;

class PatrolState : public State
{
public:

	PatrolState() : currentPoint(0)
	{}
	PatrolState(std::vector<Vector2f> points, Creature *_owner, int currPoint)
	{
		patrolPoints	= points;
		owner			= _owner;
		currentPoint	= currPoint;
		frameCount		= 0;
		stateID = PATROL_STATE;
	}
	~PatrolState()
	{}

	void enter() override
	{

	}
	void execute(float time) override
	{
		++frameCount;
		std::cerr << owner->getPos().x << "/" << owner->getPos().y << " -frame: " << frameCount << std::endl;
		std::cerr << patrolPoints[currentPoint].x << "/" << patrolPoints[currentPoint].y << std::endl;

		if (patrolPoints.size() > 0)
		{
			int dir = 0;

			if ((abs(owner->getPos().x - patrolPoints[currentPoint].x) <= PATH_OFFSET) &&
				(abs(owner->getPos().y - patrolPoints[currentPoint].y) <= PATH_OFFSET))
			{
				if (currentPoint < patrolPoints.size() - 1)
				{
					++currentPoint;
				}
				else
				{
					currentPoint = 0;
				}
			}
			else
			{
				//Находим направление
				if (patrolPoints[currentPoint].x - owner->getPos().x >= PATH_OFFSET &&
					patrolPoints[currentPoint].y - owner->getPos().y >= PATH_OFFSET)
				{
					dir = RIGHT_DOWN;
				}
				else if (patrolPoints[currentPoint].x - owner->getPos().x <= -PATH_OFFSET &&
					patrolPoints[currentPoint].y - owner->getPos().y >= PATH_OFFSET)
				{
					dir = DOWN_LEFT;
				}
				else if (patrolPoints[currentPoint].x - owner->getPos().x >= PATH_OFFSET &&
					patrolPoints[currentPoint].y - owner->getPos().y <= -PATH_OFFSET)
				{
					dir = UP_RIGHT;
				}
				else if (patrolPoints[currentPoint].x - owner->getPos().x <= -PATH_OFFSET &&
					patrolPoints[currentPoint].y - owner->getPos().y <= -PATH_OFFSET)
				{
					dir = LEFT_UP;
				}
				else if (patrolPoints[currentPoint].x - owner->getPos().x <= -PATH_OFFSET)
				{
					dir = LEFT;
				}
				else if (patrolPoints[currentPoint].x - owner->getPos().x >= PATH_OFFSET)
				{
					dir = RIGHT;
				}
				else if (patrolPoints[currentPoint].y - owner->getPos().y >= PATH_OFFSET)
				{
					dir = DOWN;
				}
				else if (patrolPoints[currentPoint].y - owner->getPos().y <= -PATH_OFFSET)
				{
					dir = UP;
				}
				/////////////////////////////////////////////////////////

				owner->move(dir, time * owner->getSpeed());
			}
		}
	}
	void exit() override
	{

	}


private:
	std::vector<Vector2f>	patrolPoints;
	unsigned int			currentPoint;
	unsigned int			frameCount;
};
