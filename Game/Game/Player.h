#pragma once
#include "Creature.h"

const int STAY = 0;

const int GO_UP         = 1;
const int GO_UP_RIGHT   = 2;
const int GO_RIGHT      = 3;
const int GO_RIGHT_DOWN = 4;
const int GO_DOWN       = 5;
const int GO_DOWN_LEFT  = 6;
const int GO_LEFT       = 7;
const int GO_LEFT_UP    = 8;

class Player : public Creature
{
public:
	
	Player(Vector2f _pos)
	{
		pos = _pos;
	}
	Player(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}
	Player(Vector2f _pos, Image _image)
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

	void move(int status, float distance = 0)
	{
		Vector2f dPos;

		switch (status)
		{
		case STAY: dPos.x = 0; dPos.y = 0;
			break;

		case         GO_UP: dPos.y = -distance;     dPos.x = 0;
			break;
		case   GO_UP_RIGHT: dPos.y = -distance / 2; dPos.x = distance / 2;
			break;
		case      GO_RIGHT: dPos.y = 0;             dPos.x = distance;
			break;
		case GO_RIGHT_DOWN: dPos.y = distance / 2;  dPos.x = distance / 2;
			break;
		case       GO_DOWN: dPos.y = distance;      dPos.x = 0;
			break;
		case  GO_DOWN_LEFT: dPos.y = distance / 2;  dPos.x = -distance / 2;
			break;
		case       GO_LEFT: dPos.y = 0;             dPos.x = -distance;
			break;
		case    GO_LEFT_UP: dPos.y = -distance / 2; dPos.x = -distance / 2;
			break;
		}

		pos += dPos;
	}

	~Player()
	{}
private:
	
};
