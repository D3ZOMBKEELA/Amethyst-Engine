#ifndef _D3DCLASS_H_
#define _D3DCLASS_H_

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "dxgi.lib")

#include <d3d10.h>
#include <d3dx10.h>

class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D10Device *GetDevice();

	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);

	void GetVideoCardInfo(char*, int&);

private:
	bool h_vsync_enabled;
	int h_videoCardMemory;
	char h_videoCardDescription[128];
	IDXGISwapChain *h_swapChain;
	ID3D10Device *h_device;
	ID3D10RenderTargetView *h_renderTargetView;
	ID3D10Texture2D *h_depthStencilBuffer;
	ID3D10DepthStencilState *h_depthStencilState;
	ID3D10DepthStencilView *h_depthStencilView;
	ID3D10RasterizerState *h_rasterState;
	D3DXMATRIX h_projectionMatrix;
	D3DXMATRIX h_worldMatrix;
	D3DXMATRIX h_orthoMatrix;
};

#endif