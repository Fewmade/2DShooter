#pragma once

#include "State.h"
#include <vector>
#include <iostream>

using namespace sf;

class PatrolState : public State
{
public:

	PatrolState() : currentPoint(0)
	{}
	PatrolState(std::vector<Vector2f> points, DynamicObject *_owner, int currPoint)
	{
		patrolPoints	= points;
		owner			= _owner;
		currentPoint	= currPoint;
		pathOffset		= 0.1f;
	}

	PatrolState(std::vector<Vector2f> points, DynamicObject *_owner, int currPoint, float _pathOffset)
	{
		patrolPoints	= points;
		owner			= _owner;
		currentPoint	= currPoint;
		pathOffset		= _pathOffset;
	}
	~PatrolState()
	{}

	void enter() override
	{
		std::cerr << "Enter in patrol state" << std::endl;
		std::cerr << "Patrol points length: " << patrolPoints.size() << std::endl;
		std::cerr << "Offset: " << pathOffset << std::endl;
		std::cerr << "Owner: " << owner << std::endl;
	}

	void execute() override
	{
		std::cerr << owner->getPos().x << "/" << owner->getPos().y << std::endl;

		//Patrolling
		if (currentPoint < patrolPoints.size() - 1)
		{
			Vector2f point = patrolPoints[currentPoint] - owner->getPos();				//Находим направление в котором надо идти
			double vecLength = sqrt(point.x * point.x + point.y * point.y);
			if (vecLength <= pathOffset)												//Если мы уже достигли точки
			{
				//Идем к следующей
				++currentPoint;															
			}
			else
			{
				Vector2f normalizedDir = Vector2f(point.x / vecLength, point.y / vecLength);		//Нормализованное направление
				owner->setPos(Vector2f(owner->getPos().x + normalizedDir.x,							//Устанавливаем новую позицию нпс
										owner->getPos().y + normalizedDir.y));
			}
		}
		else
		{
			currentPoint = 0;
		}
	}

	void exit() override
	{

	}

private:
	std::vector<Vector2f>	patrolPoints;
	DynamicObject			*owner;
	float					pathOffset;
	int						currentPoint;
	
};
