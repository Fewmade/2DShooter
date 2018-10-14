#pragma once

#include "DynamicObject.h"
#include "HealthComponent.h"

class Creature : public DynamicObject
{
public:
	Creature()
	{
		healthComp = new HealthComponent(0);
		pos = Vector2f(0, 0);
	}
	Creature(Vector2f _pos, int maxHp, int currHp)
	{
		healthComp = new HealthComponent(maxHp, currHp);
		pos = _pos;
	}
	Creature(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}
	Creature(Vector2f _pos, Image _image)
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

	virtual ~Creature()
	{
		delete healthComp;
		healthComp = nullptr;
	}

protected:
	HealthComponent* healthComp;
};
