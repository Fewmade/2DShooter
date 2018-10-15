#pragma once

#include <cmath>

#include "DynamicObject.h"
#include "HealthComponent.h"
#include "Room.h"
#include "CreaturesID.h"


class Creature : public DynamicObject
{
public:
	Creature()
	{
		healthComp = new HealthComponent(0);
		pos = Vector2f(0, 0);

		id = DEFAULT_ID;
	}
	Creature(Image _image, Vector2f _pos, int maxHp, int currHp, bool _solid = false, Vector2i _spriteSize = Vector2i(32, 32))
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

	virtual ~Creature()
	{
		delete healthComp;
		healthComp = nullptr;
	}

	void move(Room & room, int status, float distance = 0)
	{
		Vector2f newPos; // ����� �������
		Vector2f dPos;   // ��������� ���������

		switch (status)
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

		unsigned int mx = unsigned(nx + ceil(nx + spriteSize.x / CELL_WIDTH)) / 2;
		for (unsigned int i = unsigned(ny); i < unsigned(ceil(ny + spriteSize.y / CELL_HEIGHT)); i++)
		{
			for (unsigned int j = unsigned(nx); j < unsigned(ceil(nx + spriteSize.x / CELL_WIDTH)); j++)
			{
				// ���� ��� ������� ������
				if (solid && room.getCell(j, i) >= 0 && objects[room.getCell(j, i)].getSolid())
				{
					// � ����� ������� ����������� � ��������
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
		
		// ��������� ����������� ��� �������� �� y
		nx = pos.x;
		ny = pos.y + dPos.y;

		unsigned int my = unsigned(ny + ceil(ny + spriteSize.y / CELL_HEIGHT)) / 2;
		for (unsigned int i = unsigned(ny); i < unsigned(ceil(ny + spriteSize.y / CELL_HEIGHT)); i++)
		{
			for (unsigned int j = unsigned(nx); j < unsigned(ceil(nx + spriteSize.x / CELL_WIDTH)); j++)
			{
				// ���� ��� ������� ������
				if (solid && room.getCell(j, i) >= 0 && objects[room.getCell(j, i)].getSolid())
				{
					// � ����� ������� ����������� � ��������
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
	HealthComponent*	healthComp;

	float				speed;
	unsigned int		id;
};
