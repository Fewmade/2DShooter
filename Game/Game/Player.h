#pragma once
#include "Creature.h"


class Player : public Creature
{
public:
	
	Player(Vector2i _pos)
	{
		pos = _pos;
	}
	Player(Image _image)
	{
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}
	Player(Vector2i _pos, Image _image)
	{
		pos = _pos;
		image = _image;

		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}

	~Player()
	{}



private:
	
};
