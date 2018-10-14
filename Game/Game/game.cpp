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
#include "PatrolState.h"
#include "State.h"

using namespace sf;

// Размер 1 клетки карты в пикселях
const unsigned int CELL_WIDTH  = 32;
const unsigned int CELL_HEIGHT = 32;


const unsigned int numOfObjects = 2;
std::vector<StaticObject> objects(numOfObjects);

const unsigned int numOfBackgrounds = 1;
std::vector<Texture> backgrounds(numOfBackgrounds);
unsigned int correntbackground;

void loadImages()
{
	Image image;
	Texture texture;
	Sprite sprite;

	//StaticObject
	image.loadFromFile("../images/objects/wall.png");
	objects[0] = StaticObject(image);

	image.loadFromFile("../images/objects/stone.png");
	objects[1] = StaticObject(image);

	//Backgrounds
	image.loadFromFile("../images/backgrounds/background1.png");
	texture.loadFromImage(image);
	backgrounds[0] = texture;
}

int main()
{
	RenderWindow window(VideoMode(ROOM_WIDTH * CELL_WIDTH, ROOM_HEIGHT * CELL_HEIGHT), "SFML works!");

	globalMap = generateRandomMap();
	Room currectRoom = rooms[0];

	loadImages();
	
	correntbackground = 0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		std::vector<std::vector<int> > map = currectRoom.getMap();
		
		window.clear();

		//Прорисовка заднего фона
		for (unsigned int i = 0; i < ROOM_HEIGHT; i++)
		{
			for (unsigned int j = 0; j < ROOM_WIDTH; j++)
			{
				Sprite background(backgrounds[correntbackground]);
				background.setPosition(float(j * CELL_WIDTH), float(i * CELL_HEIGHT));
				window.draw(background);
			}
		}

		//Прорисовка карты
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

		window.display();
	}

	return 0;
}
