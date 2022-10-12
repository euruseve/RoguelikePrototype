#pragma once

#include "ECS.h"

class PositionComponent : public Component
{
public:
	int X() { return xPos; }
	int Y() { return yPos; }

	void SetPosition(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

	void Init() override
	{
		xPos = 0;
		yPos = 0;
	}

	void Update() override
	{
		xPos++;
		yPos++;
	}

private:
	int xPos, yPos;
};
