#pragma once

#include <vector>
#include <iostream>
#include "StaticObject.h"

const unsigned int ROOM_WIDTH  = 16;
const unsigned int ROOM_HEIGHT = 16;

std::vector<std::vector<StaticObject> > generateRanomMap()
{
	std::vector<std::vector<StaticObject> > map(ROOM_HEIGHT, std::vector<StaticObject>(ROOM_WIDTH));

	return map;
}

class Room
{
private:
	std::vector<std::vector<StaticObject> > map;

	bool connectingToRightRoom;
	bool connectingToLeftRoom;
	bool connectingToUpRoom;
	bool connectingToDownRoom;

public:
	Room(std::vector<std::vector<StaticObject> > _map = generateRanomMap()) : map(_map) 
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

	void changeCell(Vector2i pos, StaticObject obj)
	{
		map[pos.y][pos.x] = obj;
	}

	StaticObject getCell(Vector2i pos)
	{
		return map[pos.y][pos.x];
	}
};

