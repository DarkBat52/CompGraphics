#include "Game.h"
#include <time.h>
#include <chrono>
#include <iostream>
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include "InputDevice.h"
#include "CollisionComponent.h"
#include "Camera.h"

using namespace std::chrono;

Game* Game::Instance = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

Game::~Game()
{
	for (GameComponent* g : Components) {
		delete g;
	}
	delete Display;
}

Game* Game::Get()
{
	return Instance;
}

Game::Game()
{
	StartTime = (float) duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	//PrevTime = StartTime;

	Instance = this;

	Display = new DisplayWin32(WndProc);

}

HRESULT Game::CreateBackBuffer()
{

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = Display->ClientWidth;
	swapDesc.BufferDesc.Height = Display->ClientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = Display->hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	HRESULT res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		SwapChain.GetAddressOf(),
		Device.GetAddressOf(),
		nullptr,
		Context.GetAddressOf());

	 res = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	 res = Device->CreateRenderTargetView(backBuffer.Get(), nullptr, RenderView.GetAddressOf());

	 D3D11_TEXTURE2D_DESC descDepth;
	 descDepth.Width = Display->ClientWidth;
	 descDepth.Height = Display->ClientHeight;
	 descDepth.MipLevels = 1;
	 descDepth.ArraySize = 1;
	 descDepth.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	 descDepth.SampleDesc.Count = 1;
	 descDepth.SampleDesc.Quality = 0;
	 descDepth.Usage = D3D11_USAGE_DEFAULT;
	 descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	 descDepth.CPUAccessFlags = 0;
	 descDepth.MiscFlags = 0;
	 res = Device->CreateTexture2D(&descDepth, NULL, DepthBuffer.GetAddressOf());

	 res = Device->CreateDepthStencilView(DepthBuffer.Get(), // Depth stencil texture
		 nullptr, // Depth stencil desc
		 DepthStencilView.GetAddressOf());  // [out] Depth stencil view


	return res;
}

