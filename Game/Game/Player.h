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
	Player()
	{
		healthComp = new HealthComponent(0);
		pos = Vector2f(0, 0);

		id = DEFAULT_ID;
	}
	Player(Image _image, Vector2f _pos, int maxHp, int currHp, bool _solid = false, Vector2i _spriteSize = Vector2i(32, 32))
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);

		healthComp = new HealthComponent(maxHp, currHp);
		pos = _pos;

		id = DEFAULT_ID;

		solid = _solid;
		spriteSize = _spriteSize;
	}

	~Player()
	{}
private:
	
};
