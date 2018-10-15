#pragma once

#include <vector>
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject()
	{}
	StaticObject(Image _image, bool _solid = false, Vector2i _spriteSize = Vector2i(32, 32))
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
		spriteSize = _spriteSize;
	}

	virtual ~StaticObject()
	{}
protected:

};