#pragma once

#include <vector>
#include <iostream>
#include "StaticObject.h"

const unsigned int ROOM_WIDTH  = 16;
const unsigned int ROOM_HEIGHT = 16;

std::vector<std::vector<int> > generateRanomRoom()
{
	std::vector<std::vector<int> > map(ROOM_HEIGHT, std::vector<int>(ROOM_WIDTH, -1));

	for (unsigned int i = 0; i < ROOM_HEIGHT; i++) 
	{
		for (unsigned int j = 0; j < ROOM_WIDTH; j++)
		{
			srand(int(time(NULL)) + rand());
			int chance = rand() % 100;

			if (chance <= 10)
			{
				map[i][j] = 0;
			}
		}
	}

	return map;
}

class Room
{
private:
	std::vector<std::vector<int> > map;

	// Соединено ли с правой, левой, верхней и нижней комнатой
	bool connectingToRightRoom;
	bool connectingToLeftRoom;
	bool connectingToUpRoom;
	bool connectingToDownRoom;

public:
	Room(std::vector<std::vector<int> > _map = generateRanomRoom()) : map(_map)
	{
		connectingToRightRoom = false;
		connectingToLeftRoom  = false;
		connectingToUpRoom    = false;
		connectingToDownRoom  = false;
	}

	std::vector<std::vector<int> > getMap()
	{
		return map;
	}
	void setMap(std::vector<std::vector<int> > _map)
	{
		map = _map;
	}

	void setCell(Vector2i pos, int obj)
	{
		map[pos.y][pos.x] = obj;
	}
	void setCell(unsigned int x, unsigned int y, int obj)
	{
		map[x][y] = obj;
	}
	unsigned int getCell(Vector2i pos)
	{
		return map[pos.y][pos.x];
	}
	unsigned int getCell(unsigned int x, unsigned int y)
	{
		return map[y][x];
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

