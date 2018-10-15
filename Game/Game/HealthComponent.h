#pragma once

class HealthComponent
{
public:
	HealthComponent()
	{}
	HealthComponent(int maxVal)
	{
		maxHp = maxVal;
	}
	HealthComponent(int maxVal, int curVal)
	{
		maxHp = maxVal;

		if (curVal > maxHp)					//Если заданное значение некорректно
		{
			curVal = maxHp;
		}
		else if (curVal < 0)
		{
			curVal = 0;
		}

		currentHp = curVal;
	}

	~HealthComponent()
	{}

	void TakeDamage(int val)
	{
		currentHp -= val;
		if (currentHp < 0)
		{
			currentHp = 0;
		}
	}
	void Heal(int val)
	{
		currentHp += val;
		if (currentHp > maxHp)
		{
			currentHp = maxHp;
		}
	}

	int GetCurrentHp() const
	{
		return currentHp;
	}

private:
	int currentHp;							//Текущее ХП
	int maxHp;								//Максимально возможное значение
};