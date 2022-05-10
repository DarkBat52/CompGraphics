#include "Camera.h"

Matrix Camera::GetViewMatrix() const
{
	 return   Matrix::CreateLookAt(transform.Position, transform.Position + transform.Rotation.GetForwardVector(), Vector3::Up);

}

Matrix Camera::GetProjectionMatrix() const
{
	return ProjectionMatrix;
}

void Camera::UpdateProjectionMatrixPerspective(float FOV, float AspectRatio, float NearPlane, float FarPlane)
{
	this->FOV = FOV;
	this->AspectRatio = AspectRatio;
	this->NearPlane = NearPlane;
	this->FarPlane = FarPlane;

	ProjectionMatrix = Matrix::CreatePerspectiveFieldOfView(FOV, AspectRatio, NearPlane, FarPlane);
}

void Camera::UpdateProjectionMatrixOrthographic(float Width, float Height, float NearPlane, float FarPlane)
{
	ProjectionMatrix = Matrix::CreateOrthographic(Width, Height, NearPlane, FarPlane);
	this->NearPlane = NearPlane;
	this->FarPlane = FarPlane;
}

void Camera::UpdateFOV(float NewFOV)
{
	FOV = NewFOV;
	UpdateProjectionMatrixPerspective(FOV, AspectRatio, NearPlane, FarPlane);
}

// may need transposing
Matrix Camera::GetWorldToClipMatrix() const
{
	return  GetViewMatrix() * GetProjectionMatrix();
}

float Camera::GetFOV() const
{
	return FOV;
}

