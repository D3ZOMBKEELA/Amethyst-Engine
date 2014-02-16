#include "textureclass.h"

TextureClass::TextureClass()
{
	h_texture = 0;
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D10Device *device, WCHAR *filename)
{
	HRESULT result;

	result = D3DX10CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &h_texture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void TextureClass::Shutdown()
{
	if(h_texture)
	{
		h_texture->Release();
		h_texture = 0;
	}

	return;
}

ID3D10ShaderResourceView *TextureClass::GetTexture()
{
	return h_texture;
}