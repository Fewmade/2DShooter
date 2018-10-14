#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class GameObject
{
public:

	GameObject()
	{}
	GameObject(Image _image) : image(_image)
	{
		//image.createMaskFromColor();
		texture.loadFromImage(image);
	}
	
	void setImage(Image _image)
	{
		image = _image;
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

	/*void setSpriteSize(Vector2i size)
	{
		spriteSize = size;
	}
	Vector2i getSpriteSize()
	{
		return spriteSize;
	}*/

	virtual ~GameObject()
	{}

protected:
	Image image;
	Texture texture;

	bool solid;

	Vector2i spriteSize = Vector2i(32, 32);
};
