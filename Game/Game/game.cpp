#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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

Font basicFont;

void loadImages()
{
	Image image;
	Texture texture;
	Sprite sprite;

	//StaticObject
	image.loadFromFile("../images/objects/wall.png");
	objects[WALL]  = StaticObject(image, true, Vector2u(32, 32), IntRect(0, 0, 32, 32));

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

void otherLoads()
{
	// Загрузка шрифта
	Font font;
	font.loadFromFile("../fonts/CyrilicOld.ttf");

	basicFont = font;
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
}
*/

int main()
{
	RenderWindow window(VideoMode(ROOM_WIDTH * CELL_WIDTH, ROOM_HEIGHT * CELL_HEIGHT), "2D Shooter");
	window.setFramerateLimit(120);

	rooms.push_back(generateRandomRoom(true, true, true, true));

	loadImages();
	otherLoads();
	
	correntbackground = 0;

	//Игрок
	Player player(playerImage, Vector2f(ROOM_WIDTH / 2, ROOM_HEIGHT / 2), &rooms[STARTING_ROOM], 100, 100, true, Vector2u(32, 32), IntRect(5, 5, 22, 22));
	player.setGoSpeed(0.003f);
	player.setRunSpeed(0.007f);

	// Количство кадров для каждого состояния
	player.setNumOfFrames(std::vector<unsigned int>(numOfAnimationLines, 4));
	// Скорость изменения кадров для кажлого состояния
	player.setFrameSpeed(std::vector<float>(numOfAnimationLines, 0.0015f));

	// Создание тестовых нпс
	//createTestNPC(rooms[STARTING_ROOM]);

	// Время
	Clock clock; // Считает время между кадрами

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

		//std::cerr << time << "\n";

		// Просчет нпс
		//GameManager::Instance().CalculateNPC(window, time);
		///////////////////////////////////////

		// Обработка движений и анимации
		CreatureStatus playerStatus = getPlayerStatus();
		player.move(playerStatus, time);

		// Update всех существ
		player.update();

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

		// Прорисовка здоровья
		String HPString;
		HPString = "Здоровье: " + String(std::to_string(player.getHP()));
		Text HPText(HPString, basicFont, 20);
		HPText.setFillColor(Color::Red);
		HPText.setStyle(Text::Bold);
		HPText.setPosition(0, 0);
		window.draw(HPText);

		window.display();
	}

	return 0;
}
