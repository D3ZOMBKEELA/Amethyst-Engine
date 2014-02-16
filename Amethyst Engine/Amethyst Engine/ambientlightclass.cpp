#include "ambientlightclass.h"

AmbientLightClass::AmbientLightClass()
{
}

AmbientLightClass::AmbientLightClass(const AmbientLightClass& other)
{
}

AmbientLightClass::~AmbientLightClass()
{
}

void AmbientLightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	h_ambientColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void AmbientLightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	h_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void AmbientLightClass::SetDirection(float x, float y, float z)
{
	h_direction = D3DXVECTOR3(x, y, z);
	return;
}

D3DXVECTOR4 AmbientLightClass::GetAmbientColor()
{
	return h_ambientColor;
}

D3DXVECTOR4 AmbientLightClass::GetDiffuseColor()
{
	return h_diffuseColor;
}

D3DXVECTOR3 AmbientLightClass::GetDirection()
{
	return h_direction;
}