#pragma once

// ������ 1 ������ ������� � ��������
const unsigned int CELL_WIDTH = 32;
const unsigned int CELL_HEIGHT = 32;

// �����������
const unsigned int numOfDirections = 8;

const int UP         = 0;
const int UP_RIGHT   = 1;
const int RIGHT      = 2;
const int RIGHT_DOWN = 3;
const int DOWN       = 4;
const int DOWN_LEFT  = 5;
const int LEFT       = 6;
const int LEFT_UP    = 7;

// ������ �������
const unsigned int ROOM_WIDTH  = 15;
const unsigned int ROOM_HEIGHT = 15;

// ��������� Player
const int STAY = 0;
const int GO   = 1;
const int RUN  = 2;

// ����������  ��������
const unsigned int NUMBER_OF_OBJECTS = 3;

// ������ ��������
const unsigned int WALL  = 0;
const unsigned int STONE = 1;
const unsigned int DOOR  = 2;

// ���������� ������ �����
const unsigned int NUMBER_OF_BACKGROUNDS = 1;

// ID �������
const unsigned int DEFAULT_ID     = 0;
const unsigned int ENEMY_BASE_NPC = 1;

// ��������� �������
const int STARTING_ROOM = 0;

// ��������� ��� ���
const float PATH_OFFSET = 0.1f;

// ������������ ���������� ����������� ������
const unsigned int maxNumberOfRooms = 10;

// ������ �� ����� ��� �������� � ������ �������(� ��������)
const int distanceFromDoor = 10;
