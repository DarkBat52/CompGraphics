#include "CameraController.h"
#include "Game.h"
#include "InputDevice.h"
#include "Camera.h"


HRESULT CameraController::Update(float deltaTime)
{
	if (cam == nullptr) return 0;

	Game* game = Game::Get();

	Vector3 movement = {};

	if (game->input->IsKeyDown(87)) {
		movement.z += deltaTime * movementSpeed;
	}
	
	if (game->input->IsKeyDown(83)) {
		movement.z -= deltaTime * movementSpeed;
	}
	
	if (game->input->IsKeyDown(65)) {
		movement.x -= deltaTime * movementSpeed;
	}
	
	if (game->input->IsKeyDown(68)) {
		movement.x += deltaTime * movementSpeed;
	}
	
	if (game->input->IsKeyDown(69) && cam->GetFOV() < 140) {
		cam->UpdateFOV(cam->GetFOV() + 0.01f);
	}
	
	if (game->input->IsKeyDown(81) && cam->GetFOV() >= 0) {
		cam->UpdateFOV(cam->GetFOV() - 0.01f);
	}

	if (game->input->IsKeyDown(82)) {
		if (isOrtho) {
			cam->UpdateProjectionMatrixPerspective(DirectX::XMConvertToRadians(60),
				static_cast<float>(game->Display->ClientWidth) / game->Display->ClientHeight, 0.01f, 100.0f);
		}
		else {
			cam->UpdateProjectionMatrixOrthographic(game->Display->ClientWidth/20, game->Display->ClientHeight/20, 0.0f, 100.0f);
		}
		isOrtho = !isOrtho;
	}


	cam->transform.Position += movement.z * cam->transform.Rotation.GetForwardVector() + movement.x * cam->transform.Rotation.GetRightVector();

	float deltaX;
	float deltaY;
	game->input->GetMouseDelta(deltaX, deltaY);

	Pitch += deltaTime * deltaY * RotSpeedPitch;
	Pitch = Pitch < -MaxPitch ? -MaxPitch : Pitch > MaxPitch ? MaxPitch : Pitch;
	Yaw += deltaTime * deltaX * RotSpeedYaw;

	cam->transform.Rotation.SetEulerAngles(Pitch, Yaw, 0.0f);
	
}
