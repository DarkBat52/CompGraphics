#include "KatamariGame.h"
#include "FBXMeshComponent.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "CameraController.h"
#include "CameraOrbitController.h"
#include "InputDevice.h"
#include "WICTextureLoader.h"
#include "SphereCollisionComponent.h"

HRESULT KatamariGame::PrepareResources()
{
	Game::PrepareResources();

	clearColor = { 0.15f, 0.1f, 0.3f, 1.0f };

	meshLoader = new MeshLoader("../../Meshes/test.fbx");
	chessLoader = new MeshLoader("../../Meshes/ChessBoard.fbx");

	// PLAYER \\
	
	player = CreateGameComponent<FBXMeshComponent>();
	meshLoader->GetMesh(0, player);
	CreateWICTextureFromFile(Device.Get(), L"E:/repos/CompGraphicsHW/Textures/test.png", testTexResource.GetAddressOf(), testTexSRV.GetAddressOf(), 1024);
	player->SetAlbedoSRV(testTexSRV);
	player->transform.Scale = {0.15f, 0.15f, 0.15f};
	player->transform.Position.y -= 0.15f;



	chessBoard = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(6, chessBoard);
	CreateWICTextureFromFile(Device.Get(), L"../../Textures/Chess Board.jpg", cbTexResource.GetAddressOf(), cbTexSRV.GetAddressOf(), 1024);
	chessBoard->SetAlbedoSRV(cbTexSRV);
	chessBoard->transform.Scale = {0.02f, 0.02f, 0.02f};
	chessBoard->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	chessBoard->transform.Position.y -= 1.5f;

	pawn1 = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(3, pawn1);
	CreateWICTextureFromFile(Device.Get(), L"../../Textures/Black Pieces.jpg", cbTexResource.GetAddressOf(), cbTexSRV.GetAddressOf(), 1024);
	pawn1->SetAlbedoSRV(cbTexSRV);
	pawn1->transform.Scale = {0.01f, 0.01f, 0.01f};
	pawn1->transform.Scale /= 3.0f;
	pawn1->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	pawn1->transform.Position -= {1.0f, 0.35f, 2.0f};

	pawn2 = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(3, pawn2);
	pawn2->SetAlbedoSRV(cbTexSRV);
	pawn2->transform.Scale = { 0.01f, 0.01f, 0.01f };
	pawn2->transform.Scale /= 3.0f;
	pawn2->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	pawn2->transform.Position += {1.0f, -0.35f, 2.0f};

	knight1 = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(2, knight1);
	knight1->SetAlbedoSRV(cbTexSRV);
	knight1->transform.Scale = { 0.005f, 0.005f, 0.005f };
	knight1->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	knight1->transform.Position += {1.5f, -0.35f, 2.0f};

	bishop1 = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(0, bishop1);
	bishop1->SetAlbedoSRV(cbTexSRV);
	bishop1->transform.Scale = { 0.01f, 0.01f, 0.01f };
	bishop1->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	bishop1->transform.Position += {2.5f, -0.35f, 1.5f};

	queen = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(4, queen);
	queen->SetAlbedoSRV(cbTexSRV);
	queen->transform.Scale = { 0.015f, 0.015f, 0.015f };
	queen->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	queen->transform.Position += {2.5f, -0.35f, 2.5f};

	// white pieces \\

	pawn3 = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(3, pawn3);
	CreateWICTextureFromFile(Device.Get(), L"../../Textures/White.jpg", cbTexResource.GetAddressOf(), cbTexSRV.GetAddressOf(), 1024);
	pawn3->SetAlbedoSRV(cbTexSRV);
	pawn3->transform.Scale = { 0.01f, 0.01f, 0.01f };
	pawn3->transform.Scale /= 3.0f;
	pawn3->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	pawn3->transform.Position += {2.0f, -0.35f, 2.0f};

	pawn4 = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(3, pawn4);
	pawn4->SetAlbedoSRV(cbTexSRV);
	pawn4->transform.Scale = { 0.01f, 0.01f, 0.01f };
	pawn4->transform.Scale /= 3.0f;
	pawn4->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	pawn4->transform.Position += {-2.0f, -0.35f, -2.0f};

	knight2 = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(2, knight2);
	knight2->SetAlbedoSRV(cbTexSRV);
	knight2->transform.Scale = { 0.005f, 0.005f, 0.005f };
	knight2->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	knight2->transform.Position += {-1.5f, -0.35f, 2.0f};

	bishop2 = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(0, bishop2);
	bishop2->SetAlbedoSRV(cbTexSRV);
	bishop2->transform.Scale = { 0.01f, 0.01f, 0.01f };
	bishop2->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	bishop2->transform.Position += {2.5f, -0.35f, -1.5f};

	king = CreateGameComponent<FBXMeshComponent>();
	chessLoader->GetMesh(1, king);
	king->SetAlbedoSRV(cbTexSRV);
	king->transform.Scale = { 0.02f, 0.02f, 0.02f };
	king->transform.Rotation.SetEulerAngles(-90.0f, 0.0f, 0.0f);
	king->transform.Position += {-2.5f, -0.35f, -2.5f};

	// collsisions
	
	playerCol = CreateGameComponent<SphereCollisionComponent>();
	playerCol->SetParent(player);
	playerCol->setCollisionRadius(0.3f);

	pawn1Col = CreateGameComponent<SphereCollisionComponent>();
	pawn1Col->SetParent(pawn1);
	pawn1Col->setCollisionRadius(0.15f);
	pawn1Col->transform.Position.z += 2.0f;
	
	pawn2Col = CreateGameComponent<SphereCollisionComponent>();
	pawn2Col->SetParent(pawn2);
	pawn2Col->setCollisionRadius(0.15f);
	pawn2Col->transform.Position.z += 2.0f;

	pawn3Col = CreateGameComponent<SphereCollisionComponent>();
	pawn3Col->SetParent(pawn3);
	pawn3Col->setCollisionRadius(0.15f);
	pawn3Col->transform.Position.z += 2.0f;

	pawn4Col = CreateGameComponent<SphereCollisionComponent>();
	pawn4Col->SetParent(pawn4);
	pawn4Col->setCollisionRadius(0.15f);
	pawn4Col->transform.Position.z += 2.0f;

	knight1Col = CreateGameComponent<SphereCollisionComponent>();
	knight1Col->SetParent(knight1);
	knight1Col->setCollisionRadius(0.33f);
	knight1Col->transform.Position.z += 2.0f;

	knight2Col = CreateGameComponent<SphereCollisionComponent>();
	knight2Col->SetParent(knight2);
	knight2Col->setCollisionRadius(0.33f);
	knight2Col->transform.Position.z += 2.0f;

	bishop1Col = CreateGameComponent<SphereCollisionComponent>();
	bishop1Col->SetParent(bishop1);
	bishop1Col->setCollisionRadius(0.37f);
	bishop1Col->transform.Position.z += 2.0f;

	bishop2Col = CreateGameComponent<SphereCollisionComponent>();
	bishop2Col->SetParent(bishop2);
	bishop2Col->setCollisionRadius(0.37f);
	bishop2Col->transform.Position.z += 2.0f;

	queenCol = CreateGameComponent<SphereCollisionComponent>();
	queenCol->SetParent(queen);
	queenCol->setCollisionRadius(0.57f);
	queenCol->transform.Position.z += 2.0f;

	kingCol = CreateGameComponent<SphereCollisionComponent>();
	kingCol->SetParent(king);
	kingCol->setCollisionRadius(0.72f);
	kingCol->transform.Position.z += 2.0f;

	//Camera work

	currentCamera = CreateGameComponent<Camera>();
	Camera* fpsCam = currentCamera;
	currentCamera->UpdateProjectionMatrixPerspective(DirectX::XMConvertToRadians(60), static_cast<float>(Display->ClientWidth) / Display->ClientHeight, 0.01f, 100.0f);
	currentCamera->transform.Position.z += 5;

	camControl = CreateGameComponent<CameraController>();
	camOrbitControl = CreateGameComponent<CameraOrbitController>();
	//camControl->cam = currentCamera;
	camOrbitControl->cam = currentCamera;
	camOrbitControl->GCToOrbit = player;

	/*currentCamera->transform.Rotation = Vector3(-70.0f, 0.0f, 0.0f);
	currentCamera->transform.Position = Vector3(0.0f, 5.0f, 0.0f);
	currentCamera->UpdateProjectionMatrixOrthographic(20.0f, 20.0f, 0.0f, 100.0f);*/

	LightCam.transform.Rotation = Vector3(-70.0f, 0.0f, 0.0f);
	LightCam.transform.Position = Vector3(0.0f, 5.0f, 0.0f);
	LightCam.UpdateProjectionMatrixOrthographic(20.0f, 20.0f, 0.0f, 100.0f);
	DirectionalLight.direction = LightCam.transform.Rotation.GetForwardVector();

	return 0;
}

