#include "positionclass.h"

PositionClass::PositionClass()
{
	h_frameTime = 0.0F;
	h_rotationY = 0.0F;
	h_leftTurnSpeed = 0.0F;
	h_rightTurnSpeed = 0.0F;
}

PositionClass::PositionClass(const PositionClass& other)
{
}

PositionClass::~PositionClass()
{
}

void PositionClass::SetFrameTime(float time)
{
	h_frameTime = time;
	return;
}

void PositionClass::GetRotation(float& y)
{
	y = h_rotationY;
	return;
}

void PositionClass::TurnLeft(bool keydown)
{
	if(keydown)
	{
		h_leftTurnSpeed += h_frameTime * 0.01F;

		if(h_leftTurnSpeed > (h_frameTime * 0.15F))
		{
			h_leftTurnSpeed = h_frameTime * 0.15F;
		}
	}
	else
	{
		h_leftTurnSpeed -= h_frameTime * 0.005F;

		if(h_leftTurnSpeed < 0.0F)
		{
			h_leftTurnSpeed = 0.0F;
		}
	}

	h_rotationY -= h_leftTurnSpeed;
	if(h_rotationY < 0.0F)
	{
		h_rotationY += 360.0F;
	}

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	if(keydown)
	{
		h_rightTurnSpeed += h_frameTime * 0.01F;

		if(h_rightTurnSpeed > (h_frameTime * 0.15F))
		{
			h_rightTurnSpeed = h_frameTime * 0.15F;
		}
	}
	else
	{
		h_rightTurnSpeed -= h_frameTime * 0.005F;

		if(h_rightTurnSpeed < 0.0F)
		{
			h_rightTurnSpeed = 0.0F;
		}
	}

	h_rotationY += h_rightTurnSpeed;
	if(h_rotationY > 360.0F)
	{
		h_rotationY -= 360.0F;
	}

	return;
}