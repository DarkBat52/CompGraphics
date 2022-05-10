#include "CameraOrbitController.h"
#include "InputDevice.h"
#include "Game.h"
#include "Camera.h"

HRESULT CameraOrbitController::Update(float DeltaTime)
{
	if (cam == nullptr)
	{
		return 0;
	}

	InputDevice& input = *Game::Get()->input;

	float orbitRadiusDelta = 0.0f;

	if (input.IsKeyDown(69))
	{
		orbitRadiusDelta += DeltaTime * Speed;
	}
	if (input.IsKeyDown(81))
	{
		orbitRadiusDelta -= DeltaTime * Speed;
	}

	float deltaX;
	float deltaY;
	input.GetMouseDelta(deltaX, deltaY);

	Pitch += DeltaTime * deltaY * RotSpeedPitch;
	Pitch = Pitch < -MaxPitch ? -MaxPitch : Pitch > MaxPitch ? MaxPitch : Pitch;
	Yaw += DeltaTime * deltaX * RotSpeedYaw;

	OrbitRadius += orbitRadiusDelta;

	
	cam->transform = Matrix::CreateTranslation(Vector3(0.0f, 0.0f, OrbitRadius)) *
		Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(Yaw), DirectX::XMConvertToRadians(Pitch), 0.0f) *
		Matrix::CreateTranslation(GCToOrbit->GetWorldTransform().Position);

	return 0;
}
