#include "ambientlightshaderclass.h"

AmbientLightShaderClass::AmbientLightShaderClass()
{
	h_effect = 0;
	h_technique = 0;
	h_layout = 0;

	h_worldMatrixPtr = 0;
	h_viewMatrixPtr = 0;
	h_projectionMatrixPtr = 0;

	h_texturePtr = 0;
	h_lightDirectionPtr = 0;
	h_ambientColorPtr = 0;
	h_diffuseColorPtr = 0;
}

AmbientLightShaderClass::AmbientLightShaderClass(const AmbientLightShaderClass& other)
{
}

AmbientLightShaderClass::~AmbientLightShaderClass()
{
}

bool AmbientLightShaderClass::Initialize(ID3D10Device *device, HWND hwnd)
{
	bool result;

	result = InitializeShader(device, hwnd, L"../Amethyst Engine/ambientlight.fx");
	if(!result)
	{
		return false;
	}

	return true;
}

void AmbientLightShaderClass::Shutdown()
{
	ShutdownShader();

	return;
}

void AmbientLightShaderClass::Render(ID3D10Device *device, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D10ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor)
{
	SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambientColor, diffuseColor);

	RenderShader(device, indexCount);

	return;
}

bool AmbientLightShaderClass::InitializeShader(ID3D10Device *device, HWND hwnd, WCHAR *filename)
{
	HRESULT result;
	ID3D10Blob *errorMessage;
	D3D10_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D10_PASS_DESC passDesc;

	errorMessage = 0;

	result = D3DX10CreateEffectFromFile(filename, NULL, NULL, "fx_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, device, NULL, NULL, &h_effect, &errorMessage, NULL);
	if(FAILED(result))
	{
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, filename);
		}
		else
		{
			MessageBox(hwnd, filename, L"Missing shader file.", MB_OK);
		}

		return false;
	}

	h_technique =  h_effect->GetTechniqueByName("AmbientLightTechnique");
	if(!h_technique)
	{
		return false;
	}

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	h_technique->GetPassByIndex(0)->GetDesc(&passDesc);

	result = device->CreateInputLayout(polygonLayout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &h_layout);
	if(FAILED(result))
	{
		return false;
	}

	h_worldMatrixPtr = h_effect->GetVariableByName("worldMatrix")->AsMatrix();
	h_viewMatrixPtr = h_effect->GetVariableByName("viewMatrix")->AsMatrix();
	h_projectionMatrixPtr = h_effect->GetVariableByName("projectionMatrix")->AsMatrix();

	h_texturePtr = h_effect->GetVariableByName("shaderTexture")->AsShaderResource();
	h_lightDirectionPtr = h_effect->GetVariableByName("lightDirection")->AsVector();
	h_ambientColorPtr = h_effect->GetVariableByName("ambientColor")->AsVector();
	h_diffuseColorPtr = h_effect->GetVariableByName("diffuseColor")->AsVector();

	return true;
}

void AmbientLightShaderClass::ShutdownShader()
{
	h_lightDirectionPtr = 0;
	h_ambientColorPtr = 0;
	h_diffuseColorPtr = 0;
	h_texturePtr = 0;

	h_worldMatrixPtr = 0;
	h_viewMatrixPtr = 0;
	h_projectionMatrixPtr = 0;

	if(h_layout)
	{
		h_layout->Release();
		h_layout = 0;
	}

	h_technique = 0;

	if(h_effect)
	{
		h_effect->Release();
		h_effect = 0;
	}

	return;
}

void AmbientLightShaderClass::OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, WCHAR *shaderFilename)
{
	char *compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;

	compileErrors = (char*)(errorMessage->GetBufferPointer());

	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for(i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for details.", shaderFilename, MB_OK);

	return;
}

void AmbientLightShaderClass::SetShaderParameters(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D10ShaderResourceView *texture, D3DXVECTOR3 lightDirection, D3DXVECTOR4 ambientColor, D3DXVECTOR4 diffuseColor)
{
	h_worldMatrixPtr->SetMatrix((float*)&worldMatrix);
	h_viewMatrixPtr->SetMatrix((float*)&viewMatrix);
	h_projectionMatrixPtr->SetMatrix((float*)&projectionMatrix);

	h_texturePtr->SetResource(texture);
	h_lightDirectionPtr->SetFloatVector((float*)&lightDirection);
	h_ambientColorPtr->SetFloatVector((float*)&ambientColor);
	h_diffuseColorPtr->SetFloatVector((float*)&diffuseColor);

	return;
}

void AmbientLightShaderClass::RenderShader(ID3D10Device *device, int indexCount)
{
	D3D10_TECHNIQUE_DESC techniqueDesc;
	unsigned int i;

	device->IASetInputLayout(h_layout);

	h_technique->GetDesc(&techniqueDesc);

	for(i = 0; i < techniqueDesc.Passes; ++i)
	{
		h_technique->GetPassByIndex(i)->Apply(0);
		device->DrawIndexed(indexCount, 0, 0);
	}

	return;
}