#pragma once

#include <vector>
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject()
	{}
	StaticObject(Image _image, bool _solid = false, Vector2u _spriteSize = Vector2u(32, 32), IntRect _collisionRect = IntRect(0, 0, 32, 32))
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
		collisionRect = _collisionRect;
		spriteSize = _spriteSize;
	}

	virtual ~StaticObject()
	{}
protected:

};