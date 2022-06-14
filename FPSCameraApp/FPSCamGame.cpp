#include "FPSCamGame.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "CameraController.h"
#include "CameraOrbitController.h"
#include "InputDevice.h"

std::vector<Vector4> GenerateSphere(const int numPointsVert, const int numPointsHor, std::vector<int>& indices, std::vector<Vector4>& points, Vector4 color);

HRESULT FPSCamGame::PrepareResources()
{

    clearColor = {0.15f, 0.1f, 0.3f, 1.0f};

	XMFLOAT4 points[16] =
	{
		XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),		// 0
		XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),	// 1
		XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),	// 2
		XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),	// 3
		XMFLOAT4(0.5f, 0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f),	// 4
		XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),	// 5
		XMFLOAT4(0.5f, -0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),	// 6
		XMFLOAT4(-0.5f, 0.5f, -0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f),	// 7
	};

	int indices[] =
	{
		0, 1, 2,
		1, 0, 3,
		4, 5, 6,
		5, 4, 7,
		4, 0, 2,
		4, 2, 6,
		7, 5, 1,
		7, 1, 3,
		4, 0, 3,
		4, 3, 7,
		6, 1, 2,
		6, 5, 1
	};

	cube = CreateGameComponent<MeshComponent>(indices, std::size(indices), points, std::size(points));
	cube->transform.Position = { 0.0f, 10.0f, 3.0f };
	cube->transform.Rotation.SetEulerAngles(45, 45, 90);

	cube2 = CreateGameComponent<MeshComponent>(indices, std::size(indices), points, std::size(points));
	cube2->transform.Position = {3.0f, 10.0f, 0.0f};

	std::vector<int> sphereIndices; 
	std::vector<Vector4> spherePoints;
	Vector4 sunColor = {1.0f, 0.9f, 0.3f, 1.0f};

	GenerateSphere(24, 48, sphereIndices, spherePoints, sunColor);

	sun = CreateGameComponent<MeshComponent>(&sphereIndices[0], sphereIndices.size(), &spherePoints[0], spherePoints.size());

	// Mercury

	sphereIndices.clear();
	spherePoints.clear();
	Vector4 mercuryColor = { 0.6f, 0.55f, 0.55f, 1.0f };
	GenerateSphere(24, 48, sphereIndices, spherePoints, mercuryColor);
	mercury = CreateGameComponent<MeshComponent>(&sphereIndices[0], sphereIndices.size(), &spherePoints[0], spherePoints.size());
	mercury->transform.Scale *= 0.15;
	mercury->transform.Position = { 2.0f, 0.0f, 0.0f };
	mercury->SetParent(sun);

	// Venus

	sphereIndices.clear();
	spherePoints.clear();
	Vector4 venusColor = { 0.8f, 0.5f, 0.4f, 1.0f };
	GenerateSphere(24, 48, sphereIndices, spherePoints, venusColor);
	venus = CreateGameComponent<MeshComponent>(&sphereIndices[0], sphereIndices.size(), &spherePoints[0], spherePoints.size());
	venus->transform.Scale *= 0.18;
	venus->transform.Position = { 3.5f, 0.0f, 0.0f };
	venus->SetParent(sun);

	// Earth
	sphereIndices.clear();
	spherePoints.clear();
	Vector4 earthColor = {0.1f, 0.2f, 0.45f, 1.0f};
	GenerateSphere(24, 48, sphereIndices, spherePoints, earthColor);
	earth = CreateGameComponent<MeshComponent>(&sphereIndices[0], sphereIndices.size(), &spherePoints[0], spherePoints.size());
	earth->transform.Scale *= 0.2;
	earth->transform.Position = {5.0f, 0.0f, 0.0f};
	earth->SetParent(sun);

	//Moon
	sphereIndices.clear();
	spherePoints.clear();
	Vector4 moonColor = { 0.4f, 0.4f, 0.5f, 1.0f };
	GenerateSphere(24, 48, sphereIndices, spherePoints, moonColor);
	moon = CreateGameComponent<MeshComponent>(&sphereIndices[0], sphereIndices.size(), &spherePoints[0], spherePoints.size());
	moon->transform.Scale *= 0.2;
	moon->transform.Position = { 2.0f, 0.0f, 0.0f };
	moon->SetParent(earth);

	//Mars
	sphereIndices.clear();
	spherePoints.clear();
	Vector4 marsColor = { 0.9f, 0.3f, 0.1f, 1.0f };
	GenerateSphere(24, 48, sphereIndices, spherePoints, marsColor);
	mars = CreateGameComponent<MeshComponent>(&sphereIndices[0], sphereIndices.size(), &spherePoints[0], spherePoints.size());
	mars->transform.Scale *= 0.2;
	mars->transform.Position = { 6.5f, 0.0f, 0.0f };
	mars->SetParent(sun);

	//Jupiter
	sphereIndices.clear();
	spherePoints.clear();
	Vector4 jupiterColor = { 0.7f, 0.65f, 0.3f, 1.0f };
	GenerateSphere(24, 48, sphereIndices, spherePoints, jupiterColor);
	jupiter = CreateGameComponent<MeshComponent>(&sphereIndices[0], sphereIndices.size(), &spherePoints[0], spherePoints.size());
	jupiter->transform.Scale *= 0.5;
	jupiter->transform.Position = { 8.5f, 0.0f, 0.0f };
	jupiter->SetParent(sun);

	//Camera work

	currentCamera = CreateGameComponent<Camera>();
	Camera* fpsCam = currentCamera;
	currentCamera->UpdateProjectionMatrixPerspective(DirectX::XMConvertToRadians(60), static_cast<float>(Display->ClientWidth) / Display->ClientHeight, 0.01f, 100.0f);
	currentCamera->transform.Position.z += 5;

	camControl = CreateGameComponent<CameraController>();
	camOrbitControl = CreateGameComponent<CameraOrbitController>();
	camControl->cam = currentCamera;
	//camOrbitControl->cam = currentCamera;
	camOrbitControl->GCToOrbit = earth;

	return Game::PrepareResources();
}

