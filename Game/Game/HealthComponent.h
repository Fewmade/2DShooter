#pragma once

class HealthComponent
{
public:
	HealthComponent()
	{}
	HealthComponent(int maxVal)
	{
		maxHP = maxVal;
		currentHP = maxVal;
	}
	HealthComponent(int maxVal, int curVal)
	{
		maxHP = maxVal;
		setHP(curVal);
	}

	~HealthComponent()
	{}

	void changeHP(int HPDif)
	{
		currentHP += HPDif;

		//Если заданное значение некорректно
		if (currentHP < 0)
		{
			currentHP = 0;
		}
		if (currentHP > maxHP)
		{
			currentHP = maxHP;
		}
	}

	void setHP(unsigned int _HP)
	{
		currentHP = _HP;

		//Если заданное значение некорректно
		if (currentHP < 0)
		{
			currentHP = 0;
		}
		if (currentHP > maxHP)
		{
			currentHP = maxHP;
		}
	}
	void setMaxHP(unsigned int _maxHP)
	{
		maxHP = _maxHP;
	}

	int getHP() const
	{
		return currentHP;
	}
	int getMaxHP() const
	{
		return maxHP;
	}

private:
	int currentHP;							//Текущее ХП
	int maxHP;								//Максимально возможное значение
};