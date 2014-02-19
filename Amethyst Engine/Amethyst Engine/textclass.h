#ifndef _TEXTCLASS_H_
#define _TEXTCLASS_H_

#include "fontclass.h"
#include "fontshaderclass.h"

class TextClass
{
private:
	struct SentenceType
	{
		ID3D10Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D10Device*, HWND, int, int, D3DXMATRIX);
	void Shutdown();
	void Render(ID3D10Device*, D3DXMATRIX, D3DXMATRIX);
	bool SetMousePosition(int, int);

private:
	bool InitializeSentence(SentenceType**, int, ID3D10Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float);
	void ReleaseSentence(SentenceType**);
	void RenderSentence(ID3D10Device*, SentenceType*, D3DXMATRIX, D3DXMATRIX);

private:
	FontClass *h_Font;
	FontShaderClass *h_FontShader;
	int h_screenWidth, h_screenHeight;
	D3DXMATRIX h_baseViewMatrix;

	SentenceType *h_sentence1;
	SentenceType *h_sentence2;
};

#endif