#include "bitmapclass.h"

BitmapClass::BitmapClass()
{
	h_vertexBuffer = 0;
	h_indexBuffer = 0;
	h_Texture = 0;
}

BitmapClass::BitmapClass(const BitmapClass& other)
{
}

BitmapClass::~BitmapClass()
{
}

bool BitmapClass::Initialize(ID3D10Device *device, int screenWidth, int screenHeight, WCHAR *textureFilename, int bitmapWidth, int bitmapHeight)
{
	bool result;

	h_screenWidth = screenWidth;
	h_screenHeight = screenHeight;

	h_bitmapWidth = bitmapWidth;
	h_bitmapHeight = bitmapHeight;

	h_prevPosX = -1;
	h_prevPosY = -1;

	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	result = LoadTexture(device, textureFilename);
	if(!result)
	{
		return false;
	}

	return true;
}

void BitmapClass::Shutdown()
{
	ReleaseTexture();

	ShutdownBuffers();

	return;
}

bool BitmapClass::Render(ID3D10Device *device, int posX, int posY)
{
	bool result;

	result = UpdateBuffers(posX, posY);
	if(!result)
	{
		return false;
	}

	RenderBuffers(device);

	return true;
}

int BitmapClass::GetIndexCount()
{
	return h_indexCount;
}

ID3D10ShaderResourceView *BitmapClass::GetTexture()
{
	return h_Texture->GetTexture();
}

bool BitmapClass::InitializeBuffers(ID3D10Device *device)
{
	VertexType *vertices;
	unsigned long *indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	h_vertexCount = 6;
	h_indexCount = h_vertexCount;

	vertices = new VertexType[h_vertexCount];
	if(!vertices)
	{
		return false;
	}

	indices = new unsigned long[h_indexCount];
	if(!indices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * h_vertexCount));

	for(i = 0; i < h_indexCount; i++)
	{
		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * h_vertexCount;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0; // OPTIONAL
	vertexData.SysMemSlicePitch = 0; // OPTIONAL

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &h_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * h_indexCount;
	indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0; // OPTIONAL
	indexData.SysMemSlicePitch = 0; // OPTIONAL

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &h_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}

void BitmapClass::ShutdownBuffers()
{
	if(h_indexBuffer)
	{
		h_indexBuffer->Release();
		h_indexBuffer = 0;
	}

	if(h_vertexBuffer)
	{
		h_vertexBuffer->Release();
		h_vertexBuffer = 0;
	}

	return;
}

bool BitmapClass::UpdateBuffers(int posX, int posY)
{
	float left, right, top, bottom;
	VertexType *vertices;
	void *verticesPtr;
	HRESULT result;

	if((posX == h_prevPosX) && (posY == h_prevPosY))
	{
		return true;
	}

	h_prevPosX = posX;
	h_prevPosY = posY;

	left = (float)((h_screenWidth / 2) * -1) + (float)posX;
	
	right = left + (float)h_bitmapWidth;

	top = (float)(h_screenHeight / 2) - (float)posY;
	
	bottom = top - (float)h_bitmapHeight;

	vertices = new VertexType[h_vertexCount];
	if(!vertices)
	{
		return false;
	}

	vertices[0].position = D3DXVECTOR3(left, top, 0.0F);
	vertices[0].texture = D3DXVECTOR2(0.0F, 0.0F);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0F);
	vertices[1].texture = D3DXVECTOR2(1.0F, 1.0F);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0F);
	vertices[2].texture = D3DXVECTOR2(0.0F, 1.0F);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0F);
	vertices[3].texture = D3DXVECTOR2(0.0F, 0.0F);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0F);
	vertices[4].texture = D3DXVECTOR2(1.0F, 0.0F);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0F);
	vertices[5].texture = D3DXVECTOR2(1.0F, 1.0F);

	verticesPtr = 0;

	result = h_vertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);
	if(FAILED(result))
	{
		return false;
	}

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * h_vertexCount));

	h_vertexBuffer->Unmap();

	delete [] vertices;
	vertices = 0;

	return true;
}

void BitmapClass::RenderBuffers(ID3D10Device *device)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	device->IASetVertexBuffers(0, 1, &h_vertexBuffer, &stride, &offset);

	device->IASetIndexBuffer(h_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool BitmapClass::LoadTexture(ID3D10Device *device, WCHAR *filename)
{
	bool result;

	h_Texture = new TextureClass;
	if(!h_Texture)
	{
		return false;
	}

	result = h_Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}

void BitmapClass::ReleaseTexture()
{
	if(h_Texture)
	{
		h_Texture->Shutdown();
		delete h_Texture;
		h_Texture = 0;
	}

	return;
}