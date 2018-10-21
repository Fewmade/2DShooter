#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class GameObject
{
public:
	GameObject()
	{}
	GameObject(Image _image, bool _solid = false, Vector2u _spriteSize = Vector2u(32, 32), IntRect _collisionRect = IntRect(0, 0, 32, 32)) : 
		image(_image), spriteSize(_spriteSize), collisionRect(_collisionRect), solid(_solid)
	{
		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}
	
	Sprite getSprite()
	{
		Sprite sprite;
		sprite.setTexture(texture);
		return sprite;
	}
	
	void setSolid(bool _solid)
	{
		solid = _solid;
	}
	bool getSolid()
	{
		return solid;
	}

	void setCollisionRect(IntRect size)
	{
		collisionRect = size;
	}
	IntRect getCollisionRect()
	{
		return collisionRect;
	}

	virtual ~GameObject()
	{}

protected:
	Image image;
	Texture texture;

	bool solid;  // Твёрдый ли обьект

	IntRect collisionRect; // Физическая модель
	Vector2u spriteSize;
};
