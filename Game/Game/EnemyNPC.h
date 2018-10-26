#pragma once
#include "Creature.h"
#include "PatrolState.h"
#include "SeekState.h"
#include "AttackState.h"

class EnemyNPC : public Creature
{
public:
	EnemyNPC()
	{}
	EnemyNPC(Image _image, Vector2f _pos, Room *_room, bool _solid = false, Vector2u _spriteSize = Vector2u(32, 32), IntRect _collisionRect = IntRect(0, 0, 32, 32), int _damage = 30)
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;
		room = _room;
		patrolPoints = std::vector<Vector2f>();
		attackRadius = 2;
		seekRadius = 4;

		//НПС входит в состояние патруллирования
		currentState = new PatrolState(patrolPoints ,this, 0);
		currentState->enter();

		healthComp = new HealthComponent(100, 100);

		image = _image;
		texture.loadFromImage(image);

		solid = _solid;
		collisionRect = _collisionRect;
		spriteSize = _spriteSize;
	}
	EnemyNPC(Image _image, Vector2f _pos, Room *_room, std::vector<Vector2f> _patrolPoints, float _attackRadius, float _seekRadius, bool _solid = false, Vector2u _spriteSize = Vector2u(32, 32), IntRect _collisionRect = IntRect(0, 0, 32, 32), int _damage = 30)
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;
		room = _room;
		patrolPoints = _patrolPoints;
		attackRadius = _attackRadius;
		seekRadius = _seekRadius;
		damage = _damage;

		//НПС входит в состояние патруллирования
		currentState = new PatrolState(patrolPoints, this, 0);
		currentState->enter();

		healthComp = new HealthComponent(100, 100);

		image = _image;
		texture.loadFromImage(image);

		solid = _solid;
		collisionRect = _collisionRect;
		spriteSize = _spriteSize;
	}
	EnemyNPC(Image _image, Vector2f _pos, State *state, Room *_room, bool _solid = false, Vector2u _spriteSize = Vector2u(32, 32), IntRect _collisionRect = IntRect(0, 0, 32, 32))
	{
		pos = _pos;
		id = ENEMY_BASE_NPC;
		room = _room;

		currentState = state;
		currentState->enter();

		healthComp = new HealthComponent(100, 100);

		image = _image;
		
		texture.loadFromImage(image);

		solid = _solid;
		collisionRect = _collisionRect;
		spriteSize = _spriteSize;
	}

	int getStateID() const
	{
		return currentState->getStateID();
	}
	

	virtual ~EnemyNPC()
	{}


	int executeState(float time, Creature* player)
	{
		if (healthComp->getHP() > 0)
		{
			Vector2f vDist = player->getPos() - pos;
			float dist = sqrt(vDist.x * vDist.x + vDist.y * vDist.y);

			if (dist <= attackRadius && currentState->getStateID() != ATTACK_STATE)
			{
				delete currentState;
				currentState = new AttackState(this);
			}
			else if (dist <= seekRadius && dist > attackRadius && currentState->getStateID() != SEEK_STATE)
			{
				delete currentState;
				currentState = new SeekState(this);
			}
			else if (dist > seekRadius && currentState->getStateID() != PATROL_STATE)
			{
				delete currentState;
				currentState = new PatrolState(patrolPoints, this, 0);
			}

			currentState->execute(time, player);
			return SUCCESS;
		}
		else
		{
			return DESTROYED;

		}
		
	}
	

protected:
	State * currentState;								//Текущее состояние НПС
	std::vector<Vector2f> patrolPoints;

	float	seekRadius;
	float	attackRadius;
};