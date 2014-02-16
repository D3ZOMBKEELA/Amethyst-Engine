#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <fstream>
using namespace std;

#include "textureclass.h"

class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D10Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D10Device*);

	int GetIndexCount();

	ID3D10ShaderResourceView *GetTexture();

private:
	bool InitializeBuffers(ID3D10Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D10Device*);

	bool LoadTexture(ID3D10Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D10Buffer *h_vertexBuffer, *h_indexBuffer;
	int h_vertexCount, h_indexCount;
	TextureClass *h_Texture;
	ModelType *h_model;
};

#endif