HRESULT FPSCamGame::Update(float deltaTime)
{
	Game::Update(deltaTime);

	mercury->transform = mercury->transform.GetTransformMatrix() * Matrix::CreateFromAxisAngle(Vector3::Up, deltaTime * 0.2f);
	venus->transform = venus->transform.GetTransformMatrix() * Matrix::CreateFromAxisAngle(Vector3::Up, deltaTime * 0.19f);
	earth->transform = earth->transform.GetTransformMatrix() * Matrix::CreateFromAxisAngle(Vector3::Up, deltaTime * 0.1f);
	moon->transform = moon->transform.GetTransformMatrix() * Matrix::CreateFromAxisAngle(Vector3::Up, deltaTime * 0.5f);
	mars->transform = mars->transform.GetTransformMatrix() * Matrix::CreateFromAxisAngle(Vector3::Up, deltaTime * 0.25f);
	jupiter->transform = jupiter->transform.GetTransformMatrix() * Matrix::CreateFromAxisAngle(Vector3::Up, deltaTime * 0.29f);

	if (input->IsKeyDown(79)) {
		camOrbitControl->cam = currentCamera;
		camControl->cam = nullptr;
	}

	if (input->IsKeyDown(70)) {
		camControl->cam = currentCamera;
		camOrbitControl->cam = nullptr;
	}

	cube->transform.Position += {0.0f, 0.05f * sin(TotalTime), 0.0f};
	cube2->transform.Position += {0.0f, 0.05f * -sin(TotalTime), 0.0f};

	return 0;
}


std::vector<Vector4> GenerateSphere(const int numPointsVert, const int numPointsHor, std::vector<int>& indices, std::vector<Vector4>& points, Vector4 color) {

#pragma region GeneratePoints
	// Generate north pole point
	points.push_back({ 0.0f, 1.0f, 0.0f, 1.0f });
	points.push_back(color);

	const float phetaDelta = XM_PI / (numPointsVert + 1);
	for (int j = 0; j < numPointsVert; ++j)
	{
		// Generate current circle points
		const float pheta = XM_PIDIV2 - phetaDelta * (j + 1);
		const float y = sinf(pheta);
		const float deltaAlpha = XM_2PI / static_cast<float>(numPointsHor);
		const float curRadius = cosf(pheta);
		for (int i = 0; i < numPointsHor; ++i)
		{
			const float alpha = deltaAlpha * i;
			points.push_back(XMFLOAT4(curRadius * cosf(alpha), y, curRadius * sinf(alpha), 1.0f));
			points.push_back(XMFLOAT4(color));
		}
	}

	// Generate south pole point
	points.push_back({ 0.0f, -1.0f, 0.0f, 1.0f });
	points.push_back(color);
#pragma endregion GeneratePoints

#pragma region CreateTriangleIndices
	// Connect the first circle to the north pole
	for (int i = 1; i <= numPointsHor; ++i)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back((i % numPointsHor) + 1);
	}
	// Connect the intermediate circles to each other
	for (int j = 1; j < numPointsVert; ++j)
	{
		const int curOffset = j * numPointsHor;
		const int prevOffset = curOffset - numPointsHor;
		for (int i = 1; i <= numPointsHor; ++i)
		{
			const int circlePoint1 = i;
			const int circlePoint2 = (i % numPointsHor) + 1;
			indices.push_back(prevOffset + circlePoint2);
			indices.push_back(prevOffset + circlePoint1);
			indices.push_back(curOffset + circlePoint1);
			indices.push_back(curOffset + circlePoint1);
			indices.push_back(curOffset + circlePoint2);
			indices.push_back(prevOffset + circlePoint2);
		}
	}
	// Connect the last circle to the south pole
	const int offset = (numPointsVert - 1) * numPointsHor;
	for (int i = 1; i <= numPointsHor; ++i)
	{
		indices.push_back(offset + i);
		indices.push_back(offset + (i % numPointsHor) + 1);
		indices.push_back(numPointsHor * numPointsVert + 1);
	}
#pragma endregion CreateTriangleIndices

	return points;
}