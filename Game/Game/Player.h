#pragma once
#include "Creature.h"

int getplayerStatus()
{
	// Движение по диагоналям
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
	{
		return GO_UP_RIGHT;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
	{
		return GO_RIGHT_DOWN;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
	{
		return GO_DOWN_LEFT;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
	{
		return GO_LEFT_UP;
	}

	// Движение по прямым
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		return GO_UP;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		return GO_RIGHT;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		return GO_DOWN;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		return GO_LEFT;
	}

	// Если ничего из этого
	return STAY;
}

class Player : public Creature
{
public:
	
	Player(Vector2f _pos)
	{
		pos = _pos;

		speed = 0.000005f;
	}
	Player(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);

		speed = 0.000005f;
	}
	Player(Vector2f _pos, Image _image)
	{
		pos = _pos;
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);

		speed = 0.000005f;
	}

	~Player()
	{}
private:
	
};
