#ifndef _FONTSHADERCLASS_H
#define _FONTSHADERCLASS_H

#include <d3d10.h>
#include <d3dx10.h>
#include <fstream>
using namespace std;

class FontShaderClass
{
public:
	FontShaderClass();
	FontShaderClass(const FontShaderClass&);
	~FontShaderClass();

	bool Initialize(ID3D10Device*, HWND);
	void Shutdown();
	void Render(ID3D10Device*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*, D3DXVECTOR4);

private:
	bool InitializeShader(ID3D10Device*, HWND, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*, D3DXVECTOR4);
	void RenderShader(ID3D10Device*, int);

private:
	ID3D10Effect *h_effect;
	ID3D10EffectTechnique *h_technique;
	ID3D10InputLayout *h_layout;

	ID3D10EffectMatrixVariable *h_worldMatrixPtr;
	ID3D10EffectMatrixVariable *h_viewMatrixPtr;
	ID3D10EffectMatrixVariable *h_projectionMatrixPtr;
	ID3D10EffectShaderResourceVariable *h_texturePtr;

	ID3D10EffectVectorVariable *h_pixelColorPtr;
};

#endif