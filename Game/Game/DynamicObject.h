#pragma once

#include "GameObject.h"

class DynamicObject : public GameObject
{
public:

	DynamicObject()
	{}
	DynamicObject(Image _image, Vector2f _pos, bool _solid = false, Vector2u _spriteSize = Vector2u(32, 32), IntRect _collisionRect = IntRect(0, 0, 32, 32)) : pos(_pos)
	{
		image = _image;

		
		texture.loadFromImage(image);

		solid = _solid;
		collisionRect = _collisionRect;
		spriteSize = _spriteSize;
	}
	

	Vector2f getPos()
	{
		return pos;
	}
	void setPos(Vector2f _pos)
	{
		pos = _pos;
	}

	virtual ~DynamicObject()
	{}

protected:
	Vector2f pos;			//Позиция объекта в пространстве
};