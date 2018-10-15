#pragma once
#include "Creature.h"
#include "State.h"
#include "PatrolState.h"

class EnemyNPC : public Creature
{
public:
	EnemyNPC()
	{}
	EnemyNPC(Image _image, Vector2f _pos, bool _solid = false, Vector2i _spriteSize = Vector2i(32, 32))
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;

		//��� ������ � ��������� ���������������
		currentState = new PatrolState();
		currentState->enter();

		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
		spriteSize = _spriteSize;
	}
	EnemyNPC(Image _image, Vector2f _pos, std::vector<Vector2f> _patrolPoints, bool _solid = false, Vector2i _spriteSize = Vector2i(32, 32))
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;

		//��� ������ � ��������� ���������������
		currentState = new PatrolState(_patrolPoints, this, 0);
		currentState->enter();

		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
		spriteSize = _spriteSize;
	}
	EnemyNPC(Image _image, Vector2f _pos, State *state, bool _solid = false, Vector2i _spriteSize = Vector2i(32, 32))
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;

		currentState = state;
		currentState->enter();

		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
		spriteSize = _spriteSize;
	}

	virtual ~EnemyNPC()
	{}


	virtual void executeState() const
	{
		//If player in seek radius and player not in seek state
			//Change to seek state
		//If player in attack radius and player not in attack state
			//Change to attack state
		//Else if player too far and player not in patrol state
			//Change to patrol state

		currentState->execute();
	}

protected:
	State * currentState;								//������� ��������� ���
};