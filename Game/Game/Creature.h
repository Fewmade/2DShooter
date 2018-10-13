#pragma once

#include "DynamicObject.h"
#include "HealthComponent.h"

class Creature : public DynamicObject
{
public:
	Creature()
	{
		healthComp = new HealthComponent(0);
		pos = Vector2i(0, 0);
	}
	Creature(Vector2i _pos, int maxHp, int currHp)
	{
		healthComp = new HealthComponent(maxHp, currHp);
		pos = _pos;
	}
	Creature(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}
	Creature(Vector2i _pos, Image _image)
	{
		pos = _pos;
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}

	virtual ~Creature()
	{
		delete healthComp;
		healthComp = nullptr;
	}

protected:
	HealthComponent* healthComp;
};
