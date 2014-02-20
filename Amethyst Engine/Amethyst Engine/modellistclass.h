#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_

#include <d3dx10math.h>
#include <stdlib.h>
#include <time.h>

class ModelListClass
{
private:
	struct ModelInfoType
	{
		D3DXVECTOR4 color;
		float positionX, positionY, positionZ;
	};

public:
	ModelListClass();
	ModelListClass(const ModelListClass&);
	~ModelListClass();

	bool Initialize(int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, float&, float&, float&, D3DXVECTOR4&);

private:
	int h_modelCount;
	ModelInfoType *h_ModelInfoList;
};

#endif