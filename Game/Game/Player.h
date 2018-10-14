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
