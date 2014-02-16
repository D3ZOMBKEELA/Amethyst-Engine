#ifndef _DIFFUSELIGHTCLASS_H_
#define _DIFFUSELIGHTCLASS_H_

#include <d3dx10math.h>

class DiffuseLightClass
{
public:
	DiffuseLightClass();
	DiffuseLightClass(const DiffuseLightClass&);
	~DiffuseLightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();

private:
	D3DXVECTOR4 h_diffuseColor;
	D3DXVECTOR3 h_direction;
};

#endif