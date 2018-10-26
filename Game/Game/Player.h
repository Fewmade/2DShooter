#pragma once
#include "Creature.h"
#include "EnemyNPC.h"

CreatureStatus getPlayerStatus()
{
	CreatureStatus status;
	status.condition = STAY;
	status.attack = false;

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

	//Атака
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		status.attack = true;
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
	Player(Image _image, Vector2f _pos, Room *_room, int maxHp, int currHp, bool _solid = false, Vector2u _spriteSize = Vector2u(32, 32), IntRect _collisionRect = IntRect(0, 0, 32, 32), int _damage = 30)
	{
		image = _image;

		
		texture.loadFromImage(image);

		healthComp = new HealthComponent(maxHp, currHp);
		pos = _pos;
		room = _room;
		damage = _damage;

		id = DEFAULT_ID;

		solid = _solid;
		collisionRect = _collisionRect;
		spriteSize = _spriteSize;
	}

	void changeRoom(int objectID, unsigned int x, unsigned int y)
	{
		unsigned int direction;

		// Верхнаяя дверь
		if (y < ROOM_HEIGHT / 2 - 1)
		{
			pos.y = ROOM_HEIGHT - 1.f - float(collisionRect.height) / CELL_HEIGHT - distanceFromDoor;
			direction = UP;
		}
		// Нижняя дверь
		else if (y > ROOM_HEIGHT / 2 + 1)
		{
			pos.y = 1.f - float(collisionRect.top) / CELL_HEIGHT + distanceFromDoor;
			direction = DOWN;
		}
		// Левая дверь
		else if (x < ROOM_WIDTH / 2 - 1)
		{
			pos.x = ROOM_WIDTH - 1.f - float(collisionRect.width) / CELL_WIDTH - distanceFromDoor;
			direction = LEFT;
		}
		// Правая дверь
		else if (x > ROOM_HEIGHT / 2 + 1)
		{
			pos.x = 1.f - float(collisionRect.left) / CELL_WIDTH + distanceFromDoor;
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

			// Ищем комнату, в которой находится персонаж
			unsigned int i = 0;
			for (; i < rooms.size(); i++)
			{
				if (room == rooms[i])
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

			rooms.push_back(new Room(generateRandomRoom(upDoor, rightDoor, downDoor, leftDoor)));

			newRoomNumber = rooms.size() - 1;

			// Ставим соединения между комнатами
			rooms[newRoomNumber]->getConnections()[invDir] = i;
			room->getConnections()[direction] = newRoomNumber;

			if (room->getConnections()[UP] == -1)
			{
				room->setCell(ROOM_WIDTH / 2, 0, WALL);
			}
			if (room->getConnections()[RIGHT] == -1)
			{
				room->setCell(ROOM_WIDTH - 1, ROOM_HEIGHT / 2, WALL);
			}
			if (room->getConnections()[DOWN] == -1)
			{
				room->setCell(ROOM_WIDTH / 2, ROOM_HEIGHT - 1, WALL);
			}
			if (room->getConnections()[LEFT] == -1)
			{
				room->setCell(0, ROOM_HEIGHT / 2, WALL);
			}
		}
		else
		{
			newRoomNumber = room->getConnections()[direction];
		}

		room = rooms[newRoomNumber];
	}

	void individualCollisions(int objectID, unsigned int x, unsigned int y)
	{
		switch (objectID)
		{
		case DOOR: 
			healthComp->changeHP(+10);
			changeRoom(objectID, x, y);
			break;
		case STONE:
			healthComp->changeHP(-10);
			room->setCell(x, y, -1);
			break;
		}
	}

	void attack(std::vector<EnemyNPC*>& _objects, CreatureStatus status)
	{
		Vector2f playerCenter(pos.x + spriteSize.x / (CELL_WIDTH * 2.f), pos.y + spriteSize.y / (CELL_HEIGHT * 2.f));

		float upEdgeOfAtack;
		float downEdgeOfAtack;
		float rightEdgeOfAtack;
		float leftEdgeOfAtack;

		// Грани атаки игрока
		if (status.dir == UP)
		{
			upEdgeOfAtack    = playerCenter.y - atackSize.y;
			downEdgeOfAtack  = playerCenter.y;
			rightEdgeOfAtack = playerCenter.x + atackSize.x / 2.f;
			leftEdgeOfAtack  = playerCenter.x - atackSize.x / 2.f;
		}
		else if (status.dir == RIGHT)
		{
			upEdgeOfAtack    = playerCenter.y - atackSize.y / 2.f;
			downEdgeOfAtack  = playerCenter.y + atackSize.y / 2.f;
			rightEdgeOfAtack = playerCenter.x + atackSize.x;
			leftEdgeOfAtack  = playerCenter.x;
		}
		else if (status.dir == DOWN)
		{
			upEdgeOfAtack    = playerCenter.y;
			downEdgeOfAtack  = playerCenter.y + atackSize.y;
			rightEdgeOfAtack = playerCenter.x + atackSize.x / 2.f;
			leftEdgeOfAtack  = playerCenter.x - atackSize.x / 2.f;
		}
		else if (status.dir == LEFT)
		{
			upEdgeOfAtack    = playerCenter.y - atackSize.y / 2.f;
			downEdgeOfAtack  = playerCenter.y + atackSize.y / 2.f;
			rightEdgeOfAtack = playerCenter.x;
			leftEdgeOfAtack  = playerCenter.x - atackSize.x;
		}

		for (unsigned int i = 0; i < _objects.size(); i++)
		{
			// Object Collision Rect
			IntRect OCR = _objects[i]->getCollisionRect();
			// Object Position
			Vector2f OP = _objects[i]->getPos();

			// Грани обьекта
			float upEdgeOfObject    = OP.y + float(OCR.top)               / CELL_HEIGHT;
			float downEdgeOfObject  = OP.y + float(OCR.top  + OCR.height) / CELL_HEIGHT;
			float rightEdgeOfObject = OP.x + float(OCR.left + OCR.width)  / CELL_WIDTH;
			float leftEdgeOfObject  = OP.x + float(OCR.left)              / CELL_WIDTH;

			// Попал ли игрок
			// По Y
			if ((upEdgeOfObject < upEdgeOfAtack    && upEdgeOfAtack    < downEdgeOfObject) ||
				(upEdgeOfObject < downEdgeOfAtack  && downEdgeOfAtack  < downEdgeOfObject) ||
				(upEdgeOfAtack  < upEdgeOfObject   && upEdgeOfObject   < downEdgeOfAtack)  ||
				(upEdgeOfAtack  < downEdgeOfObject && downEdgeOfObject < downEdgeOfAtack))
			{
				// По X
				if ((leftEdgeOfObject < leftEdgeOfAtack   && leftEdgeOfAtack   < rightEdgeOfObject) ||
					(leftEdgeOfObject < rightEdgeOfAtack  && rightEdgeOfAtack  < rightEdgeOfObject) ||
					(leftEdgeOfAtack  < leftEdgeOfObject  && leftEdgeOfObject  < rightEdgeOfAtack)  ||
					(leftEdgeOfAtack  < rightEdgeOfObject && rightEdgeOfObject < rightEdgeOfAtack))
				{
					_objects[i]->dealDamage(damage);
				}
			}
		}
	}

	~Player()
	{}
private:
	
};
