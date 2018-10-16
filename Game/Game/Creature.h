#pragma once

#include <cmath>

#include "DynamicObject.h"
#include "HealthComponent.h"
#include "Room.h"
#include "Consts.h"

class Creature : public DynamicObject
{
public:
	Creature()
	{ }
	Creature(Image _image, Vector2f _pos, Room *_room, int maxHp, int currHp, bool _solid = false, Vector2i _spriteSize = Vector2i(32, 32))
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);

		healthComp = new HealthComponent(maxHp, currHp);
		pos = _pos;
		room = _room;

		id = DEFAULT_ID;

		solid = _solid;
		spriteSize = _spriteSize;
	}

	void setSpeed(float _speed)
	{
		speed = _speed;
	}
	float getSpeed() const
	{
		return speed;
	}
	int getID() const
	{
		return id;
	}
	Room& getRoom() const
	{
		return *room;
	}

	// Индивидуальный обработчик столкновений(у каждого производного класса свой)
	virtual void individualCollisions(int objectID)
	{ }

	virtual ~Creature()
	{
		delete healthComp;
		healthComp = nullptr;
	}


	void move(Room & room, int directory, float distance)
	{
		Vector2f newPos; // Новая позиция
		Vector2f dPos;   // Изменение координат

		switch (directory)
		{
		case         UP: dPos.y = -distance;                   dPos.x = 0;
			break;
		case   UP_RIGHT: dPos.y = -sqrt(pow(distance, 2) / 2); dPos.x = sqrt(pow(distance, 2) / 2);
			break;
		case      RIGHT: dPos.y = 0;                           dPos.x = distance;
			break;
		case RIGHT_DOWN: dPos.y = sqrt(pow(distance, 2) / 2);  dPos.x = sqrt(pow(distance, 2) / 2);
			break;
		case       DOWN: dPos.y = distance;                    dPos.x = 0;
			break;
		case  DOWN_LEFT: dPos.y = sqrt(pow(distance, 2) / 2);  dPos.x = -sqrt(pow(distance, 2) / 2);
			break;
		case       LEFT: dPos.y = 0;                           dPos.x = -distance;
			break;
		case    LEFT_UP: dPos.y = -sqrt(pow(distance, 2) / 2); dPos.x = -sqrt(pow(distance, 2) / 2);
			break;
		}

		// Обработка столкновний при движении по x
		float nx = pos.x + dPos.x;
		float ny = pos.y;

		unsigned int mx = unsigned(nx + ceil(nx + spriteSize.x / CELL_WIDTH)) / 2;
		for (unsigned int i = unsigned(ny); i < unsigned(ceil(ny + spriteSize.y / CELL_HEIGHT)); i++)
		{
			for (unsigned int j = unsigned(nx); j < unsigned(ceil(nx + spriteSize.x / CELL_WIDTH)); j++)
			{
				// Если оба обьекта твёрдые
				if (solid && room.getCell(j, i) >= 0 && objects[room.getCell(j, i)].getSolid())
				{
					// С какой стороны столкнулись с обьектом
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
		
		// Обработка столкновний при движении по y
		nx = pos.x;
		ny = pos.y + dPos.y;

		unsigned int my = unsigned(ny + ceil(ny + spriteSize.y / CELL_HEIGHT)) / 2;
		for (unsigned int i = unsigned(ny); i < unsigned(ceil(ny + spriteSize.y / CELL_HEIGHT)); i++)
		{
			for (unsigned int j = unsigned(nx); j < unsigned(ceil(nx + spriteSize.x / CELL_WIDTH)); j++)
			{
				// Если оба обьекта твёрдые
				if (solid && room.getCell(j, i) >= 0 && objects[room.getCell(j, i)].getSolid())
				{
					// С какой стороны столкнулись с обьектом
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

		for (unsigned int i = unsigned(pos.y); i < unsigned(ceil(pos.y + spriteSize.y / CELL_HEIGHT)); i++)
		{
			for (unsigned int j = unsigned(pos.x); j < unsigned(ceil(pos.x + spriteSize.x / CELL_WIDTH)); j++)
			{
				individualCollisions(room.getCell(j, i));
			}
		}
	}
protected:
	HealthComponent*	healthComp;
	Room*				room;

	float				speed;
	unsigned int		id;
};
