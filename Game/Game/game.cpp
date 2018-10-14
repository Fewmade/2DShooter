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
#include <iostream>

using namespace sf;

// Размер 1 клетки карты в пикселях
const unsigned int CELL_WIDTH  = 32;
const unsigned int CELL_HEIGHT = 32;


//Коллекция нпс в игре
//Необходимо пробегать по массиву нпс каждый кадр
//И вызывать функцию ExecuteState()
//***********************************************
//Всех нпс подгружать до начала игры
//***********************************************
std::vector<EnemyNPC> enemies;


const unsigned int numOfObjects = 2;
std::vector<StaticObject> objects(numOfObjects);

const unsigned int numOfBackgrounds = 1;
std::vector<Texture> backgrounds(numOfBackgrounds);
unsigned int correntbackground;

Image playerImage;


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

	//Player
	image.loadFromFile("../images/characters/player.png");
	playerImage = image;
}

/*
void createTestNPC()
{
	Image npcImage;
	npcImage.loadFromFile("../images/characters/soldier.png");

	std::vector<Vector2f> patrolPoints;
	patrolPoints.push_back(Vector2f(2,3));
	patrolPoints.push_back(Vector2f(2,4));
	patrolPoints.push_back(Vector2f(3,4));

	EnemyNPC npc1(Vector2f(2, 2), npcImage , patrolPoints);
	enemies.push_back(npc1);
}*/

int main()
{
	RenderWindow window(VideoMode(ROOM_WIDTH * CELL_WIDTH, ROOM_HEIGHT * CELL_HEIGHT), "SFML works!");

	globalMap = generateRandomMap();
	Room currectRoom = rooms[0];

	loadImages();
	
	correntbackground = 0;

	//Создание тестовых нпс
	//createTestNPC();

	//Игрок
	Player player(Vector2f(ROOM_WIDTH / 2, ROOM_HEIGHT / 2), playerImage);

	// Время
	Clock clock; // Считает время между кадрами

	while (window.isOpen())
	{
		// Время
		float time; //Хранит время между кадрами
		time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();

		// Обработка движений
		int playerStatus = getplayerStatus();
		float distance = time * player.getSpeed();

		player.move(playerStatus, distance);

		std::cerr << int(player.getPos().x) << " " << int(player.getPos().y) << std::endl;

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

		//Прорисовка игрока
		Sprite pl = player.getSprite();
		Vector2f pos = player.getPos();
		pl.setPosition(float(pos.x * CELL_WIDTH), float(pos.y * CELL_HEIGHT));
		window.draw(pl);

		//Тест НПС
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			//enemies[i].executeState();
		}
		///////////////////////////////////////

		window.display();
	}

	return 0;
}
