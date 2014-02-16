#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_SpecularLightShader = 0;
	m_SpecularLight = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Cloud not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0F, 0.0F, -10.0F);

	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	result = m_Model->Initialize(m_D3D->GetDevice(), "../Test Game/data/cube.txt", L"../Test Game/data/rockz.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not intialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_SpecularLightShader = new SpecularLightShaderClass;
	if(!m_SpecularLightShader)
	{
		return false;
	}

	result = m_SpecularLightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the diffuse light shader object.", L"Error", MB_OK);
		return false;
	}

	m_SpecularLight = new SpecularLightClass;
	if(!m_SpecularLight)
	{
		return false;
	}

	m_SpecularLight->SetAmbientColor(0.15F, 0.15F, 0.15F, 1.0F);
	m_SpecularLight->SetDiffuseColor(1.0F, 1.0F, 1.0F, 1.0F);
	m_SpecularLight->SetDirection(0.0F, 0.0F, 1.0F);
	m_SpecularLight->SetSpecularColor(1.0F, 1.0F, 1.0F, 1.0F);
	m_SpecularLight->SetSpecularPower(32.0F);

	return true;
}

void GraphicsClass::Shutdown()
{
	if(m_SpecularLight)
	{
		delete m_SpecularLight;
		m_SpecularLight = 0;
	}

	if(m_SpecularLightShader)
	{
		m_SpecularLightShader->Shutdown();
		delete m_SpecularLightShader;
		m_SpecularLightShader = 0;
	}

	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0F;

	rotation += (float)D3DX_PI * 0.005F;
	if(rotation > 360.0F)
	{
		rotation -= 360.0F;
	}

	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;

	m_D3D->BeginScene(0.0F, 0.0F, 0.0F, 1.0F);

	m_Camera->Render();

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixRotationY(&worldMatrix, rotation);

	m_Model->Render(m_D3D->GetDevice());

	m_SpecularLightShader->Render(m_D3D->GetDevice(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_SpecularLight->GetDirection(), m_SpecularLight->GetAmbientColor(), m_SpecularLight->GetDiffuseColor(), m_Camera->GetPosition(), m_SpecularLight->GetSpecularColor(), m_SpecularLight->GetSpecularPower());

	m_D3D->EndScene();

	return true;
}