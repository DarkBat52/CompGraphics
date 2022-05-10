#include "TriApp.h"
#include "MeshComponent.h"

TriApp::TriApp() : Game()
{
	
}

HRESULT TriApp::PrepareResources()
{
	XMFLOAT4 vertices[8] = {
		XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
		XMFLOAT4(-0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT4(0.5f, -0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f),
		XMFLOAT4(-0.5f, 0.5f, 0.5f, 1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	};

	int indices[] = { 0, 1, 2, 1, 0, 3 };

	GameComponent* mc = new MeshComponent(indices, 6, vertices, 8);

	TriApp::Get()->Components.push_back(mc);

	HRESULT res = Game::PrepareResources();

	



	return 0;
}
