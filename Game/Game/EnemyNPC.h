#pragma once
#include "Creature.h"

class EnemyNPC : public Creature
{
public:
	EnemyNPC()
	{}
	EnemyNPC(Vector2i _pos)
	{
		pos = _pos;
	}
	EnemyNPC(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}
	EnemyNPC(Vector2i _pos, Image _image)
	{
		pos = _pos;
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}

	virtual ~EnemyNPC()
	{}

protected:

};