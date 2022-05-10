#include "PongGame.h"
#include "MeshComponent.h"
#include "InputDevice.h"
#include <algorithm>
#include "CollisionComponent.h"
#include "AABBCollisionComponent.h"


void GenerateBall(int verts, XMFLOAT4 color, std::vector<XMFLOAT4>& circleVertices, std::vector<int>& circleIndices);

HRESULT PongGame::PrepareResources()
{
	Game* game = PongGame::Get();

	// All shadows

	Vector4 shadowColor = XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f);
	
	// square shadow
	XMFLOAT4 verts[8] = {
		XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(-0.5f, 0.5, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f)
	};

	int indices[] = { 0, 1, 2, 1, 0, 3 };

	//game->Components.push_back(new MeshComponent(indices, 6, verts, 8));

	//border shadow

	int borderIndices[] = {
		0, 1, 2,
		1, 2, 3,
		3, 4, 5,
		3, 5, 6,
		6, 7, 8,
		6, 8, 9
	};

	XMFLOAT4 BorderShadowVertices[20] = {
		XMFLOAT4(-0.95f, -0.65f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(-0.9f, -0.65f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(-0.95f, -0.95f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(-0.9f, -0.95f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(-0.9f, -0.9f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),

		XMFLOAT4(0.9f, -0.9f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(0.9f, -0.95f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(0.95f, -0.95f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(0.95f, -0.65f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f),
		XMFLOAT4(0.9f, -0.65f, 0.5f, 1.0f), XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f)
	};

	MeshComponent* LowerBorderShadow = new MeshComponent(borderIndices, std::size(borderIndices), BorderShadowVertices, 20);
	LowerBorderShadow->transform.Position = DirectX::SimpleMath::Vector3(0.025, -0.025, 0.5);
	game->Components.push_back(LowerBorderShadow);
	
	// uppper border shadow

	MeshComponent* UpperBorderShadow = new MeshComponent(borderIndices, std::size(borderIndices), BorderShadowVertices, 20);
	UpperBorderShadow->transform.Rotation.SetEulerAngles(0, 0, 180);
	UpperBorderShadow->transform.Position = DirectX::SimpleMath::Vector3(0.025, -0.025, 0.5);
	game->Components.push_back(UpperBorderShadow);


	// Left block shadow

	MeshComponent* leftBlockShadow = new MeshComponent(indices, 6, verts, 8);
	//leftBlockShadow->transform.Scale = Vector3(0.05, 0.5, 1);
	leftBlockShadow->transform.Position = Vector3( 0.5, -0.05, 0.5);
	game->Components.push_back(leftBlockShadow);

	// Right block shadow

	MeshComponent* rightBlockShadow = new MeshComponent(indices, 6, verts, 8);
	//rightBlockShadow->transform.Scale = Vector3(0.05, 0.5, 1);
	rightBlockShadow->transform.Position = Vector3( 0.5, -0.05, 0.5);
	game->Components.push_back(rightBlockShadow);


	// ball shadow

	std::vector<XMFLOAT4> circleVertices;
	std::vector<int> circleIndices;

	GenerateBall(40, XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f), circleVertices, circleIndices);

	MeshComponent* circleShadow = new MeshComponent(&circleIndices[0], circleIndices.size(), &circleVertices[0], circleVertices.size());
	//circleShadow->transform.Scale = Vector3(0.02, 0.03, 1.0);
	circleShadow->transform.Position = Vector3(1.0, -1.0, 0.0);

	game->Components.push_back(circleShadow);
	
	// GEOMETRY

	XMFLOAT4 vertices[8] = {
		XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
	};

	

	GameComponent* mc = new MeshComponent(indices, 6, vertices, 8);

	

	//game->Components.push_back(mc);
	
	

	// lower border
	XMFLOAT4 borderVertices[20] = {
		XMFLOAT4(-0.95f, -0.65f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(-0.9f, -0.65f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(-0.95f, -0.95f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(-0.9f, -0.95f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(-0.9f, -0.9f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),

		XMFLOAT4(0.9f, -0.9f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(0.9f, -0.95f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(0.95f, -0.95f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(0.95f, -0.65f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(0.9f, -0.65f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
	};

	



	MeshComponent* lowerBorder = new MeshComponent(borderIndices, std::size(borderIndices), borderVertices, 20);
	LowerBorderShadow->parent = lowerBorder;

	game->Components.push_back(lowerBorder);

	// upper border
	MeshComponent* border = new MeshComponent(borderIndices, std::size(borderIndices), borderVertices, 20);
	border->transform.Rotation.SetEulerAngles(0, 0, 180);
	border->transform.Position = DirectX::SimpleMath::Vector3(0, 0, 0.5);
	game->Components.push_back(border);
	
	
	// Left block

	MeshComponent* leftBlock = new MeshComponent(indices, 6, vertices, 8);
	leftBlock->transform.Scale = Vector3(0.05, 0.5, 1);
	leftBlock->transform.Position = Vector3(-0.7, 0, 0.5);
	leftBlockShadow->parent = leftBlock;
	game->Components.push_back(leftBlock);	

	this->leftBlock = leftBlock;

	// right block
	
	MeshComponent* rightBlock = new MeshComponent(indices, 6, vertices, 8);
	rightBlock->transform.Scale = Vector3(0.05, 0.5, 1);
	rightBlock->transform.Position = Vector3( 0.7, 0, 0.5);
	rightBlockShadow->parent = rightBlock;
	game->Components.push_back(rightBlock);

	this->rightBlock = rightBlock;

   

	// the ball

	circleVertices.clear();
	circleIndices.clear();

	GenerateBall(50, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), circleVertices, circleIndices);

	MeshComponent* circle = new MeshComponent(&circleIndices[0], circleIndices.size(), &circleVertices[0], circleVertices.size());
	circle->transform.Scale = Vector3(0.02, 0.03, 0.1);
	circleShadow->SetParent(circle);
	game->Components.push_back(circle);

	this->ball = circle;

	///collisions

	ballCol = CreateGameComponent<AABBCollisionComponent>();
	ballCol->SetParent(circle);
	

	leftBlockCol = CreateGameComponent<AABBCollisionComponent>();
	leftBlockCol->transform.Scale = {0.5f, 0.5f, 0.5f};
	leftBlockCol->SetParent(leftBlock);
	
	rightBlockCol = CreateGameComponent<AABBCollisionComponent>();
	rightBlockCol->transform.Scale = { 0.5f, 0.5f, 0.5f };
	rightBlockCol->SetParent(rightBlock);

	// BORDER COLLISIONS

	llborderCol = CreateGameComponent<AABBCollisionComponent>();
	llborderCol->transform.Position = { -0.925f, -0.8f, 1.0f };
	llborderCol->transform.Scale = { 0.025f, 0.15f, 1.0f };

	lrborderCol = CreateGameComponent<AABBCollisionComponent>();
	lrborderCol->transform.Position = { 0.925f, -0.8f, 1.0f };
	lrborderCol->transform.Scale = { 0.025f, 0.15f, 1.0f };

	lborderCol = CreateGameComponent<AABBCollisionComponent>();
	lborderCol->transform.Position = { 0.0f, -0.925f, 1.0f };
	lborderCol->transform.Scale = { 0.95f, 0.025f, 1.0f };

	ulborderCol = CreateGameComponent<AABBCollisionComponent>();
	ulborderCol->transform.Position = { -0.925f, 0.8f, 1.0f };
	ulborderCol->transform.Scale = { 0.05f, 0.15f, 1.0f };

	urborderCol = CreateGameComponent<AABBCollisionComponent>();
	urborderCol->transform.Position = { 0.925f, 0.8f, 1.0f };
	urborderCol->transform.Scale = { 0.05f, 0.15f, 1.0f };

	uborderCol = CreateGameComponent<AABBCollisionComponent>();
	uborderCol->transform.Position = { 0.0f, 0.925f, 1.0f };
	uborderCol->transform.Scale = { 0.95f, 0.025f, 1.0f };

	// GATE COLLISIONS

	leftGate = CreateGameComponent<AABBCollisionComponent>();
	leftGate->transform.Position = {-1.05f, 0.0f, 1.0f};
	leftGate->transform.Scale = { 0.05f, 1.0f, 1.0f };

	rightGate = CreateGameComponent<AABBCollisionComponent>();
	rightGate->transform.Position = {1.05f, 0.0f, 1.0f};
	rightGate->transform.Scale = { 0.05f, 1.0f, 1.0f };

	ballDirection = { 1.0f, std::clamp((float)rand()/ float(RAND_MAX), 0.3f, 0.9f) , 0.0f };

	std::cout << ballDirection.y << std::endl;


	Game::PrepareResources();

    return 0;
}

HRESULT PongGame::Update(float deltaTime)
{

	Game::Update(deltaTime);

	//left block movement

	if (input->IsKeyDown(87) && leftBlock->transform.Position.y < 0.65) {

		leftBlock->transform.Position.y += blockSpeed * deltaTime;

	}
	
	if (input->IsKeyDown(83) && leftBlock->transform.Position.y > -0.65) {

		leftBlock->transform.Position.y -= blockSpeed * deltaTime;

	}

	leftBlock->transform.Position.y = std::clamp(leftBlock->transform.Position.y, -0.65f, 0.65f);
	
	//right block movement

	if (input->IsKeyDown(38)) {

		rightBlock->transform.Position.y += blockSpeed * deltaTime;

	}
	
	if (input->IsKeyDown(40)) {

		rightBlock->transform.Position.y -= blockSpeed * deltaTime;

	}

	rightBlock->transform.Position.y = std::clamp(rightBlock->transform.Position.y, -0.65f, 0.65f);


	// ball movement

	ball->transform.Position += ballDirection * ballSpeed * deltaTime;
	
	if (fabs(ball->transform.Position.x) > 2.0f || fabs(ball->transform.Position.y) > 2.0f) {
		ball->transform.Position = {0.0f, 0.0f, 1.0f};
		ballSpeed = baseBallSpeed;
	}

	auto cols = GetOverlappingComponents(*ballCol);

	if (!isIntersecting) {
		for (auto col : cols) {
			isIntersecting = true;
			if (col == leftBlockCol || col == rightBlockCol || col == llborderCol || col == lrborderCol
				|| col == ulborderCol || col == urborderCol) {
				ballDirection.x = -ballDirection.x;
				if (col == leftBlockCol || col == rightBlockCol) {
					ballSpeed += ballAcceleration;
				}
			}
			else if (col == lborderCol || col == uborderCol) {
				ballDirection.y = -ballDirection.y;
			}
			else if (col == leftGate || col == rightGate) {
				ball->transform.Position = { 0.0f, 0.0f, 1.0f };
				ballDirection = { ballDirection.x * advantage, (float) std::clamp((float)rand() / float(RAND_MAX), 0.3f, 0.7f), 0.0f };
				ballSpeed = baseBallSpeed;
				if (col == leftGate) {
					++player2score;
					std::cout << "Player 2 Scores!!" << std::endl;
				}
				else if (col == rightGate) {
					++player1score;
					std::cout << "Player 1 Scores!!" << std::endl;
				}
				std::cout << "Current Score is " << player1score << '/' << player2score << std::endl;
			}
		}
	}
	else if (cols.empty()) {
		isIntersecting = false;
	}
	
	

	return 0;
}

void GenerateBall(int verts, XMFLOAT4 color, std::vector<XMFLOAT4> &circleVertices, std::vector<int> &circleIndices) {
	
	/*
	XMFLOAT4 center = {0, 0, 0, 1};
	XMFLOAT4 start = {1, 0, 0, 1};
	
	float alpha = 0;
	float delta = DirectX::XM_2PI / verts;
	
	circleVertices.push_back(center);
	circleVertices.push_back(color);

	for (int i = 0; i < verts; i++) {
		circleVertices.push_back(Vector4(cos(i*delta), sin(i*delta), 0.5, 1.0));
		circleVertices.push_back(Vector4(color));
		circleIndices.push_back(0);
		circleIndices.push_back(i+1);
		circleIndices.push_back(i+2);
	}


	circleIndices.push_back(0);
	circleIndices.push_back(verts);
	circleIndices.push_back(1);
*/
	circleVertices.push_back({ 0.0f, 0.0f, 0.0f, 1.0f });
	circleVertices.push_back(color);

	int i = 1;
	for (float alpha = 0.0f; alpha < 6.28f; alpha += 6.28f / verts, ++i)
	{
		XMFLOAT4 point = XMFLOAT4(cosf(alpha), sinf(alpha), 0.0f, 1.0f);
		circleVertices.push_back(point);
		circleVertices.push_back(color);
		circleIndices.push_back(0);
		circleIndices.push_back(i);
		int ind2 = (i + 1) % (verts + 1);
		if (ind2 == 0)
		{
			ind2 = 1;
		}
		circleIndices.push_back(ind2);
	}

}

