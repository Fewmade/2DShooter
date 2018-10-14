#pragma once

#include <vector>
#include <iostream>
#include "StaticObject.h"

const unsigned int ROOM_WIDTH  = 16;
const unsigned int ROOM_HEIGHT = 16;

const unsigned int WALL = 0;
const unsigned int STONE = 1;

std::vector<std::vector<int> > generateRanomRoom()
{
	std::vector<std::vector<int> > map(ROOM_HEIGHT, std::vector<int>(ROOM_WIDTH, -1));

	//Стены по бокам
	for (unsigned int i = 0; i < ROOM_HEIGHT; i++)
	{
		map[i][0] = WALL;
		map[i][ROOM_WIDTH - 1] = WALL;
	}

	for (unsigned int j = 0; j < ROOM_WIDTH; j++)
	{
		map[0][j] = WALL;
		map[ROOM_HEIGHT - 1][j] = WALL;
	}

	//Рандомно расположенные камни
	for (unsigned int i = 1; i < ROOM_HEIGHT - 1; i++) 
	{
		for (unsigned int j = 0; j < ROOM_WIDTH - 1; j++)
		{
			if (map[i][j] == -1)
			{
				srand(int(time(NULL)) + rand());
				int chance = rand() % 100;

				if (chance <= 5)
				{
					map[i][j] = STONE;
				}
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

