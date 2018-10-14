#pragma once

#include "DynamicObject.h"
#include "HealthComponent.h"

const int STAY = 0;

const int GO_UP = 1;
const int GO_UP_RIGHT = 2;
const int GO_RIGHT = 3;
const int GO_RIGHT_DOWN = 4;
const int GO_DOWN = 5;
const int GO_DOWN_LEFT = 6;
const int GO_LEFT = 7;
const int GO_LEFT_UP = 8;

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

	void setSpeed(float _speed)
	{
		speed = _speed;
	}
	float getSpeed()
	{
		return speed;
	}

	virtual ~Creature()
	{
		delete healthComp;
		healthComp = nullptr;
	}

protected:
	HealthComponent* healthComp;

	float speed;
};
