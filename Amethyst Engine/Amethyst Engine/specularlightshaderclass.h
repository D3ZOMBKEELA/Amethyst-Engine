#ifndef _SPECULARLIGHTSHADERCLASS_H
#define _SPECULARLIGHTSHADERCLASS_H_

#include <d3d10.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

class SpecularLightShaderClass
{
public:
	SpecularLightShaderClass();
	SpecularLightShaderClass(const SpecularLightShaderClass&);
	~SpecularLightShaderClass();

	bool Initialize(ID3D10Device*, HWND);
	void Shutdown();
	void Render(ID3D10Device*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3, D3DXVECTOR4, float);

private:
	bool InitializeShader(ID3D10Device*, HWND, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	void SetShaderParameters(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D10ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3, D3DXVECTOR4, float);
	void RenderShader(ID3D10Device*, int);

private:
	ID3D10Effect *h_effect;
	ID3D10EffectTechnique *h_technique;
	ID3D10InputLayout *h_layout;

	ID3D10EffectMatrixVariable *h_worldMatrixPtr;
	ID3D10EffectMatrixVariable *h_viewMatrixPtr;
	ID3D10EffectMatrixVariable *h_projectionMatrixPtr;

	ID3D10EffectShaderResourceVariable *h_texturePtr;
	ID3D10EffectVectorVariable *h_lightDirectionPtr;
	ID3D10EffectVectorVariable *h_ambientColorPtr;
	ID3D10EffectVectorVariable *h_diffuseColorPtr;

	ID3D10EffectVectorVariable *h_cameraPositionPtr;
	ID3D10EffectVectorVariable *h_specularColorPtr;
	ID3D10EffectScalarVariable *h_specularPowerPtr;
};

#endif