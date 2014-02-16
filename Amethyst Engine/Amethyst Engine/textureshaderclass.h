#ifndef _TEXTURESHADERCLASS_H_
#define _TEXTURESHADERCLASS_H_

#include <d3d10.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

class TextureShaderClass
{
public:
	TextureShaderClass();
	TextureShaderClass(const TextureShaderClass&);
	~TextureShaderClass();

	bool Initialize(ID3D10Device*, HWND);
	void Shutdown();
	void Render(ID3D10Device*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*);

private:
	bool InitializeShader(ID3D10Device*, HWND, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*);
	void RenderShader(ID3D10Device*, int);

private:
	ID3D10Effect *h_effect;
	ID3D10EffectTechnique *h_technique;
	ID3D10InputLayout *h_layout;

	ID3D10EffectMatrixVariable *h_worldMatrixPtr;
	ID3D10EffectMatrixVariable *h_viewMatrixPtr;
	ID3D10EffectMatrixVariable *h_projectionMatrixPtr;

	ID3D10EffectShaderResourceVariable *h_texturePtr;
};

#endif