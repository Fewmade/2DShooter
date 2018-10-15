#pragma once
#include "Creature.h"

// Conditions
const int STAY = 0;
const int GO   = 1;
const int RUN  = 2;

struct PlayerStatus
{
	int condition;
	int dir;
};

PlayerStatus getPlayerStatus()
{
	PlayerStatus status;
	status.condition = STAY;

	// Движение по диагоналям
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
	{
		status.condition = GO;
		status.dir = UP_RIGHT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
	{
		status.condition = GO;
		status.dir = RIGHT_DOWN;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
	{
		status.condition = GO;
		status.dir = DOWN_LEFT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
	{
		status.condition = GO;
		status.dir = LEFT_UP;
	}

	// Движение по прямым
	else if (Keyboard::isKeyPressed(Keyboard::W))
	{
		status.condition = GO;
		status.dir = UP;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		status.condition = GO;
		status.dir = RIGHT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		status.condition = GO;
		status.dir = DOWN;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
		status.condition = GO;
		status.dir = LEFT;
	}

	// Бег
	if (Keyboard::isKeyPressed(Keyboard::LShift) && status.condition != STAY)
	{
		status.condition = RUN;
	}

	return status;
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
