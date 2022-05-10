#pragma once
#include "GameComponent.h"
class CameraOrbitController :
    public GameComponent
{
public:

	HRESULT Update(float DeltaTime) override;

	float Speed = 3.0f;

	float OrbitRadius = 5.0f;

	GameComponent* GCToOrbit = nullptr;

	class Camera* cam = nullptr;

private:

	float Pitch = 0.0f;
	float Yaw = 0.0f;

	const float MaxPitch = 85.0f;

	float RotSpeedYaw = 50000.0f;
	float RotSpeedPitch = 15000.0f;
};

