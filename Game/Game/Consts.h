#pragma once

// Размер 1 клетки комнаты в пикселях
const unsigned int CELL_WIDTH = 32;
const unsigned int CELL_HEIGHT = 32;

// Направления движения Creature
const int UP = 1;
const int UP_RIGHT = 2;
const int RIGHT = 3;
const int RIGHT_DOWN = 4;
const int DOWN = 5;
const int DOWN_LEFT = 6;
const int LEFT = 7;
const int LEFT_UP = 8;

// Размер глобальной карты
const unsigned int MAP_WIDTH = 11;
const unsigned int MAP_HEIGHT = 11;

// Размер комнаты
const unsigned int ROOM_WIDTH = 16;
const unsigned int ROOM_HEIGHT = 16;

// Состояния Player
const int STAY = 0;
const int GO = 1;
const int RUN = 2;

// id StaticObjects
const unsigned int WALL = 0;
const unsigned int STONE = 1;

// Количество  обьектов
const unsigned int numOfObjects = 2;

// Количество задних фонов
const unsigned int numOfBackgrounds = 1;