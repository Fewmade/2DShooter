#pragma once

#include "State.h"
#include <vector>

using namespace sf;

class PatrolState : public State
{
public:

	PatrolState() : currentPoint(0)
	{}
	PatrolState(std::vector<Vector2i> points, DynamicObject *_owner, int currPoint)
	{
		patrolPoints	= points;
		owner			= _owner;
		currentPoint	= currPoint;
		pathOffset		= 0;
	}
	PatrolState(std::vector<Vector2i> points, DynamicObject *_owner, int currPoint, int _pathOffset)
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
			Vector2i point = patrolPoints[currentPoint] - owner->GetPos();				//������� ����������� � ������� ���� ����
			double vecLength = sqrt(point.x * point.x + point.y * point.y);
			if (vecLength <= pathOffset)												//���� �� ��� �������� �����
			{
				//���� � ���������
				++currentPoint;															
			}
			else
			{
				Vector2i normalizedDir = Vector2i(point.x / vecLength, point.y / vecLength);		//��������������� �����������
				owner->SetPos(Vector2i(owner->GetPos().x + normalizedDir.x,							//������������� ����� ������� ���
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
	std::vector<Vector2i>	patrolPoints;
	DynamicObject			*owner;
	int						pathOffset;
	int						currentPoint;
	
};
