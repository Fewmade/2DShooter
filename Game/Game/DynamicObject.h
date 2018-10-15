#pragma once

#include "GameObject.h"

class DynamicObject : public GameObject
{
public:

	DynamicObject()
	{}
	DynamicObject(Image _image, Vector2f _pos, bool _solid = false, Vector2i _spriteSize = Vector2i(32, 32)) : pos(_pos)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
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