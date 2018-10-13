#pragma once

#include "DynamicObject.h"
#include "HealthComponent.h"

class Creature : public DynamicObject
{
public:
	Creature()
	{
		healthComp = new HealthComponent(0);
		pos = Vector2i(0, 0);
	}
	Creature(Vector2i _pos, int maxHp, int currHp)
	{
		healthComp = new HealthComponent(maxHp, currHp);
		pos = _pos;
	}

	virtual ~Creature()
	{
		delete healthComp;
		healthComp = nullptr;
	}

protected:
	HealthComponent* healthComp;
};
