#pragma once
#include "GameComponent.h"
class Camera :
    public GameComponent
{
public:

	Matrix GetViewMatrix() const;

	Matrix GetProjectionMatrix() const;

	void UpdateProjectionMatrixPerspective(float FOV, float AspectRatio, float NearPlane, float FarPlane);
	void UpdateProjectionMatrixOrthographic(float Width, float Height, float NearPlane, float FarPlane);

	void UpdateFOV(float NewFOV);

	Matrix GetWorldToClipMatrix() const;

	float GetFOV() const;

private:
	Matrix ProjectionMatrix = Matrix::Identity;

	float FOV;
	float AspectRatio;
	float NearPlane;
	float FarPlane;
};

