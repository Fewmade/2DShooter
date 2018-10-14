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


const unsigned int numOfObjects = 2;
std::vector<StaticObject> objects(numOfObjects);

//Коллекция нпс в игре
//Необходимо пробегать по массиву нпс каждый кадр
//И вызывать функцию ExecuteState()
//***********************************************
//Всех нпс подгружать до начала игры
//***********************************************
std::vector<EnemyNPC> enemies;

void loadImages()
{
	Image image;

	image.loadFromFile("../images/stone.png");
	objects[0] = StaticObject(image);

	image.loadFromFile("../images/empty.png");
	objects[1] = StaticObject(image);
}

int main()
{
	RenderWindow window(VideoMode(ROOM_WIDTH * CELL_WIDTH, ROOM_HEIGHT * CELL_HEIGHT), "SFML works!");

	globalMap = generateRandomMap();
	Room currectRoom = rooms[0];

	loadImages();

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		window.clear();

		//Прорисовка карты
		std::vector<std::vector<int> > map = currectRoom.getMap();
		for (unsigned int i = 0; i < ROOM_HEIGHT; i++)
		{
			for (unsigned int j = 0; j < ROOM_WIDTH; j++)
			{
				if (map[i][j] >= -1)
				{
					Sprite object = objects[map[j][i]].getSprite();

					object.setPosition(float(j * CELL_WIDTH), float(i * CELL_HEIGHT));
					window.draw(object);
				}
			}
		}
		/*
		Sprite sp = objects[0].sprite;
		sp.setPosition(15, 15);
		sp.setTextureRect(IntRect(0, 0, 32, 32));
		window.draw(sp);*/

		window.display();
	} 

	return 0;
}
