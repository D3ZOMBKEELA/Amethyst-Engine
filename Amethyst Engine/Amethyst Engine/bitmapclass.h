#ifndef _BITMAPCLASS_H_
#define _BITMAPCLASS_H_

#include "textureclass.h"

class BitmapClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialize(ID3D10Device*, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D10Device*, int, int);

	int GetIndexCount();
	ID3D10ShaderResourceView *GetTexture();

private:
	bool InitializeBuffers(ID3D10Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(int, int);
	void RenderBuffers(ID3D10Device*);

	bool LoadTexture(ID3D10Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D10Buffer *h_vertexBuffer, *h_indexBuffer;
	int h_vertexCount, h_indexCount;
	TextureClass *h_Texture;

	int h_screenWidth, h_screenHeight;
	int h_bitmapWidth, h_bitmapHeight;
	int h_prevPosX, h_prevPosY;
};

#endif