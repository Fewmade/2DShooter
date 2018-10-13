#pragma once
#include "Creature.h"
#include "State.h"

class EnemyNPC : public Creature
{
public:
	EnemyNPC()
	{}
	EnemyNPC(Vector2i _pos)
	{
		pos = _pos;

		//currentState = new PatrolState();
		//currentState->Enter();
	}
	EnemyNPC(Image _image)
	{
		image = _image;
		pos = Vector2i(0, 0);

		//currentState = new PatrolState();
		//currentState->Enter();

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}
	EnemyNPC(Vector2i _pos, Image _image, State *state)
	{
		pos = _pos;
		image = _image;

		currentState = state;
		currentState->Execute();

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}

	virtual ~EnemyNPC()
	{}

protected:
	State * currentState;								//Current npc state
};