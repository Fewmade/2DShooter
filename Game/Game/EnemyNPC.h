#pragma once
#include "Creature.h"
#include "State.h"
#include "PatrolState.h"

class EnemyNPC : public Creature
{
public:
	EnemyNPC()
	{}
	EnemyNPC(Image _image, Vector2f _pos, Room *_room, bool _solid = false, IntRect _collisionRect = IntRect(0, 0, 32, 32))
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;
		room = _room;

		//НПС входит в состояние патруллирования
		currentState = new PatrolState(std::vector<Vector2f>() ,this, 0);
		currentState->enter();

		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
		collisionRect = _collisionRect;
	}
	EnemyNPC(Image _image, Vector2f _pos, Room *_room, std::vector<Vector2f> _patrolPoints, bool _solid = false, IntRect _collisionRect = IntRect(0, 0, 32, 32))
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;
		room = _room;

		//НПС входит в состояние патруллирования
		currentState = new PatrolState(_patrolPoints, this, 0);
		currentState->enter();

		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
		collisionRect = _collisionRect;
	}
	EnemyNPC(Image _image, Vector2f _pos, State *state, Room *_room, bool _solid = false, IntRect _collisionRect = IntRect(0, 0, 32, 32))
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;
		room = _room;

		currentState = state;
		currentState->enter();

		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);

		solid = _solid;
		collisionRect = _collisionRect;
	}

	virtual ~EnemyNPC()
	{}


	virtual void executeState(float time) const
	{
		//If player in seek radius and player not in seek state
			//Change to seek state
		//If player in attack radius and player not in attack state
			//Change to attack state
		//Else if player too far and player not in patrol state
			//Change to patrol state

		currentState->execute(time);
	}

protected:
	State * currentState;								//Текущее состояние НПС
};