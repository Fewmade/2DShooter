#include <SFML/Graphics.hpp>

#include "Consts.h"
#include "AllyNPC.h"
#include "Creature.h"
#include "DynamicObject.h"
//#include "GameManager.h"
#include "EnemyNPC.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Player.h"
#include "Room.h"
#include "StaticObject.h"
#include "PatrolState.h"
#include "State.h"
#include <iostream>

using namespace sf;

//Необходимо пробегать по массиву нпс каждый кадр
//И вызывать функцию ExecuteState()
//***********************************************
//Всех нпс подгружать до начала игры
//***********************************************


// Задний фон
std::vector<Texture> backgrounds(NUMBER_OF_BACKGROUNDS);
unsigned int correntbackground;

Image playerImage;

void loadImages()
{
	Image image;
	Texture texture;
	Sprite sprite;

	//StaticObject
	image.loadFromFile("../images/objects/wall.png");
	objects[WALL]  = StaticObject(image, true);

	image.loadFromFile("../images/objects/stone.png");
	objects[STONE] = StaticObject(image);

	image.loadFromFile("../images/objects/door.png");
	objects[DOOR]  = StaticObject(image);

	//Backgrounds
	image.loadFromFile("../images/backgrounds/background1.png");
	texture.loadFromImage(image);
	backgrounds[0] = texture;

	//Player
	image.loadFromFile("../images/characters/player.png");
	playerImage = image;
}

/*
void createTestNPC(Room &room)
{
	Image npcImage;
	npcImage.loadFromFile("../images/characters/soldier.png");

	std::vector<Vector2f> patrolPoints;
	patrolPoints.push_back(Vector2f(8,3));
	patrolPoints.push_back(Vector2f(8,4));
	patrolPoints.push_back(Vector2f(8,5));
	patrolPoints.push_back(Vector2f(7,5));
	patrolPoints.push_back(Vector2f(6,2));

	EnemyNPC* npc1 = new EnemyNPC(npcImage, Vector2f(ROOM_WIDTH / 2, ROOM_HEIGHT / 2), &room, patrolPoints, true);
	npc1->setSpeed(0.000003f);
	GameManager::Instance().AddNPC(npc1);
}
*/

int main()
{
	RenderWindow window(VideoMode(ROOM_WIDTH * CELL_WIDTH, ROOM_HEIGHT * CELL_HEIGHT), "2D Shooter");
	window.setFramerateLimit(120);

	rooms.push_back(generateRandomRoom(true, true, true, true));
	loadImages();
	
	correntbackground = 0;

	//Игрок
	Player player(playerImage, Vector2f(ROOM_WIDTH / 2, ROOM_HEIGHT / 2), &rooms[STARTING_ROOM], 100, 100, true, IntRect(8, 2, 16, 59));
	player.setSpeed(0.000003f);
	//GameManager::Instance().setPlayer(&player);

	//Создание тестовых нпс
	//createTestNPC(rooms[STARTING_ROOM]);

	// Время
	Clock clock; // Считает время между кадрами

	while (window.isOpen())
	{
		// Время
		float time; // Хранит время между кадрами
		time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();

		// Обработка движений
		PlayerStatus playerStatus = getPlayerStatus();
		float distance = time * player.getSpeed();

		if (playerStatus.condition != STAY)
		{
			if (playerStatus.condition == GO)
			{
				player.setSpeed(0.000003f);
			}
			else if (playerStatus.condition == RUN)
			{
				player.setSpeed(0.000007f);
			}

			player.move(player.getRoom(), playerStatus.dir, distance);
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		std::vector<std::vector<int> > map = player.getRoom().getMap();
		
		window.clear();

		// Прорисовка заднего фона
		for (unsigned int i = 0; i < ROOM_HEIGHT; i++)
		{
			for (unsigned int j = 0; j < ROOM_WIDTH; j++)
			{
				Sprite background(backgrounds[correntbackground]);
				background.setPosition(float(j * CELL_WIDTH), float(i * CELL_HEIGHT));
				window.draw(background);
			}
		}

		// Прорисовка карты
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

		// Прорисовка игрока
		Sprite pl = player.getSprite();
		Vector2f pos = player.getPos();
		pl.setPosition(float(pos.x * CELL_WIDTH), float(pos.y * CELL_HEIGHT));
		window.draw(pl);

		// Просчет нпс
		//GameManager::Instance().CalculateNPC(window, time);
		///////////////////////////////////////

		window.display();
	}

	return 0;
}
