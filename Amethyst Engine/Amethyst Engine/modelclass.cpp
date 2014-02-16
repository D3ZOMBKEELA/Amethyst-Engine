#include "modelclass.h"

ModelClass::ModelClass()
{
	h_vertexBuffer = 0;
	h_indexBuffer = 0;
	h_Texture = 0;
	h_model = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{
}

ModelClass::~ModelClass()
{
}

bool ModelClass::Initialize(ID3D10Device *device, char *modelFilename, WCHAR *textureFilename)
{
	bool result;

	result = LoadModel(modelFilename);
	if(!result)
	{
		return false;
	}

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

void ModelClass::Shutdown()
{
	ReleaseTexture();

	ShutdownBuffers();

	ReleaseModel();

	return;
}

void ModelClass::Render(ID3D10Device *device)
{
	RenderBuffers(device);

	return;
}

int ModelClass::GetIndexCount()
{
	return h_indexCount;
}

ID3D10ShaderResourceView *ModelClass::GetTexture()
{
	return h_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D10Device *device)
{
	VertexType *vertices;
	unsigned long *indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

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

	for(i = 0; i < h_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(h_model[i].x, h_model[i].y, h_model[i].z);
		vertices[i].texture = D3DXVECTOR2(h_model[i].tu, h_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(h_model[i].nx, h_model[i].ny, h_model[i].nz);

		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * h_vertexCount;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
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

void ModelClass::ShutdownBuffers()
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

void ModelClass::RenderBuffers(ID3D10Device *device)
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

bool ModelClass::LoadTexture(ID3D10Device *device, WCHAR *filename)
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

void ModelClass::ReleaseTexture()
{
	if(h_Texture)
	{
		h_Texture->Shutdown();
		delete h_Texture;
		h_Texture = 0;
	}

	return;
}

bool ModelClass::LoadModel(char *filename)
{
	ifstream fin;
	char input;
	int i;

	fin.open(filename);

	if(fin.fail())
	{
		return false;
	}

	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}

	fin >> h_vertexCount;

	h_indexCount = h_vertexCount;

	h_model = new ModelType[h_vertexCount];
	if(!h_model)
	{
		return false;
	}

	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	for(i = 0; i < h_vertexCount; i++)
	{
		fin >> h_model[i].x >> h_model[i].y >> h_model[i].z;
		fin >> h_model[i].tu >> h_model[i].tv;
		fin >> h_model[i].nx >> h_model[i].ny >> h_model[i].nz;
	}

	fin.close();

	return true;
}

void ModelClass::ReleaseModel()
{
	if(h_model)
	{
		delete [] h_model;
		h_model = 0;
	}

	return;
}