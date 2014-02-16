#include "diffuselightclass.h"

DiffuseLightClass::DiffuseLightClass()
{
}

DiffuseLightClass::DiffuseLightClass(const DiffuseLightClass& other)
{
}

DiffuseLightClass::~DiffuseLightClass()
{
}

void DiffuseLightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	h_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void DiffuseLightClass::SetDirection(float x, float y, float z)
{
	h_direction = D3DXVECTOR3(x, y, z);
	return;
}

D3DXVECTOR4 DiffuseLightClass::GetDiffuseColor()
{
	return h_diffuseColor;
}

D3DXVECTOR3 DiffuseLightClass::GetDirection()
{
	return h_direction;
}