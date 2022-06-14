#include "KatamariGame.h"
#include "FBXMeshComponent.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "CameraController.h"
#include "CameraOrbitController.h"
#include "InputDevice.h"
#include "WICTextureLoader.h"

HRESULT KatamariGame::PrepareResources()
{

	clearColor = { 0.15f, 0.1f, 0.3f, 1.0f };

	meshLoader = new MeshLoader("../../Meshes/test.fbx");

	testfbx = CreateGameComponent<FBXMeshComponent>();
	meshLoader->GetMesh(0, testfbx);
	CreateWICTextureFromFile(Device.Get(), L"../../Textures/test.png", testTexResource.GetAddressOf(), testTexSRV.GetAddressOf(), 1024);
	testfbx->SetAlbedoSRV(testTexSRV);

	//Camera work

	currentCamera = CreateGameComponent<Camera>();
	Camera* fpsCam = currentCamera;
	currentCamera->UpdateProjectionMatrixPerspective(DirectX::XMConvertToRadians(60), static_cast<float>(Display->ClientWidth) / Display->ClientHeight, 0.01f, 1000.0f);
	currentCamera->transform.Position.z += 5;

	camControl = CreateGameComponent<CameraController>();
	camOrbitControl = CreateGameComponent<CameraOrbitController>();
	//camControl->cam = currentCamera;
	camOrbitControl->cam = currentCamera;
	camOrbitControl->GCToOrbit = testfbx;

	
	return Game::PrepareResources();
}

HRESULT KatamariGame::Update(float deltaTime)
{
	Game::Update(deltaTime);
	return 0;
}
