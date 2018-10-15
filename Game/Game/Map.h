#pragma once

#include <vector>
#include <queue>
#include "Room.h"

// Глобальная карта
std::vector<std::vector<int> > globalMap(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, 1));

// Все комнаты на карте
std::vector<Room> rooms;

std::vector<std::vector<int> > generateRandomMap(unsigned int roomCreatingChance = 50) 
{
	// roomCreatingChance - Шанс с которым создаётся комната

	std::vector<std::vector<int> > map(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, -1));

	// Очередь из созданных комнат
	std::queue<Vector2i> roomCreatingQueue;
	roomCreatingQueue.push(Vector2i(MAP_WIDTH / 2, MAP_HEIGHT / 2));

	// Проверена ли комната
	std::vector<std::vector<bool> > checked(MAP_HEIGHT, std::vector<bool>(MAP_WIDTH));
	checked[MAP_WIDTH / 2][MAP_HEIGHT / 2] = true;

	// Добавляем в очередь центральную комнату
	rooms.push_back(Room());
	map[MAP_WIDTH / 2][MAP_HEIGHT / 2] = rooms.size() - 1;

	while (roomCreatingQueue.size() > 0)
	{
		Vector2i cord = roomCreatingQueue.front();
		roomCreatingQueue.pop();

		// Смотрим все комнаты вокруг неё
		for (int dx = -1; dx <= 1; dx++)
		{
			for (int dy = -1; dy <= 1; dy++)
			{
				// dx * dx = abs(dx)
				if (dx * dx + dy * dy == 1)
				{
					Vector2i newCord = cord + Vector2i(dx, dy);
					// Если комната с новыми координатами ещё не проверялась и находится в пределах карты
					if (newCord.x >= 0 && newCord.x < MAP_WIDTH &&
						newCord.y >= 0 && newCord.y < MAP_HEIGHT &&
						!checked[newCord.y][newCord.x])
					{
						// Ставим что комнату проверили
						checked[newCord.y][newCord.x] = true;

						srand(int(time(NULL)) + rand());
						unsigned int chance = rand() % 100;

						// С шансом roomCreatingChance создаём новую комнату
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