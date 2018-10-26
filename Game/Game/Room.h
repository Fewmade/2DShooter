#pragma once

#include <vector>
#include <queue>
#include <iostream>
#include "StaticObject.h"
#include "Consts.h"

std::vector<StaticObject> objects(NUMBER_OF_OBJECTS);

std::vector<std::vector<int> > generateRandomRoom(bool upRoom, bool rightRoom, bool downRoom, bool leftRoom)
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

	// Двери
	if (upRoom)
	{
		map[0][ROOM_WIDTH / 2]               = DOOR;
	}
	if (rightRoom)
	{
		map[ROOM_HEIGHT / 2][ROOM_WIDTH - 1] = DOOR;
	}
	if (downRoom)
	{
		map[ROOM_HEIGHT - 1][ROOM_WIDTH / 2] = DOOR;
	}
	if (leftRoom)
	{
		map[ROOM_HEIGHT / 2][0]              = DOOR;
	}

	return map;
}

class Room
{
private:
	std::vector<std::vector<int> > map;

	// Массив соединений дверей к комнатам(я заню что дверей 4, а направлений 8)
	std::vector<int> connections;
public:
	Room(std::vector<std::vector<int> > _map) : map(_map)
	{
		// Двери для всех направлений
		connections.resize(numOfDirections, -1);
	}

	std::vector<std::vector<int> > getMap() const
	{
		return map;
	}
	void setMap(std::vector<std::vector<int> > _map)
	{
		map = _map;
	}

	std::vector<int>& getConnections()
	{
		return connections;
	}

	void setCell(Vector2i pos, int obj)
	{
		map[pos.y][pos.x] = obj;
	}
	void setCell(unsigned int x, unsigned int y, int obj)
	{
		map[y][x] = obj;
	}

	int getCell(Vector2i pos) const
	{
		return map[pos.y][pos.x];
	}
	int getCell(unsigned int x, unsigned int y) const
	{
		return map[y][x];
	}
};

std::vector<Room*> rooms;