HRESULT KatamariGame::Update(float deltaTime)
{
	Game::Update(deltaTime);

#pragma region Player Movement
	
	Vector3 movementDelta;
	float Speed = 5.0f;
	if (input->IsKeyDown(87))
	{
		movementDelta.x += deltaTime * Speed;
	}
	if (input->IsKeyDown(83))
	{
		movementDelta.x -= deltaTime * Speed;
	}
	if (input->IsKeyDown(68))
	{
		movementDelta.y += deltaTime * Speed;
	}
	if (input->IsKeyDown(65))
	{
		movementDelta.y -= deltaTime * Speed;
	}
	const float radius = 1.0f;
	const float rotAngleX = -movementDelta.x / radius;
	const float rotAngleY = -movementDelta.y / radius;
	const Vector3 right = currentCamera->transform.Rotation.GetRightVector();
	player->transform.Rotation.RotateAroundAxis(right, rotAngleX);
	const Vector3 forward = right.Cross(Vector3::Up);
	player->transform.Rotation.RotateAroundAxis(forward, rotAngleY);
	player->transform.Position -= forward * movementDelta.x;
	player->transform.Position += right * movementDelta.y;
#pragma endregion Player Movement

#pragma region Collisions
	auto cols = GetOverlappingComponents(*playerCol);

	if (!isIntersecting) 
	{
		for (auto col : cols) 
		{
			isIntersecting = true;
			if (static_cast<SphereCollisionComponent*>(col)->getCollisionRadius() < playerCol->getCollisionRadius())
			{
				auto parent = col->parent;
				parent->children.clear();
				parent->SetParent(player);
				parent->transform = parent->transform.GetTransformMatrix() * parent->parent->GetWorldTransform().GetInverseTransformMatrix();
				playerCol->setCollisionRadius(pow(pow(playerCol->getCollisionRadius(), 3) 
					+ pow(static_cast<SphereCollisionComponent*>(col)->getCollisionRadius(), 3),0.3333333));
				collisions.erase(std::remove(collisions.begin(), collisions.end(), col), collisions.end());
			}
			
		}

	}
	else if (cols.empty())
	{
		isIntersecting = false;
	}

#pragma endregion Collisions

	return 0;
}
