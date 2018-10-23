#pragma once

#include "Consts.h"
#include <vector>

struct CreatureStatus
{
	int		condition; // go, run, stay
	int		dir;       // up, down, right, left etc.
	bool	attack;
};

bool operator== (CreatureStatus a, CreatureStatus b)
{
	return (a.condition == b.condition &&
		a.dir == b.dir);
}

class AnimationComponent
{
public:
	AnimationComponent()
	{
		numOfFrames.resize(numOfAnimationLines);
		 frameSpeed.resize(numOfAnimationLines);

		currentFrame = 0;
	}
	AnimationComponent(std::vector<unsigned int> _numOfFrames, std::vector<float> _frameSpeed): numOfFrames(_numOfFrames), frameSpeed(_frameSpeed)
	{
		numOfFrames.resize(numOfAnimationLines);
		 frameSpeed.resize(numOfAnimationLines);

		currentFrame = 0;
	}

	std::vector<unsigned int> getNumOfFrames()
	{
		return numOfFrames;
	}
	std::vector<float> getFrameSpeed()
	{
		return frameSpeed;
	}

	void setNumOfFrames(std::vector<unsigned int> _numOfFrames)
	{
		numOfFrames = _numOfFrames;
		
	}
	void setFrameSpeed(std::vector<float> _frameSpeed)
	{
		frameSpeed = _frameSpeed;
	}

	// ������������ ����� ����������� � ����
	void updateFrame(CreatureStatus _status, float time)
	{
		// ���� ������� ����� ��������
		unsigned int _animationLine = 0;
		if (_status.condition == STAY)
		{
			_animationLine = STAY_LINE;
		}
		else if (_status.condition == GO)
		{
			switch (_status.dir)
			{
			case UP:    _animationLine = GO_UP_LINE;
				break;
			case RIGHT: _animationLine = GO_RIGHT_LINE;
				break;
			case DOWN:  _animationLine = GO_DOWN_LINE;
				break;
			case LEFT:  _animationLine = GO_LEFT_LINE;
				break;
			}
		}
		else if (_status.condition == RUN)
		{
			switch (_status.dir)
			{
			case UP:    _animationLine = RUN_UP_LINE;
				break;
			case RIGHT: _animationLine = RUN_RIGHT_LINE;
				break;
			case DOWN:  _animationLine = RUN_DOWN_LINE;
				break;
			case LEFT:  _animationLine = RUN_LEFT_LINE;
				break;
			}
		}

		// ���� ����� ������ ����� ��������, �� �������� ������������, ���� ���, �� ���������� ������
		if (status == _status)
		{
			currentFrame += frameSpeed[_animationLine] * time;

			// ���� ������� ���� ������ ������������� ��������� ������ ��� ������ ����� ��������, �� �������� ���������� ������
			if (unsigned(currentFrame) >= numOfFrames[_animationLine])
			{
				currentFrame = 0;
			}
		}
		else
		{
			currentFrame = 0;
		}

		status = _status;
		animationLine = _animationLine;
	}

	Vector2u getFrame()
	{
		return Vector2u(unsigned(currentFrame), animationLine);
	}

private:
	// ���������� ������ ��� ������� ���������
	std::vector<unsigned int> numOfFrames;
	// �������� ��������� ������ ��� ������� ���������
	std::vector<float> frameSpeed;

	// ������� ����
	float currentFrame;
	// ������� ����� ���������
	unsigned int animationLine;

	// ������ ��������
	CreatureStatus status;
};