#include "frustumclass.h"

FrustumClass::FrustumClass()
{
}

FrustumClass::FrustumClass(const FrustumClass& other)
{
}

FrustumClass::~FrustumClass()
{
}

void FrustumClass::ConstructFrustum(float screenDepth, D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix)
{
	float zMinimum, r;
	D3DXMATRIX matrix;

	zMinimum = -projectionMatrix._43 / projectionMatrix._33;
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix._33 = r;
	projectionMatrix._43 = -r * zMinimum;

	D3DXMatrixMultiply(&matrix, &viewMatrix, &projectionMatrix);

	h_planes[0].a = matrix._14 + matrix._13;
	h_planes[0].b = matrix._24 + matrix._23;
	h_planes[0].c = matrix._34 + matrix._33;
	h_planes[0].d = matrix._44 + matrix._43;
	D3DXPlaneNormalize(&h_planes[0], &h_planes[0]);

	h_planes[1].a = matrix._14 + matrix._13;
	h_planes[1].b = matrix._24 + matrix._23;
	h_planes[1].c = matrix._34 + matrix._33;
	h_planes[1].d = matrix._44 + matrix._43;
	D3DXPlaneNormalize(&h_planes[1], &h_planes[1]);

	h_planes[2].a = matrix._14 + matrix._11;
	h_planes[2].b = matrix._24 + matrix._21;
	h_planes[2].c = matrix._34 + matrix._31;
	h_planes[2].d = matrix._44 + matrix._41;
	D3DXPlaneNormalize(&h_planes[2], &h_planes[2]);

	h_planes[3].a = matrix._14 + matrix._11;
	h_planes[3].b = matrix._24 + matrix._21;
	h_planes[3].c = matrix._34 + matrix._31;
	h_planes[3].d = matrix._44 + matrix._41;
	D3DXPlaneNormalize(&h_planes[3], &h_planes[3]);

	h_planes[4].a = matrix._14 + matrix._12;
	h_planes[4].b = matrix._24 + matrix._22;
	h_planes[4].c = matrix._34 + matrix._32;
	h_planes[4].d = matrix._44 + matrix._42;
	D3DXPlaneNormalize(&h_planes[4], &h_planes[4]);

	h_planes[5].a = matrix._14 + matrix._12;
	h_planes[5].b = matrix._24 + matrix._22;
	h_planes[5].c = matrix._34 + matrix._32;
	h_planes[5].d = matrix._44 + matrix._42;
	D3DXPlaneNormalize(&h_planes[5], &h_planes[5]);

	return;
}

bool FrustumClass::CheckPoint(float x, float y, float z)
{
	int i;

	for(i = 0; i < 6; i++)
	{
		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3(x, y, z)) < 0.0F)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;

	for(i = 0; i < 6; i++)
	{
		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter - radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter - radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter + radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter + radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter - radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter - radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter + radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter + radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;

	for(i = 0; i < 6; i++)
	{
		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3(xCenter, yCenter, zCenter)) < -radius)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;

	for(i = 0; i < 6; i++)
	{
		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter - ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter - ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter + ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter - ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter + ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter - ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter + ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&h_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter + ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}