#pragma once


#include "GameObject.h"

class DynamicObject : public GameObject
{
public:

	DynamicObject()
	{}
	DynamicObject(Vector2i _pos)
	{
		pos = _pos;
	}

	virtual ~DynamicObject()
	{}


protected:

};