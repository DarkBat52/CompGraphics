#pragma once
#include "Game.h"

class MeshLoader;
class MeshComponent;
class FBXMeshComponent;
class SphereCollisionComponent;

class KatamariGame :
	public Game
{
private:

    HRESULT PrepareResources() override;
    HRESULT Update(float deltaTime) override;

    class CameraController* camControl = nullptr;
    class CameraOrbitController* camOrbitControl = nullptr;

    MeshLoader* meshLoader = nullptr;
    MeshLoader* chessLoader = nullptr;

    bool isIntersecting = false;


    // OBJECTS \\
    
    FBXMeshComponent* player = nullptr;
    ComPtr<ID3D11Resource> testTexResource;
    ComPtr<ID3D11ShaderResourceView> testTexSRV;

    FBXMeshComponent* chessBoard = nullptr;
    ComPtr<ID3D11Resource> cbTexResource;
    ComPtr<ID3D11ShaderResourceView> cbTexSRV;

    FBXMeshComponent* pawn1 = nullptr;
    ComPtr<ID3D11Resource> pawnTexResource;
    ComPtr<ID3D11ShaderResourceView> pawnTexSRV;

    FBXMeshComponent* pawn2 = nullptr;
    FBXMeshComponent* pawn3 = nullptr;
    FBXMeshComponent* pawn4 = nullptr;

    FBXMeshComponent* knight1 = nullptr;
    FBXMeshComponent* knight2 = nullptr;

    FBXMeshComponent* bishop1 = nullptr;
    FBXMeshComponent* bishop2 = nullptr;

    FBXMeshComponent* queen = nullptr;
    FBXMeshComponent* king = nullptr;


    // COLLISIONS \\

    SphereCollisionComponent* playerCol = nullptr;

    SphereCollisionComponent* pawn1Col = nullptr;
    SphereCollisionComponent* pawn2Col = nullptr;
    SphereCollisionComponent* pawn3Col = nullptr;
    SphereCollisionComponent* pawn4Col = nullptr;

    SphereCollisionComponent* knight1Col = nullptr;
    SphereCollisionComponent* knight2Col = nullptr;

    SphereCollisionComponent* bishop1Col = nullptr;
    SphereCollisionComponent* bishop2Col = nullptr;

    SphereCollisionComponent* queenCol = nullptr;
    SphereCollisionComponent* kingCol = nullptr;


};

