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
		sprite.setTexture(texture);
		//sprite.setScale();
	}

	virtual ~GameObject()
	{}
	
	void setImage(Image _image)
	{
		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}
	Sprite getSprite()
	{
		return sprite;
	}
protected:
	Image image;
	Texture texture;
	Sprite sprite;
};
