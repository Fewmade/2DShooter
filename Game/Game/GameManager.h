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

	void CalculateNPC(RenderWindow& window, float time, Creature* player)
	{
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			// Аргргр не трож
			if (&enemies[i]->getRoom() == &player->getRoom())
			{
				enemies[i]->executeState(time, player);

				Sprite sp = enemies[i]->getSprite();
				Vector2f pos = enemies[i]->getPos();
				sp.setPosition(float(pos.x * CELL_WIDTH), float(pos.y * CELL_HEIGHT));
				window.draw(sp);
			}
		}
	}
	

private:
	Player* player;
	std::vector<EnemyNPC*> enemies;
};
