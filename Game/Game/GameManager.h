#pragma once

/*
#include "Consts.h"
#include "Player.h"
#include "EnemyNPC.h"



class GameManager
{
public:
	static GameManager& Instance()
	{
		static GameManager s;
		return s;
	}

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
	void RemoveNPC(EnemyNPC* npc)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i] == npc)
			{
				EnemyNPC* tmp = enemies.back();
				enemies[enemies.size() - 1] = enemies[i];
				enemies[i] = tmp;
				enemies.pop_back();
				break;
			}
		}
	}
	void CalculateNPC(RenderWindow& window, float time)
	{
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->executeState(time);

			Sprite sp = enemies[i]->getSprite();
			Vector2f pos = enemies[i]->getPos();
			sp.setPosition(float(pos.x * CELL_WIDTH), float(pos.y * CELL_HEIGHT));
			window.draw(sp);
		}
	}
	


	GameManager(GameManager const&) = delete;
	GameManager& operator = (GameManager const&) = delete;

private:
	GameManager() { player = nullptr; }
	~GameManager() {}

	Player* player;
	std::vector<EnemyNPC*> enemies;
};
*/