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
	}
	DynamicObject(Vector2i _pos, Image _image)
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

	virtual ~DynamicObject()
	{}

	Vector2i GetPos() const
	{
		return pos;
	}
	void SetPos(Vector2i _pos)
	{
		pos = _pos;
	}



protected:
	Vector2i pos;			//Позиция объекта в пространстве
};