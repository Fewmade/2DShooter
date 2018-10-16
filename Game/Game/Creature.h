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

	// �������������� ���������� ������������(� ������� ������������ ������ ����)
	virtual void individualCollisions(int objectID)
	{ }

	virtual ~Creature()
	{
		delete healthComp;
		healthComp = nullptr;
	}


	void move(Room & room, int directory, float distance)
	{
		Vector2f newPos; // ����� �������
		Vector2f dPos;   // ��������� ���������

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

		// ��������� ����������� ��� �������� �� x
		float nx = pos.x + dPos.x;
		float ny = pos.y;

		for (unsigned int i = unsigned(ny); i < ceil(ny + float(spriteSize.y) / CELL_HEIGHT); i++)
		{
			for (unsigned int j = unsigned(nx); j < ceil(nx + float(spriteSize.x) / CELL_WIDTH); j++)
			{
				// ���� ��� ������� ������
				if (solid && room.getCell(j, i) >= 0 && objects[room.getCell(j, i)].getSolid())
				{
					// � ����� ������� ����������� � ��������
					if (nx > j + 0.5f)
					{
						nx = float(j + 1);
					}
					else if (nx + float(spriteSize.x) / CELL_WIDTH < j + 0.5f)
					{
						nx = float(j - float(spriteSize.x) / CELL_WIDTH);
					}
				}
			}
		}
		newPos.x = nx;

		
		// ��������� ����������� ��� �������� �� y
		nx = pos.x;
		ny = pos.y + dPos.y;

		for (unsigned int i = unsigned(ny); i < unsigned(ceil(ny + float(spriteSize.y) / CELL_HEIGHT)); i++)
		{
			for (unsigned int j = unsigned(nx); j < unsigned(ceil(nx + float(spriteSize.x) / CELL_WIDTH)); j++)
			{
				// ���� ��� ������� ������
				if (solid && room.getCell(j, i) >= 0 && objects[room.getCell(j, i)].getSolid())
				{
					// � ����� ������� ����������� � ��������
					if (ny > i + 0.5f)
					{
						ny = float(i + 1);
					}
					else if (ny + float(spriteSize.y) / CELL_HEIGHT < i + 0.5f)
					{
						ny = float(i - float(spriteSize.y) / CELL_HEIGHT);
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
				//individualCollisions(room.getCell(j, i));
			}
		}
	}
protected:
	HealthComponent*	healthComp;
	Room*				room;

	float				speed;
	unsigned int		id;
};
