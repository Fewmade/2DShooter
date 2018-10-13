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

	virtual ~GameObject()
	{}


	Vector2i GetPos() const
	{
		return pos;
	}
	void SetPos(Vector2i vec)
	{
		pos = vec;
	}

protected:
	Vector2i pos;			//Позиция объекта в пространстве
};