HRESULT Game::PrepareResources()
{

	HRESULT res = 0;

	input = new InputDevice();

	CreateBackBuffer();

	// Create shadowmap sampler state
	D3D11_SAMPLER_DESC smSampDesc;
	ZeroMemory(&smSampDesc, sizeof(smSampDesc));
	smSampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	smSampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	smSampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	smSampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	smSampDesc.BorderColor[0] = 1.0f;
	smSampDesc.BorderColor[1] = 1.0f;
	smSampDesc.BorderColor[2] = 1.0f;
	smSampDesc.BorderColor[3] = 1.0f;
	smSampDesc.ComparisonFunc = D3D11_COMPARISON_LESS;
	smSampDesc.MinLOD = 0;
	smSampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	Device->CreateSamplerState(&smSampDesc, ShadowmapSamplerState.GetAddressOf());

	// Create shadowmap texture
	D3D11_TEXTURE2D_DESC descSM;
	descSM.Width = 2048;
	descSM.Height = 2048;
	descSM.MipLevels = 1;
	descSM.ArraySize = 1;
	descSM.Format = DXGI_FORMAT_R32_TYPELESS;
	descSM.SampleDesc.Count = 1;
	descSM.SampleDesc.Quality = 0;
	descSM.Usage = D3D11_USAGE_DEFAULT;
	descSM.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	descSM.CPUAccessFlags = 0;
	descSM.MiscFlags = 0;
	res = Device->CreateTexture2D(&descSM, NULL, ShadowMapTex.GetAddressOf());

	// Create the depth stencil view for shadowmap
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	res = Device->CreateDepthStencilView(ShadowMapTex.Get(), &descDSV, ShadowMapView.GetAddressOf());

	D3D11_SHADER_RESOURCE_VIEW_DESC smSRVDesc;
	//ZeroMemory(&smSRVDesc, sizeof(smSRVDesc));
	smSRVDesc.Format = DXGI_FORMAT_R32_FLOAT;
	smSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	smSRVDesc.Texture2D.MostDetailedMip = 0;
	smSRVDesc.Texture2D.MipLevels = descSM.MipLevels;
	Device->CreateShaderResourceView(ShadowMapTex.Get(), &smSRVDesc, ShadowMapSRV.GetAddressOf());

	createDefaultSamplerState();



	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(Game::Get()->Display->ClientWidth);
	viewport.Height = static_cast<float>(Game::Get()->Display->ClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	Context->RSSetViewports(1, &viewport);
	Context->OMSetRenderTargets(1, RenderView.GetAddressOf(), DepthStencilView.Get());



	//Create per object constant buffer
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(CBPerObject);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	res = Device->CreateBuffer(&cbDesc, nullptr,
		PerObjectCB.GetAddressOf());

	Context->VSSetConstantBuffers(1, 1, PerObjectCB.GetAddressOf());
	Context->PSSetConstantBuffers(1, 1, PerObjectCB.GetAddressOf());

	return res;
}

HRESULT Game::Draw()
{	

	bIsRenderingShadowMap = true;
	//Context->PSSetShaderResources(1, 1, nullptr);
	Context->OMSetRenderTargets(0, nullptr, ShadowMapView.Get());
	{
		D3D11_VIEWPORT viewport = {};
		viewport.Width = 2048;
		viewport.Height = 2048;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		Context->RSSetViewports(1, &viewport);
		Context->ClearDepthStencilView(ShadowMapView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

		for (GameComponent* g : Components) {
			g->Draw();
		}

	}

	bIsRenderingShadowMap = false;

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<float>(Game::Get()->Display->ClientWidth);
	viewport.Height = static_cast<float>(Game::Get()->Display->ClientHeight);
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	Context->RSSetViewports(1, &viewport);

	Context->OMSetRenderTargets(1, RenderView.GetAddressOf(), DepthStencilView.Get());

	float color[] = { 0.945098f, 0.30588f, 0.3568627f, 1.0f };
	//float color[] = { 0.945098f, 0.30588f, 0.3568627f, 1.0f }; // pong pink
	Context->ClearRenderTargetView(RenderView.Get(), clearColor);
	Context->ClearDepthStencilView(DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	

	HRESULT res = 0;
	for (GameComponent* g : Components) {
		res = g->Draw();
	}

	res = SwapChain->Present(1, 0);

	return res;
}

HRESULT Game::Update(float deltaTime)
{
	TotalTime += deltaTime;

	input->PreInputProcess();
	HRESULT res = HandleMessage();



	for (GameComponent* g : Components) {
		res = g->Update(deltaTime);
	}





	return res;
}

void Game::createDefaultSamplerState()
{
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	Device->CreateSamplerState(&sampDesc, DefaultSamplerState.GetAddressOf());
}

HRESULT Game::Run()
{
	HRESULT res = PrepareResources();

	for (GameComponent* g : Components) {
		g->Initialize();
	}

	auto PrevTime = std::chrono::steady_clock::now();



	while (!isExitRequested) {

		auto now = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - PrevTime).count() / 1000000.0f;
		PrevTime = now;
		res = Update(deltaTime);
		res = Draw();
	}

	return 0;
}

HRESULT Game::HandleMessage()
{	
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Exit on Windows signal
	if (msg.message == WM_QUIT) {
		Exit();
	}

	return 0;
}

HRESULT Game::Exit()
{
	isExitRequested = true;
	return 0;
}

ComPtr<ID3D11Buffer> Game::GetPerObjectConstantBuffer()
{
	return PerObjectCB;
}

std::vector<CollisionComponent*> Game::GetOverlappingComponents(const CollisionComponent& col)
{

	std::vector<CollisionComponent*> cols;

	for (CollisionComponent* comp : collisions) {
		if (comp != nullptr && comp != &col && col.doesIntersect(*comp)) {
			cols.push_back(comp);
		}
	}

	return cols;
}

Camera* Game::GetCurrentCamera()
{
	if (currentCamera != nullptr) {
		return currentCamera;
	}

	if (DefaultCamera == nullptr) {
		DefaultCamera = CreateGameComponent<Camera>();
		DefaultCamera->UpdateProjectionMatrixOrthographic(2, 2, 1, -1);
	}
	return DefaultCamera;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) 
{
	return Game::Get()->Instance->input->HandleMessage(hwnd, umessage, wparam, lparam);
}