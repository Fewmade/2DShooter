#pragma once

#include <vector>
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject()
	{}
	StaticObject(Image _image, IntRect rect = IntRect(0, 0, 32, 32))
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}

	virtual ~StaticObject()
	{}
protected:

};