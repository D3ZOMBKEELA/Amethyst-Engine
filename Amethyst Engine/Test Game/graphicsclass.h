#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "d3dclass.h"
#include "cameraclass.h"
#include "textclass.h"
#include "modelclass.h"
#include "diffuselightshaderclass.h"
#include "diffuselightclass.h"
#include "modellistclass.h"
#include "frustumclass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true; // Caps the fps at 60 if true else runs at max fps
const float SCREEN_DEPTH = 1000.0F;
const float SCREEN_NEAR = 0.1F;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(float);
	bool Render();

private:
	D3DClass *m_D3D;
	CameraClass *m_Camera;
	TextClass *m_Text;
	ModelClass *m_Model;
	DiffuseLightShaderClass *m_LightShader;
	DiffuseLightClass *m_Light;
	ModelListClass *m_ModelList;
	FrustumClass *m_Frustum;
};

#endif