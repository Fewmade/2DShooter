#pragma once

#include <SFML/Graphics.hpp>


class State
{
public:
	State()
	{}
	~State()
	{}

	virtual void Enter()					//Enter state
	{}
	virtual void Execute()					//Execute state
	{}
	virtual void Exit()						//Exit from state
	{}
};
