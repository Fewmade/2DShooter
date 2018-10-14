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

		//НПС входит в состояние патруллирования
		currentState = new PatrolState();
		currentState->Enter();
	}
	EnemyNPC(Image _image)
	{
		image = _image;
		pos = Vector2f(0, 0);

		//НПС входит в состояние патруллирования
		currentState = new PatrolState();
		currentState->Enter();

		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}
	EnemyNPC(Vector2f _pos, Image _image, State *state)
	{
		pos = _pos;
		image = _image;

		currentState = state;
		currentState->Enter();

		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}

	virtual ~EnemyNPC()
	{}


	virtual void ExecuteState() const
	{
		//If player in seek radius and player not in seek state
			//Change to seek state
		//If player in attack radius and player not in attack state
			//Change to attack state
		//Else if player too far and player not in patrol state
			//Change to patrol state

		currentState->Execute();
	}

protected:
	State * currentState;								//Текущее состояние НПС
};