#include "textclass.h"

TextClass::TextClass()
{
	h_Font = 0;
	h_FontShader = 0;

	h_sentence1 = 0;
	h_sentence2 = 0;
}

TextClass::TextClass(const TextClass& other)
{
}

TextClass::~TextClass()
{
}

bool TextClass::Initialize(ID3D10Device *device, HWND hwnd, int screenWidth, int screenHeight, D3DXMATRIX baseViewMatrix)
{
	bool result;

	h_screenWidth = screenWidth;
	h_screenHeight = screenHeight;

	h_baseViewMatrix = baseViewMatrix;

	h_Font = new FontClass;
	if(!h_Font)
	{
		return false;
	}

	result = h_Font->Initialize(device, "../Amethyst Engine/data/fontdata.txt", L"../Amethyst Engine/data/font.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		return false;
	}

	h_FontShader = new FontShaderClass;
	if(!h_FontShader)
	{
		return false;
	}

	result = h_FontShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	result = InitializeSentence(&h_sentence1, 16, device);
	if(!result)
	{
		return false;
	}

	result = UpdateSentence(h_sentence1, "Hello", 100, 100, 1.0F, 1.0F, 1.0F);
	if(!result)
	{
		return false;
	}

	result = InitializeSentence(&h_sentence2, 16, device);
	if(!result)
	{
		return false;
	}

	result = UpdateSentence(h_sentence2, "Goodbye", 100, 200, 1.0F, 1.0F, 0.0F);
	if(!result)
	{
		return false;
	}

	return true;
}

void TextClass::Shutdown()
{
	ReleaseSentence(&h_sentence1);
	ReleaseSentence(&h_sentence2);

	if(h_FontShader)
	{
		h_FontShader->Shutdown();
		delete h_FontShader;
		h_FontShader = 0;
	}

	if(h_Font)
	{
		h_Font->Shutdown();
		delete h_Font;
		h_Font = 0;
	}

	return;
}

void TextClass::Render(ID3D10Device *device, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	RenderSentence(device, h_sentence1, worldMatrix, orthoMatrix);
	RenderSentence(device, h_sentence2, worldMatrix, orthoMatrix);

	return;
}

bool TextClass::SetMousePosition(int mouseX, int mouseY)
{
	char tempString[16];
	char mouseString[16];
	bool result;

	_itoa_s(mouseX, tempString, 10);

	strcpy_s(mouseString, "Mouse X: ");
	strcat_s(mouseString, tempString);

	result = UpdateSentence(h_sentence1, mouseString, 20, 20, 1.0F, 1.0F, 1.0F);
	if(!result)
	{
		return false;
	}

	_itoa_s(mouseY, tempString, 10);

	strcpy_s(mouseString, "Mouse Y: ");
	strcat_s(mouseString, tempString);

	result = UpdateSentence(h_sentence2, mouseString, 20, 40, 1.0F, 1.0F, 1.0F);
	if(!result)
	{
		return false;
	}
}

bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D10Device *device)
{
	VertexType *vertices;
	unsigned long *indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	*sentence = new SentenceType;
	if(!*sentence)
	{
		return false;
	}

	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	(*sentence)->maxLength = maxLength;

	(*sentence)->vertexCount = 6 * maxLength;

	(*sentence)->indexCount = (*sentence)->vertexCount;

	vertices = new VertexType[(*sentence)->vertexCount];
	if(!vertices)
	{
		return false;
	}

	indices = new unsigned long[(*sentence)->indexCount];
	if(!indices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	for(i = 0; i < (*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
	indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
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

bool TextClass::UpdateSentence(SentenceType *sentence, char *text, int posX, int posY, float red, float green, float blue)
{
	int numLetters;
	VertexType *vertices;
	float drawX, drawY;
	void *verticesPtr;
	HRESULT result;

	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	numLetters = (int)strlen(text);

	if(numLetters > sentence->maxLength)
	{
		return false;
	}

	vertices = new VertexType[sentence->vertexCount];
	if(!vertices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));

	drawX = (float)(((h_screenWidth / 2) * -1) + posX);
	drawY = (float)((h_screenHeight / 2) - posY);

	h_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	verticesPtr = 0;

	result = sentence->vertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**)&verticesPtr);
	if(FAILED(result))
	{
		return false;
	}

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	sentence->vertexBuffer->Unmap();

	delete [] vertices;
	vertices = 0;

	return true;
}

void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if(*sentence)
	{
		if((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		if((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		delete *sentence;
		*sentence  = 0;
	}

	return;
}

void TextClass::RenderSentence(ID3D10Device *device, SentenceType *sentence, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;

	stride = sizeof(VertexType);
	offset = 0;

	device->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

	device->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pixelColor = D3DXVECTOR4(sentence->red, sentence->green, sentence->blue, 1.0F);

	h_FontShader->Render(device, sentence->indexCount, worldMatrix, h_baseViewMatrix, orthoMatrix, h_Font->GetTexture(), pixelColor);

	return;
}