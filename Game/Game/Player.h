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
			unsigned int direction;
			
			// Верхнаяя дверь
			if (y < ROOM_HEIGHT / 2 - 1)
			{
				pos.y = ROOM_HEIGHT - 1.f - float(collisionRect.height + distanceFromDoor) / CELL_HEIGHT;
				direction = UP;
			}
			// Нижняя дверь
			else if (y > ROOM_HEIGHT / 2 + 1)
			{
				pos.y = 1.f - float(collisionRect.top - distanceFromDoor) / CELL_HEIGHT;
				direction = DOWN;
			}
			// Левая дверь
			else if (x < ROOM_WIDTH / 2 - 1)
			{
				pos.x = ROOM_WIDTH - 1.f - float(collisionRect.width + distanceFromDoor) / CELL_WIDTH;
				direction = LEFT;
			}
			// Правая дверь
			else if (x > ROOM_HEIGHT / 2 + 1)
			{
				pos.x = 1.f - float(collisionRect.left - distanceFromDoor) / CELL_WIDTH;
				direction = RIGHT;
			}

			// Номер новой комнаты
			int newRoomNumber = 0;

			// Если дверь ни к чему не ведёт, создаём новую
			if (room->getConnections()[direction] == -1)
			{
				bool upDoor = true;
				bool rightDoor = true;
				bool downDoor = true;
				bool leftDoor = true;

				Room newRoom(generateRandomRoom(upDoor, rightDoor, downDoor, leftDoor));

				// Ищем комнату, в которой находится персонаж
				int i = 0;
				for (; i < maxNumberOfRooms; i++)
				{
					if (room == &rooms[i])
					{
						break;
					}
				}

				// Направление наоборот
				unsigned int invDir;
				if (direction == UP)    { invDir = DOWN; }
				if (direction == RIGHT) { invDir = LEFT; }
				if (direction == DOWN)  { invDir = UP; }
				if (direction == LEFT)  { invDir = RIGHT; }

				newRoomNumber = roomCreatingQueue.front();

				roomCreatingQueue.pop();
				roomCreatingQueue.push(newRoomNumber);

				// Ставим соединения между комнатами
				newRoom.getConnections()[invDir] = i;
				room->getConnections()[direction] = newRoomNumber;

				rooms[newRoomNumber] = newRoom;
			}
			else
			{
				newRoomNumber = room->getConnections()[direction];
			}

			room = &rooms[newRoomNumber];

			break;
		}
	}

	~Player()
	{}
private:
	
};
