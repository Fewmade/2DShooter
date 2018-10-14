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

	virtual ~GameObject()
	{}
	
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
protected:
	Image image;
	Texture texture;
};
