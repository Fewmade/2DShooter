#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject()
	{}
	StaticObject(Vector2i _pos)
	{
		pos = _pos;
	}
	virtual ~StaticObject()
	{}



protected:

};

