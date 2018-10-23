#pragma once

// Размер 1 клетки комнаты в пикселях
const unsigned int CELL_WIDTH = 32;
const unsigned int CELL_HEIGHT = 32;

// Направления
const unsigned int numOfDirections = 8;

const int UP         = 0;
const int UP_RIGHT   = 1;
const int RIGHT      = 2;
const int RIGHT_DOWN = 3;
const int DOWN       = 4;
const int DOWN_LEFT  = 5;
const int LEFT       = 6;
const int LEFT_UP    = 7;

// Размер комнаты
const unsigned int ROOM_WIDTH  = 15;
const unsigned int ROOM_HEIGHT = 15;

// Состояния Creature
const int STAY = 0;
const int GO   = 1;
const int RUN  = 2;

// Количество  обьектов
const unsigned int NUMBER_OF_OBJECTS = 3;

// Номера обьектов
const unsigned int WALL  = 0;
const unsigned int STONE = 1;
const unsigned int DOOR  = 2;

// Количество задних фонов
const unsigned int NUMBER_OF_BACKGROUNDS = 1;

// ID существ
const unsigned int DEFAULT_ID     = 0;
const unsigned int ENEMY_BASE_NPC = 1;

// Стартовая комната
const int STARTING_ROOM = 0;

// Константы для НПС
const float PATH_OFFSET			= 0.1f;
const int	PATROL_STATE		= 0;
const int	SEEK_STATE			= 1;
const int	ATTACK_STATE		= 2;

//Константы для атаки
const int	ATTACK_DELAY		= 80;

// Отступ от двери при переходе в другую комнату
const float distanceFromDoor = 10.f / 32;

// Количесвто линий анимации
const unsigned int numOfAnimationLines = 10;

// Линии анимации(на stayLine анимация стояния)
const unsigned int STAY_LINE      = 0;

const unsigned int GO_UP_LINE     = 1;
const unsigned int GO_DOWN_LINE   = 2;
const unsigned int GO_RIGHT_LINE  = 3;
const unsigned int GO_LEFT_LINE   = 4;

const unsigned int RUN_UP_LINE    = 5;
const unsigned int RUN_DOWN_LINE  = 6;
const unsigned int RUN_RIGHT_LINE = 7;
const unsigned int RUN_LEFT_LINE  = 8;

const unsigned int ATACK_LINE     = 9;
