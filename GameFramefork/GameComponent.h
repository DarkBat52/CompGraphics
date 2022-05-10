#pragma once
#include <Windows.h>
#include <vector>
#include "Transform.h"

class GameComponent
{
public:

	GameComponent() = default;

	std::vector<GameComponent*> children;
	GameComponent* parent = nullptr;
	Transform transform;
	

	virtual HRESULT DestroyResources() 
	{
		return 0;
	};
	virtual HRESULT Draw() {
		return 0;
	};
	virtual HRESULT Initialize() {
		return 0;
	};
	HRESULT Reload() {
		return 0;
	};
	virtual HRESULT Update(float deltaTime) 
	{
		return 0;
	};

	virtual ~GameComponent() = default;

	HRESULT SetTransform(Transform t);

	virtual Transform GetWorldTransform() const;

	HRESULT SetParent(GameComponent* gc);

};

