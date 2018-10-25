#pragma once


#include "Consts.h"
#include "Player.h"
#include "EnemyNPC.h"



class GameManager
{
public:
	GameManager() { player = nullptr; }
	~GameManager() {}

	
	void setPlayer(Player* _player)
	{
		player = _player;
	}
	Player& getPlayer() const
	{
		return *player;
	}
	

	
	void AddNPC(EnemyNPC* npc)
	{
		enemies.push_back(npc);
	}

	int deleteNPC(int index)
	{
		if (index >= enemies.size())
		{
			return ERROR_BADALLOC;
		}

		EnemyNPC* tmp = enemies.back();
		enemies[enemies.size() - 1] = enemies[index];
		enemies[index] = tmp;

		enemies.pop_back();
		return SUCCESS;
	}

	void CalculateNPC(RenderWindow& window, float time, Creature* player)
	{
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			// Аргргр не трож
			if (&enemies[i]->getRoom() == &player->getRoom())
			{
				if (enemies[i]->executeState(time, player) == SUCCESS)
				{
					Sprite sp = enemies[i]->getSprite();
					Vector2f pos = enemies[i]->getPos();
					sp.setPosition(float(pos.x * CELL_WIDTH), float(pos.y * CELL_HEIGHT));
					window.draw(sp);
				}
				else
				{
					deleteNPC(i);
				}
			}
		}
	}

	std::vector<EnemyNPC*>& getEnemies()
	{
		return enemies;
	}
	

private:
	Player* player;
	std::vector<EnemyNPC*> enemies;
};
