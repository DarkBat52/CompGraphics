#pragma once
#include "Game.h"

class MeshLoader;
class MeshComponent;
class FBXMeshComponent;

class KatamariGame :
	public Game
{
private:

    HRESULT PrepareResources() override;
    HRESULT Update(float deltaTime) override;

    class CameraController* camControl = nullptr;
    class CameraOrbitController* camOrbitControl = nullptr;

    MeshLoader* meshLoader = nullptr;


    // OBJECTS \\
    
    FBXMeshComponent* testfbx = nullptr;
    ComPtr<ID3D11Resource> testTexResource;
    ComPtr<ID3D11ShaderResourceView> testTexSRV;
};

