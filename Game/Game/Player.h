#pragma once
#include "Creature.h"

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
	{ }
	Player(Image _image, Vector2f _pos, Room *_room, int maxHp, int currHp, bool _solid = false, IntRect _collisionRect = IntRect(0, 0, 32, 32))
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);

		healthComp = new HealthComponent(maxHp, currHp);
		pos = _pos;
		room = _room;

		id = DEFAULT_ID;

		solid = _solid;
		collisionRect = _collisionRect;
	}

	void individualCollisions(int objectID, unsigned int x, unsigned int y)
	{
		
		switch (objectID)
		{
		case DOOR:

			int i = 0;
			for (; i < maxNumberOfRooms; i++)
			{
				if (room == &rooms[i])
				{
					std::cerr << i << " ";
					break;
				}
			}

			if (i == maxNumberOfRooms)
			{
				i = 0;
			}
			else
			{
				i++;
			}

			rooms[i] = Room(generateRandomRoom(true, true, true, true));
			room = &rooms[i];

			// Верхнаяя дверь
			if (y < ROOM_HEIGHT / 2 - 1)
			{
				pos.y = ROOM_HEIGHT - 1.f - float(collisionRect.height + distanceFromDoor) / CELL_HEIGHT;
			}
			// Нижняя дверь
			else if (y > ROOM_HEIGHT / 2 + 1)
			{
				pos.y = 1.f - float(collisionRect.top - distanceFromDoor) / CELL_HEIGHT;
			}
			// Левая дверь
			else if (x < ROOM_WIDTH / 2 - 1)
			{
				pos.x = ROOM_WIDTH - 1.f - float(collisionRect.width + distanceFromDoor) / CELL_WIDTH;
			}
			// Правая дверь
			else if (x > ROOM_HEIGHT / 2 + 1)
			{
				pos.x = 1.f - float(collisionRect.left - distanceFromDoor) / CELL_WIDTH;
			}

			break;
		}
	}

	~Player()
	{}
private:
	
};
