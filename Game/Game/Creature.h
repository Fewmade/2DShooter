#pragma once

#include <cmath>
#include "DynamicObject.h"
#include "HealthComponent.h"
#include "Room.h"

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

	void move(Room & room, int status, float distance = 0)
	{
		Vector2f newPos;
		Vector2f dPos;

		switch (status)
		{
		case STAY: dPos.x = 0; dPos.y = 0;
			break;

		case         GO_UP: dPos.y = -distance;                   dPos.x = 0;
			break;
		case   GO_UP_RIGHT: dPos.y = -sqrt(pow(distance, 2) / 2); dPos.x = sqrt(pow(distance, 2) / 2);
			break;
		case      GO_RIGHT: dPos.y = 0;                           dPos.x = distance;
			break;
		case GO_RIGHT_DOWN: dPos.y = sqrt(pow(distance, 2) / 2);  dPos.x = sqrt(pow(distance, 2) / 2);
			break;
		case       GO_DOWN: dPos.y = distance;                    dPos.x = 0;
			break;
		case  GO_DOWN_LEFT: dPos.y = sqrt(pow(distance, 2) / 2);  dPos.x = -sqrt(pow(distance, 2) / 2);
			break;
		case       GO_LEFT: dPos.y = 0;                           dPos.x = -distance;
			break;
		case    GO_LEFT_UP: dPos.y = -sqrt(pow(distance, 2) / 2); dPos.x = -sqrt(pow(distance, 2) / 2);
			break;
		}

		float nx = pos.x + dPos.x;
		float ny = pos.y;

		unsigned int mx = unsigned(nx + ceil(nx + spriteSize.x / 32)) / 2;
		for (unsigned int i = unsigned(ny); i < unsigned(ceil(ny + spriteSize.y / 32)); i++)
		{
			for (unsigned int j = unsigned(nx); j < unsigned(ceil(nx + spriteSize.x / 32)); j++)
			{
				if (room.getCell(j, i) >= 0 && objects[room.getCell(j, i)].getSolid())
				{
					if (j < mx)
					{
						nx = float(j + 1);
					}
					else
					{
						nx = float(j - spriteSize.x / 32);
					}
				}
			}
		}
		newPos.x = nx;
		
		nx = pos.x;
		ny = pos.y + dPos.y;

		unsigned int my = unsigned(ny + ceil(ny + spriteSize.y / 32)) / 2;
		for (unsigned int i = unsigned(ny); i < unsigned(ceil(ny + spriteSize.y / 32)); i++)
		{
			for (unsigned int j = unsigned(nx); j < unsigned(ceil(nx + spriteSize.x / 32)); j++)
			{
				if (room.getCell(j, i) >= 0 && objects[room.getCell(j, i)].getSolid())
				{
					if (i < my)
					{
						ny = float(i + 1);
					}
					else
					{
						ny = float(i - spriteSize.y / 32);
					}
				}
			}
		}
		newPos.y = ny;

		pos = newPos;
	}

protected:
	HealthComponent* healthComp;

	float speed;

	
};
