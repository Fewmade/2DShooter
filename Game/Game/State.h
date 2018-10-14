#pragma once

<<<<<<< HEAD
#include <SFML/Graphics.hpp>


=======
>>>>>>> 81374341bdbfeb193f9ab47cf6df60d2b9ed9a5d
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
