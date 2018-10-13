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
	DynamicObject(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}
	DynamicObject(Vector2i _pos, Image _image)
	{
		pos = _pos;
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}

	virtual ~DynamicObject()
	{}


protected:
	Vector2i pos;			//Позиция объекта в пространстве
};