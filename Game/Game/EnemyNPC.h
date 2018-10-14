#pragma once
#include "Creature.h"
#include "State.h"
#include "PatrolState.h"

class EnemyNPC : public Creature
{
public:
	EnemyNPC()
	{}
	EnemyNPC(Vector2f _pos)
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;

		//НПС входит в состояние патруллирования
		currentState = new PatrolState();
		currentState->enter();
	}
	EnemyNPC(Vector2f _pos, Image _image, std::vector<Vector2f> _patrolPoints)
	{
		image = _image;
		pos = _pos;
		pos = Vector2f(0, 0);
		id = ENEMY_BASE_NPC;

		//НПС входит в состояние патруллирования
		currentState = new PatrolState(_patrolPoints, this , 0);
		currentState->enter();

		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}
	EnemyNPC(Vector2f _pos, Image _image, State *state)
	{
		pos = _pos;
		image = _image;
		id = ENEMY_BASE_NPC;

		currentState = state;
		currentState->enter();

		//image.createMaskFromColor();
		texture.loadFromImage(image);
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
	State * currentState;								//Текущее состояние НПС
};