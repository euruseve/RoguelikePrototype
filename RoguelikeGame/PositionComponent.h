#pragma once

#include "Components.h"

class PositionComponent : public Component
{
public:
	PositionComponent() 
	{
		xPos = 0;
		yPos = 0;
	}

	PositionComponent(int x, int y)
	{
		SetPosition(x, y);
	}

	int X() { return xPos; }
	int Y() { return yPos; }

	void SetPosition(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

	void Update() override
	{
		xPos++;
		yPos++;
	}

private:
	int xPos, yPos;
};
