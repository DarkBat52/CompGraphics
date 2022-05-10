#pragma once
#include "GameComponent.h"

class CameraController :
	public GameComponent
{
public:

	class Camera* cam = nullptr;

	HRESULT Update(float deltaTime) override;

private:

	float Pitch = 0.0f;
	float Yaw = 0.0f;

	const float MaxPitch = 85.0f;

	float movementSpeed = 1.0f;
	float RotSpeedPitch = 15000.0f;
	float RotSpeedYaw = 50000.0f;

	bool isOrtho = false;

};

