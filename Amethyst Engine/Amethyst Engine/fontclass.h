#ifndef _FONTCLASS_H_
#define _FONTCLASS_H_

#include <fstream>;
using namespace std;

#include "textureclass.h"

class FontClass
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D10Device*, char*, WCHAR*);
	void Shutdown();

	ID3D10ShaderResourceView *GetTexture();

	void BuildVertexArray(void*, char*, float, float);

private:
	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D10Device*, WCHAR*);
	void ReleaseTexture();

private:
	FontType *h_Font;
	TextureClass *h_Texture;
};

#endif