#pragma once
#include "Creature.h"
#include "EnemyNPC.h"

CreatureStatus getPlayerStatus()
{
	CreatureStatus status;
	status.condition = STAY;
	status.attack = false;

	// �������� �� ����������
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

	// �������� �� ������
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

	//�����
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		status.attack = true;
	}

	// ���
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

		//image.createMaskFromColor();
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

		// �������� �����
		if (y < ROOM_HEIGHT / 2 - 1)
		{
			pos.y = ROOM_HEIGHT - 1.f - float(collisionRect.height) / CELL_HEIGHT - distanceFromDoor;
			direction = UP;
		}
		// ������ �����
		else if (y > ROOM_HEIGHT / 2 + 1)
		{
			pos.y = 1.f - float(collisionRect.top) / CELL_HEIGHT + distanceFromDoor;
			direction = DOWN;
		}
		// ����� �����
		else if (x < ROOM_WIDTH / 2 - 1)
		{
			pos.x = ROOM_WIDTH - 1.f - float(collisionRect.width) / CELL_WIDTH - distanceFromDoor;
			direction = LEFT;
		}
		// ������ �����
		else if (x > ROOM_HEIGHT / 2 + 1)
		{
			pos.x = 1.f - float(collisionRect.left) / CELL_WIDTH + distanceFromDoor;
			direction = RIGHT;
		}

		// ����� ����� �������
		int newRoomNumber = 0;

		// ���� ����� �� � ���� �� ����, ������ �����
		if (room->getConnections()[direction] == -1)
		{
			bool upDoor = true;
			bool rightDoor = true;
			bool downDoor = true;
			bool leftDoor = true;

			// ���� �������, � ������� ��������� ��������
			unsigned int i = 0;
			for (; i < rooms.size(); i++)
			{
				if (room == rooms[i])
				{
					break;
				}
			}

			// ����������� ��������
			unsigned int invDir;
			if (direction == UP)    { invDir = DOWN; }
			if (direction == RIGHT) { invDir = LEFT; }
			if (direction == DOWN)  { invDir = UP; }
			if (direction == LEFT)  { invDir = RIGHT; }

			rooms.push_back(new Room(generateRandomRoom(upDoor, rightDoor, downDoor, leftDoor)));

			newRoomNumber = rooms.size() - 1;

			// ������ ���������� ����� ���������
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

	void attack(std::vector<EnemyNPC*>& _objects)
	{
		std::cerr << "Player Attack!" << std::endl;

		for (int i = 0; i < _objects.size(); i++)
		{
			Vector2f dif =  pos - _objects[i]->getPos() ;
			std::cerr << dif.x << " " << dif.y << std::endl;
			if ((abs(dif.x) <= 1) || (abs(dif.y) <= 1))
			{
				std::cerr << "Deal damage" << std::endl;
				_objects[i]->dealDamage(damage);
			}
		}
	}

	~Player()
	{}
private:
	
};
