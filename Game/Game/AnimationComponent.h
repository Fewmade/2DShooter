#pragma once

#include "Consts.h"
#include <vector>

class AnimationComponent
{
public:
	AnimationComponent()
	{
		numOfFrames.resize(numOfAnimationLines);
		 frameSpeed.resize(numOfAnimationLines);
	}
	AnimationComponent(std::vector<unsigned int> _numOfFrames, std::vector<float> _frameSpeed): numOfFrames(_numOfFrames), frameSpeed(_frameSpeed)
	{ }

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
private:
	std::vector<unsigned int> numOfFrames;
	std::vector<float> frameSpeed;
};