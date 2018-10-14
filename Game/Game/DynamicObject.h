#pragma once


#include "GameObject.h"

class DynamicObject : public GameObject
{
public:

	DynamicObject()
	{}
	DynamicObject(Vector2f _pos)
	{
		pos = _pos;
	}
	DynamicObject(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}
	DynamicObject(Vector2f _pos, Image _image)
	{
		pos = _pos;
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}

	void setImage(Image _image)
	{
		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}
	Sprite getSprite()
	{
		Sprite sprite;
		sprite.setTexture(texture);
		return sprite;
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