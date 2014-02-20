#include "modellistclass.h"

ModelListClass::ModelListClass()
{
	h_ModelInfoList = 0;
}

ModelListClass::ModelListClass(const ModelListClass& other)
{
}

ModelListClass::~ModelListClass()
{
}

bool ModelListClass::Initialize(int numModels)
{
	int i;
	float red, green, blue;

	h_modelCount = numModels;

	h_ModelInfoList = new ModelInfoType[h_modelCount];
	if(!h_ModelInfoList)
	{
		return false;
	}

	srand((unsigned int)time(NULL));

	for(i = 0; i < h_modelCount; i++)
	{
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

		h_ModelInfoList[i].color = D3DXVECTOR4(red, green, blue, 1.0f);

		h_ModelInfoList[i].positionX = (((float)rand()-(float)rand())/RAND_MAX) * 10.0f;
		h_ModelInfoList[i].positionY = (((float)rand()-(float)rand())/RAND_MAX) * 10.0f;
		h_ModelInfoList[i].positionZ = ((((float)rand()-(float)rand())/RAND_MAX) * 10.0f) + 5.0f;
	}

	return true;
}

void ModelListClass::Shutdown()
{
	if(h_ModelInfoList)
	{
		delete [] h_ModelInfoList;
		h_ModelInfoList = 0;
	}

	return;
}

int ModelListClass::GetModelCount()
{
	return h_modelCount;
}

void ModelListClass::GetData(int index, float& positionX, float& positionY, float& positionZ, D3DXVECTOR4& color)
{
	positionX = h_ModelInfoList[index].positionX;
	positionY = h_ModelInfoList[index].positionY;
	positionZ = h_ModelInfoList[index].positionZ;

	color = h_ModelInfoList[index].color;

	return;
}