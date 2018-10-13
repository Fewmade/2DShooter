#pragma once

#include <vector>
#include <iostream>
#include "StaticObject.h"

const unsigned int ROOM_WIDTH  = 16;
const unsigned int ROOM_HEIGHT = 16;

//Всё в говне
std::vector<std::vector<StaticObject> > generateRanomRoom()
{
	std::vector<std::vector<StaticObject> > map(ROOM_HEIGHT, std::vector<StaticObject>(ROOM_WIDTH));

	for (unsigned int i = 0; i < ROOM_HEIGHT; i++) 
	{
		for (unsigned int j = 0; j < ROOM_WIDTH; j++)
		{
			srand(int(time(NULL)) + rand());
			int chance = rand();

			if (chance > 10)
			{
				map[i][j] = StaticObject(Vector2i(i, j));
			}
		}
	}

	return map;
}
//Дальше нормас

class Room
{
private:
	std::vector<std::vector<StaticObject> > map;

	// Соединено ли с правой, левойБ верхней и нижней комнатой
	bool connectingToRightRoom;
	bool connectingToLeftRoom;
	bool connectingToUpRoom;
	bool connectingToDownRoom;

public:
	Room(std::vector<std::vector<StaticObject> > _map = generateRanomRoom()) : map(_map)
	{
		connectingToRightRoom = false;
		connectingToLeftRoom  = false;
		connectingToUpRoom    = false;
		connectingToDownRoom  = false;
	}

	std::vector<std::vector<StaticObject> > getMap()
	{
		return map;
	}
	void setMap(std::vector<std::vector<StaticObject> > _map)
	{
		map = _map;
	}

	void setCell(Vector2i pos, StaticObject obj)
	{
		map[pos.y][pos.x] = obj;
	}
	StaticObject getCell(Vector2i pos)
	{
		return map[pos.y][pos.x];
	}

	void setConnectingToRightRoom(bool value)
	{
		connectingToRightRoom = value;
	}
	void setConnectingToLeftRoom(bool value)
	{
		connectingToLeftRoom = value;
	}
	void setConnectingToUpRoom(bool value)
	{
		connectingToUpRoom = value;
	}
	void setConnectingToDownRoom(bool value)
	{
		connectingToDownRoom = value;
	}

	bool getConnectingToRightRoom()
	{
		return connectingToRightRoom;
	}
	bool getConnectingToLeftRoom()
	{
		return connectingToLeftRoom;
	}
	bool getConnectingToUpRoom()
	{
		return connectingToUpRoom;
	}
	bool getConnectingToDownRoom()
	{
		return connectingToDownRoom;
	}
};

