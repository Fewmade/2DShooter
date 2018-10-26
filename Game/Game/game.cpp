#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "GameManager.h"
#include "Consts.h"
#include "AllyNPC.h"
#include "Creature.h"
#include "DynamicObject.h"
#include "EnemyNPC.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Player.h"
#include "Room.h"
#include "StaticObject.h"
#include "PatrolState.h"
#include "State.h"

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

Image npcImage;
std::vector<Vector2f> patrolPoints;

GameManager gameManager;

Font basicFont;

void loadImages()
{
	Image image;
	Texture texture;
	Sprite sprite;

	// StaticObject
	image.loadFromFile("../images/objects/wall.png");
	objects[WALL]  = StaticObject(image, true, Vector2u(32, 32), IntRect(0, 0, 32, 32));

	image.loadFromFile("../images/objects/stone.png");
	objects[STONE] = StaticObject(image);

	image.loadFromFile("../images/objects/door.png");
	objects[DOOR]  = StaticObject(image);

	// Backgrounds
	image.loadFromFile("../images/backgrounds/background1.png");
	texture.loadFromImage(image);
	backgrounds[0] = texture;

	// Player
	image.loadFromFile("../images/characters/player.png");
	playerImage = image;

	// NPC
	image.loadFromFile("../images/characters/soldier.png");
	npcImage = image;

}

void otherLoads()
{
	// Загрузка шрифта
	Font font;
	font.loadFromFile("../fonts/CyrilicOld.ttf");

	basicFont = font;
}

void createTestNPC(Room *room)
{
	EnemyNPC* npc1 = new EnemyNPC(npcImage, Vector2f(ROOM_WIDTH / 2 - 4, ROOM_HEIGHT / 2 - 4), room, patrolPoints, 1, 2, true);
	npc1->setNumOfFrames(std::vector<unsigned int>(numOfAnimationLines, 1));

	// Скорость изменения кадров для кажлого состояния
	npc1->setFrameSpeed(std::vector<float>(numOfAnimationLines, 0.0015f));

	npc1->setGoSpeed(0.003f);
	npc1->setRunSpeed(0.01f);

	gameManager.AddNPC(npc1);
}


int main()
{
	RenderWindow window(VideoMode(ROOM_WIDTH * CELL_WIDTH, ROOM_HEIGHT * CELL_HEIGHT), "2D Shooter");
	window.setFramerateLimit(120);

	rooms.push_back(new Room(generateRandomRoom(true, true, true, true)));

	loadImages();
	otherLoads();

	// NPC
	patrolPoints.push_back(Vector2f(8, 3));
	patrolPoints.push_back(Vector2f(8, 4));
	patrolPoints.push_back(Vector2f(8, 5));
	patrolPoints.push_back(Vector2f(7, 5));
	patrolPoints.push_back(Vector2f(6, 2));
	
	correntbackground = 0;

	//Игрок
	Player player(playerImage, Vector2f(ROOM_WIDTH / 2, ROOM_HEIGHT / 2), rooms[STARTING_ROOM], 100, 100, true, Vector2u(32, 32), IntRect(5, 5, 22, 22));
	player.setGoSpeed(0.003f);
	player.setRunSpeed(0.007f);
	player.setAtackSize(Vector2f(1.f, 1.f));

	// Количство кадров для каждого состояния
	player.setNumOfFrames(std::vector<unsigned int>(numOfAnimationLines, 4));
	// Скорость изменения кадров для кажлого состояния
	player.setFrameSpeed(std::vector<float>(numOfAnimationLines, 0.0015f));

	// Создание тестовых нпс
	createTestNPC(rooms[STARTING_ROOM]);

	// Время
	Clock clock; // Считает время между кадрами

	//Для обработки атаки
	unsigned int frame = 0;
	unsigned int lastAttackFrame = -ATTACK_DELAY;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// Время
		float time; // Хранит время между кадрами
		time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();

		time /= 800;

		// Обработка движений и анимации
		CreatureStatus playerStatus = getPlayerStatus();
		player.move(playerStatus, time);

		//Обработка атаки
		if (playerStatus.attack && frame - lastAttackFrame >= ATTACK_DELAY)
		{
			player.attack(gameManager.getEnemies(), playerStatus);
			lastAttackFrame = frame;
		}

		unsigned int pr_roomsSize = rooms.size();

		// Update всех существ
		player.update();
		
		// Генерация существ в новой комнате
		if (pr_roomsSize != rooms.size())
		{
			srand(unsigned(std::time(NULL)) + rand());
			unsigned int numOfEnemies;

			if (MAX_NUMBER_OF_ENEMIES == MIN_NUMBER_OF_ENEMIES)
			{
				numOfEnemies = MAX_NUMBER_OF_ENEMIES;
			}
			else
			{
				numOfEnemies = rand() % (MAX_NUMBER_OF_ENEMIES - MIN_NUMBER_OF_ENEMIES) + MIN_NUMBER_OF_ENEMIES;
			}

			for (unsigned int en = 0; en < numOfEnemies; en++)
			{
				int x = -1;
				int y = -1;

				while (x < 0 || y < 0 || (player.getRoom().getCell(x, y) >= 0 && objects[player.getRoom().getCell(x, y)].getSolid()))
				{
					srand(unsigned(std::time(NULL)) + rand());
					x = rand() % (ROOM_WIDTH - 1);
					y = rand() % (ROOM_HEIGHT - 1);
				}

				EnemyNPC* npc = new EnemyNPC(npcImage, Vector2f(float(x), float(y)), &player.getRoom(), patrolPoints, 1, 2, true);
				npc->setNumOfFrames(std::vector<unsigned int>(numOfAnimationLines, 1));

				// Скорость изменения кадров для кажлого состояния
				npc->setFrameSpeed(std::vector<float>(numOfAnimationLines, 0.0015f));

				npc->setGoSpeed(0.003f);
				npc->setRunSpeed(0.01f);

				gameManager.AddNPC(npc);
			}
		}

		// Прорисовка
		std::vector<std::vector<int> > map = player.getRoom().getMap();
		
		window.clear();
		
		// Прорисовка заднего фона и карты
		Sprite background(backgrounds[0]);
		for (unsigned int i = 0; i < ROOM_HEIGHT; i++)
		{
			for (unsigned int j = 0; j < ROOM_WIDTH; j++)
			{
				// Прорисовка заднего фона
				background.setPosition(float(j * CELL_WIDTH), float(i * CELL_HEIGHT));
				window.draw(background);

				// Прорисовка карты
				if (map[i][j] >= 0)
				{
					Sprite object = objects[map[i][j]].getSprite();

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
		gameManager.CalculateNPC(window, time, &player);
		///////////////////////////////////////

		// Прорисовка здоровья
		String HPString;
		HPString = "Здоровье: " + String(std::to_string(player.getHP()));
		Text HPText(HPString, basicFont, 20);
		HPText.setFillColor(Color::Red);
		HPText.setStyle(Text::Bold);
		HPText.setPosition(0, 0);
		window.draw(HPText);

		window.display();

		++frame;
	}

	return 0;
}
