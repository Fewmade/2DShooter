#pragma once

#include <vector>
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject()
	{}
	StaticObject(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}

	virtual ~StaticObject()
	{}



protected:

};

std::vector<StaticObject> objects(1, StaticObject(getImage("images/stone.png")));