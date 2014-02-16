#include "specularlightclass.h"

SpecularLightClass::SpecularLightClass()
{
}

SpecularLightClass::SpecularLightClass(const SpecularLightClass& other)
{
}

SpecularLightClass::~SpecularLightClass()
{
}

void SpecularLightClass::SetAmbientColor(float red, float green, float blue, float alpha)
{
	h_ambientColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void SpecularLightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	h_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void SpecularLightClass::SetDirection(float x, float y, float z)
{
	h_direction = D3DXVECTOR3(x, y, z);
	return;
}

void SpecularLightClass::SetSpecularColor(float red, float green, float blue, float alpha)
{
	h_specularColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}

void SpecularLightClass::SetSpecularPower(float power)
{
	h_specularPower = power;
	return;
}

D3DXVECTOR4 SpecularLightClass::GetAmbientColor()
{
	return h_ambientColor;
}

D3DXVECTOR4 SpecularLightClass::GetDiffuseColor()
{
	return h_diffuseColor;
}

D3DXVECTOR3 SpecularLightClass::GetDirection()
{
	return h_direction;
}

D3DXVECTOR4 SpecularLightClass::GetSpecularColor()
{
	return h_specularColor;
}

float SpecularLightClass::GetSpecularPower()
{
	return h_specularPower;
}