#pragma once

#include "State.h"
#include <vector>

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
		pathOffset		= 0;
	}
	PatrolState(std::vector<Vector2f> points, DynamicObject *_owner, int currPoint, int _pathOffset)
	{
		patrolPoints	= points;
		owner			= _owner;
		currentPoint	= currPoint;
		pathOffset		= _pathOffset;
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
			Vector2f point = patrolPoints[currentPoint] - owner->GetPos();				//Находим направление в котором надо идти
			double vecLength = sqrt(point.x * point.x + point.y * point.y);
			if (vecLength <= pathOffset)												//Если мы уже достигли точки
			{
				//Идем к следующей
				++currentPoint;															
			}
			else
			{
				Vector2f normalizedDir = Vector2f(point.x / vecLength, point.y / vecLength);		//Нормализованное направление
				owner->SetPos(Vector2f(owner->GetPos().x + normalizedDir.x,							//Устанавливаем новую позицию нпс
										owner->GetPos().y + normalizedDir.y));
			}
		}
		else
		{
			currentPoint = 0;
		}
	}

	void Exit() override
	{

	}

private:
	std::vector<Vector2f>	patrolPoints;
	DynamicObject			*owner;
	int						pathOffset;
	int						currentPoint;
	
};
