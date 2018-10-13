#include <SFML/Graphics.hpp>
#include "AllyNPC.h"
#include "Creature.h"
#include "DynamicObject.h"
#include "EnemyNPC.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Map.h"
#include "Player.h"
#include "Room.h"
#include "StaticObject.h"

using namespace sf;

// Размер 1 клетки карты в пикселях
const unsigned int CELL_WIDTH  = 32;
const unsigned int CELL_HEIGHT = 32;

int main()
{
	RenderWindow window(VideoMode(ROOM_WIDTH * CELL_WIDTH, ROOM_HEIGHT * CELL_HEIGHT), "SFML works!");

	//globalMap = generateRandomMap();
	//Room currectRoom = rooms[0];

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		/*
		std::vector<std::vector<StaticObject> > map = currectRoom.getMap();

		for (unsigned int i = 0; i < ROOM_HEIGHT; i++)
		{
			for (unsigned int j = 0; j < ROOM_WIDTH; j++)
			{
				Sprite object = currectRoom.getMap()[j][i].getSprite();

				if (object.getTexture()->getSize().x > 0 &&
					currectRoom.getMap()[j][i].getSprite().getTexture()->getSize().y > 0)
				{
					object.setPosition(float(j * CELL_WIDTH), float(i * CELL_HEIGHT));
					window.draw(object);
				}
			}
		}*/

		window.clear();
		window.display();
	} 

	return 0;
}
