#pragma once


class SeekState : public State
{
public:
	SeekState()
	{}
	~SeekState()
	{}

	SeekState(Creature *_owner, int id = 0)
	{
		owner = _owner;
		stateID = id;
	}

	void enter() override
	{

	}

	void execute(float time, Vector2f playerPos) 
	{
		int dir = 0;

		//Находим направление
		if (playerPos.x - owner->getPos().x >= PATH_OFFSET &&
			playerPos.y - owner->getPos().y >= PATH_OFFSET)
		{
			dir = RIGHT_DOWN;
		}
		else if (playerPos.x - owner->getPos().x <= -PATH_OFFSET &&
			playerPos.y - owner->getPos().y >= PATH_OFFSET)
		{
			dir = DOWN_LEFT;
		}
		else if (playerPos.x - owner->getPos().x >= PATH_OFFSET &&
			playerPos.y - owner->getPos().y <= -PATH_OFFSET)
		{
			dir = UP_RIGHT;
		}
		else if (playerPos.x - owner->getPos().x <= -PATH_OFFSET &&
			playerPos.y - owner->getPos().y <= -PATH_OFFSET)
		{
			dir = LEFT_UP;
		}
		else if (playerPos.x - owner->getPos().x <= -PATH_OFFSET)
		{
			dir = LEFT;
		}
		else if (playerPos.x - owner->getPos().x >= PATH_OFFSET)
		{
			dir = RIGHT;
		}
		else if (playerPos.y - owner->getPos().y >= PATH_OFFSET)
		{
			dir = DOWN;
		}
		else if (playerPos.y - owner->getPos().y <= -PATH_OFFSET)
		{
			dir = UP;
		}
		/////////////////////////////////////////////////////////

		CreatureStatus status;
		status.dir = dir;
		status.condition = GO;

		owner->move(status, time);
	}

	void exit() override
	{

	}

private:


};
