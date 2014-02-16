#include "cameraclass.h"

CameraClass::CameraClass()
{
	h_posX = 0.0F;
	h_posY = 0.0F;
	h_posZ = 0.0F;

	h_rotX = 0.0F;
	h_rotY = 0.0F;
	h_rotZ = 0.0F;
}

CameraClass::CameraClass(const CameraClass& other)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	h_posX = x;
	h_posY = y;
	h_posZ = z;
	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	h_rotX = x;
	h_rotY = y;
	h_rotZ = z;
	return;
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return D3DXVECTOR3(h_posX, h_posY, h_posZ);
}

D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(h_rotX, h_rotY, h_rotZ);
}

void CameraClass::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	up.x = 0.0F;
	up.y = 1.0F;
	up.z = 0.0F;

	position.x = h_posX;
	position.y = h_posY;
	position.z = h_posZ;

	lookAt.x = 0.0F;
	lookAt.y = 0.0F;
	lookAt.z = 1.0F;

	pitch = h_rotX * 0.0174532925F; // Radians
	yaw = h_rotY * 0.0174532925F; // Radians
	roll = h_rotZ * 0.0174532925F; // Radians

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	lookAt = position + lookAt;

	D3DXMatrixLookAtLH(&h_viewMatrix, &position, &lookAt, &up);

	return;
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = h_viewMatrix;
	return;
}