#pragma once

#include <SFML/Graphics.hpp>

class State
{
public:
	State()
	{}
	~State()
	{}

	virtual void enter()					//Enter state
	{}
	virtual void execute()					//Execute state
	{}
	virtual void exit()						//Exit from state
	{}
};
