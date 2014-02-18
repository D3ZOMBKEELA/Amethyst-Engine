#include "fontclass.h"

FontClass::FontClass()
{
	h_Font = 0;
	h_Texture = 0;
}

FontClass::FontClass(const FontClass& other)
{
}

FontClass::~FontClass()
{
}

bool FontClass::Initialize(ID3D10Device *device, char *fontFilename, WCHAR *textureFilename)
{
	bool result;

	result = LoadFontData(fontFilename);
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

void FontClass::Shutdown()
{
	ReleaseTexture();

	ReleaseFontData();

	return;
}

bool FontClass::LoadFontData(char *filename)
{
	ifstream fin;
	int i;
	char temp;

	h_Font = new FontType[95];
	if(!h_Font)
	{
		return false;
	}

	fin.open(filename);
	if(fin.fail())
	{
		return false;
	}

	for(i = 0; i < 95; i++)
	{
		fin.get(temp);
		while(temp != ' ')
		{
			fin.get(temp);
		}
		fin.get(temp);
		while(temp != ' ')
		{
			fin.get(temp);
		}

		fin >> h_Font[i].left;
		fin >> h_Font[i].right;
		fin >> h_Font[i].size;
	}

	fin.close();

	return true;
}

void FontClass::ReleaseFontData()
{
	if(h_Font)
	{
		delete [] h_Font;
		h_Font = 0;
	}

	return;
}

bool FontClass::LoadTexture(ID3D10Device *device, WCHAR *filename)
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

void FontClass::ReleaseTexture()
{
	if(h_Texture)
	{
		h_Texture->Shutdown();
		delete h_Texture;
		h_Texture = 0;
	}

	return;
}

ID3D10ShaderResourceView *FontClass::GetTexture()
{
	return h_Texture->GetTexture();
}

void FontClass::BuildVertexArray(void *vertices, char *sentence, float drawX, float drawY)
{
	VertexType *vertexPtr;
	int numLetters, index, i, letter;

	vertexPtr = (VertexType*)vertices;

	numLetters = (int)strlen(sentence);

	index = 0;

	for(i = 0; i < numLetters; i++)
	{
		letter = ((int)sentence[i]) - 32;

		if(letter == 0)
		{
			drawX = drawX + 3.0F;
		}
		else
		{
			vertexPtr[index].position = D3DXVECTOR3(drawX, drawY, 0.0F);
			vertexPtr[index].texture = D3DXVECTOR2(h_Font[letter].left, 0.0F);
			index++;

			vertexPtr[index].position = D3DXVECTOR3((drawX + h_Font[letter].size), (drawY - 16), 0.0F);
			vertexPtr[index].texture = D3DXVECTOR2(h_Font[letter].right, 1.0F);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(drawX, (drawY - 16), 0.0F);
			vertexPtr[index].texture = D3DXVECTOR2(h_Font[letter].left, 1.0F);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(drawX, drawY, 0.0F);
			vertexPtr[index].texture = D3DXVECTOR2(h_Font[letter].left, 0.0F);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(drawX + h_Font[letter].size, drawY, 0.0F);
			vertexPtr[index].texture = D3DXVECTOR2(h_Font[letter].right, 0.0F);
			index++;

			vertexPtr[index].position = D3DXVECTOR3((drawX + h_Font[letter].size), (drawY - 16), 0.0F);
			vertexPtr[index].texture = D3DXVECTOR2(h_Font[letter].right, 1.0F);
			index ++;

			drawX = drawX + h_Font[letter].size + 1.0F;
		}
	}

	return;
}