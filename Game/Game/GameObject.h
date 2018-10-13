#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class GameObject
{
public:

	GameObject()
	{}
	GameObject(Vector2i _pos) : pos(_pos)
	{}
	GameObject(Image _image) : image(_image)
	{
		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}
	GameObject(Vector2i _pos, Image _image) : pos(_pos), image(_image)
	{
		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}

	virtual ~GameObject()
	{}


	Vector2i getPos() const
	{
		return pos;
	}
	void setPos(Vector2i vec)
	{
		pos = vec;
	}
	
	void setImage(Image _image)
	{
		image = _image;
		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		//sprite.setScale();
	}

protected:
	Image image;
	Texture texture;
	Sprite sprite;

	Vector2i pos;			//Позиция объекта в пространстве
};
