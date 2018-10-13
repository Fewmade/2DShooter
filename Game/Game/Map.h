#pragma once

#include <vector>
#include <queue>
#include "Room.h"

const unsigned int MAP_WIDTH  = 11;
const unsigned int MAP_HEIGHT = 11;

std::vector<std::vector<int> > globalMap(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, -1));

std::vector<Room> rooms;

/*
Когда-нибудь я напишу комментарии
Но не сегодня :)
*/

std::vector<std::vector<int> > generateRandomMap(unsigned int roomCreatingChance = 50)
{
	std::vector<std::vector<int> > map(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, -1));

	std::queue<Vector2i> roomCreatingQueue;
	roomCreatingQueue.push(Vector2i(MAP_WIDTH / 2, MAP_HEIGHT / 2));

	std::vector<std::vector<bool> > checked(MAP_HEIGHT, std::vector<bool>(MAP_WIDTH));
	checked[MAP_WIDTH / 2][MAP_HEIGHT / 2] = true;

	rooms.push_back(Room());
	map[MAP_WIDTH / 2][MAP_HEIGHT / 2] = rooms.size() - 1;

	while (roomCreatingQueue.size() > 0)
	{
		Vector2i cord = roomCreatingQueue.front();
		roomCreatingQueue.pop();

		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				if (dx * dx + dy * dy == 1)
				{
					Vector2i newCord = cord + Vector2i(dx, dy);
					if (newCord.x >= 0 && newCord.x < MAP_WIDTH &&
						newCord.y >= 0 && newCord.y < MAP_HEIGHT &&
						!checked[newCord.y][newCord.x])
					{
						checked[newCord.y][newCord.x] = true;

						srand(int(time(NULL)) + rand());
						unsigned int chance = rand() % 100;

						if (chance <= roomCreatingChance)
						{
							rooms.push_back(Room());
							map[newCord.y][newCord.x] = rooms.size() - 1;
							roomCreatingQueue.push(newCord);
						}
					}

				}
			}
		}
	}

	return map;
}