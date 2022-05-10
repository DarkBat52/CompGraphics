#pragma once
#include <d3d11.h>
#include "SimpleMath.h"

#include <wrl.h>
#include <d3d.h>

#include <string>
#include <vector>
#include <iostream>
#include <DirectXMath.h>

#include "DisplayWin32.h"
#include "GameComponent.h"




using namespace DirectX;
using namespace Microsoft::WRL;

class InputDevice;
class Camera;

#pragma pack(push, 4)
struct CBPerObject
{
	DirectX::SimpleMath::Matrix ObjectToWorld;
	DirectX::SimpleMath::Vector4 Color;
};

#pragma pack(pop)

class Game
{
	friend int main();

public:

	virtual ~Game();

	DisplayWin32* Display = nullptr;

	std::vector<GameComponent*> Components;
	
	ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11RenderTargetView> RenderView;

	ComPtr<ID3D11Texture2D> DepthBuffer;
	ComPtr<ID3D11DepthStencilView> DepthStencilView;
	
	ComPtr<ID3D11DeviceContext> Context;
	ComPtr<ID3D11Device> Device;
	ComPtr<IDXGISwapChain> SwapChain;

	ComPtr<ID3D11DepthStencilState> DepthState;

	ComPtr<ID3D11ShaderResourceView> RenderSRV;

	float StartTime = 0;
	float TotalTime = 0;
	float PrevTime = 0;

	bool ScreenResized = false;

	//MulticastDelegate<const DirectX::SimpleMath::Vector2&> ScreenResized

	static Game* Instance;

	std::string Name;

	static Game* Get();


	ComPtr<ID3D11Buffer> PerObjectCB;

	std::vector<class CollisionComponent*> collisions;

	template<class T, class... ConstrArgs>
	T* CreateGameComponent(ConstrArgs&&... args)
	{
		T* comp = new T(std::forward<ConstrArgs>(args)...);
		Components.push_back(comp);

		if constexpr (std::is_base_of<class CollisionComponent, T>::value)
		{
			// add to collision array
			collisions.push_back(comp);
		}
		return comp;
	}


	

private:

	bool isExitRequested = false;
	bool isActive = false;

	DirectX::SimpleMath::Vector4 v;

	virtual HRESULT CreateBackBuffer();

	Camera* DefaultCamera;



protected:

	Game();

	virtual HRESULT PrepareResources();

	virtual HRESULT Draw();

	virtual HRESULT Update(float deltaTime);

	Color clearColor = { 0.945098f, 0.30588f, 0.3568627f, 1.0f };

	Camera* currentCamera = nullptr;

public:

	InputDevice* input;

	virtual HRESULT Run();

	virtual HRESULT HandleMessage();

	HRESULT Exit();

	ComPtr<ID3D11Buffer> GetPerObjectConstantBuffer();

	//virtual HRESULT Initialize();

	std::vector<CollisionComponent*> GetOverlappingComponents(const CollisionComponent& col);

	Camera* GetCurrentCamera();

};

