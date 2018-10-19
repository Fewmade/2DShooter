#pragma once

// ������ 1 ������ ������� � ��������
const unsigned int CELL_WIDTH = 32;
const unsigned int CELL_HEIGHT = 32;

// �����������
const int UP         = 1;
const int UP_RIGHT   = 2;
const int RIGHT      = 3;
const int RIGHT_DOWN = 4;
const int DOWN       = 5;
const int DOWN_LEFT  = 6;
const int LEFT       = 7;
const int LEFT_UP    = 8;

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

//��������� ��� ���
const float PATH_OFFSET = 0.1f;
const int	PATROL_STATE = 0;
const int	SEEK_STATE	 = 1;



