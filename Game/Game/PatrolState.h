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
	}
	~PatrolState()
	{}

	void enter() override
	{
		std::cerr << "Enter in patrol state" << std::endl;
		std::cerr << "Patrol points length: " << patrolPoints.size() << std::endl;
		std::cerr << "Owner: " << owner << " " << owner->getID()  << std::endl;
	}

	void execute(float time) override
	{
		++frameCount;
		std::cerr << owner->getPos().x << "/" << owner->getPos().y << " -frame: " << frameCount << std::endl;

		if (patrolPoints.size() > 0)
		{
			int dir = 0;

			if (owner->getPos().x == patrolPoints[currentPoint].x &&
				owner->getPos().y == patrolPoints[currentPoint].y)
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
				if (patrolPoints[currentPoint].x > owner->getPos().x &&
					patrolPoints[currentPoint].y > owner->getPos().y)
				{
					dir = UP_RIGHT;
				}
				else if (patrolPoints[currentPoint].x < owner->getPos().x &&
					patrolPoints[currentPoint].y > owner->getPos().y)
				{
					dir = LEFT_UP;
				}
				else if (patrolPoints[currentPoint].x > owner->getPos().x &&
					patrolPoints[currentPoint].y < owner->getPos().y)
				{
					dir = RIGHT_DOWN;
				}
				else if (patrolPoints[currentPoint].x < owner->getPos().x &&
					patrolPoints[currentPoint].y < owner->getPos().y)
				{
					dir = DOWN_LEFT;
				}
				else if (patrolPoints[currentPoint].x < owner->getPos().x)
				{
					dir = LEFT;
				}
				else if (patrolPoints[currentPoint].x > owner->getPos().x)
				{
					dir = RIGHT;
				}
				else if (patrolPoints[currentPoint].y > owner->getPos().y)
				{
					dir = UP;
				}
				else if (patrolPoints[currentPoint].y < owner->getPos().y)
				{
					dir = DOWN;
				}
				/////////////////////////////////////////////////////////

				owner->move(owner->getRoom(), dir, time * owner->getSpeed());
			}
		}
		
		

		
	}

	void exit() override
	{

	}

private:
	std::vector<Vector2f>	patrolPoints;
	Creature				*owner;
	unsigned int			currentPoint;
	unsigned int			frameCount;
};
