#ifndef _AMBIENTLIGHTCLASS_H_
#define _AMBIENTLIGHTCLASS_H_

#include <d3dx10math.h>

class AmbientLightClass
{
public:
	AmbientLightClass();
	AmbientLightClass(const AmbientLightClass&);
	~AmbientLightClass();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();

private:
	D3DXVECTOR4 h_ambientColor;
	D3DXVECTOR4 h_diffuseColor;
	D3DXVECTOR3 h_direction;
};

#endif