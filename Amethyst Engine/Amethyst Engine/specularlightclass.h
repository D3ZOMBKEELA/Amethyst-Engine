#ifndef _SPECULARLIGHTCLASS_H_
#define _SPECULARLIGHTCLASS_H_

#include <d3dx10math.h>

class SpecularLightClass
{
public:
	SpecularLightClass();
	SpecularLightClass(const SpecularLightClass&);
	~SpecularLightClass();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);

	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();
	D3DXVECTOR4 GetSpecularColor();
	float GetSpecularPower();

private:
	D3DXVECTOR4 h_ambientColor;
	D3DXVECTOR4 h_diffuseColor;
	D3DXVECTOR3 h_direction;
	D3DXVECTOR4 h_specularColor;
	float h_specularPower;
};

#endif