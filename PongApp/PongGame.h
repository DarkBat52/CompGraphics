#pragma once

#include "Game.h"

class MeshComponent;
class AABBCollisionComponent;

class PongGame :
	public Game
{

	friend int main();

public:

	std::vector<XMFLOAT4> vertices;

	HRESULT PrepareResources() override;
	HRESULT Update(float deltaTime) override;

private:

	PongGame() = default;

	const float baseBallSpeed = 0.5f;

	float advantage = -1.0f;

	float blockSpeed = 0.5f;
	float ballSpeed = baseBallSpeed;
	float ballAcceleration = 0.05;
	Vector3 ballDirection = { 1.0f, 0.0f, 0.0f };
	MeshComponent* leftBlock;
	MeshComponent* rightBlock;
	MeshComponent* ball;

	AABBCollisionComponent* ballCol;
	AABBCollisionComponent* leftBlockCol;
	AABBCollisionComponent* rightBlockCol;

	int player1score = 0;
	int player2score = 0;

	//Gate Collsions

	AABBCollisionComponent* leftGate;
	AABBCollisionComponent* rightGate;


	// lower border collssions
	AABBCollisionComponent* llborderCol;
	AABBCollisionComponent* lrborderCol;
	AABBCollisionComponent* lborderCol;

	// upper border collssions
	AABBCollisionComponent* ulborderCol;
	AABBCollisionComponent* urborderCol;
	AABBCollisionComponent* uborderCol;

	bool isIntersecting = false;

};

