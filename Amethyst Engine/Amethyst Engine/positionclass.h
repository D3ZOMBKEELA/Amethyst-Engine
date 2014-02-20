#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_

#include <math.h>

class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetFrameTime(float);
	void GetRotation(float&);

	void TurnLeft(bool);
	void TurnRight(bool);

private:
	float h_frameTime;
	float h_rotationY;
	float h_leftTurnSpeed, h_rightTurnSpeed;
};

#endif