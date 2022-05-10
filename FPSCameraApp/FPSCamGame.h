#pragma once

#include "Game.h"

class MeshComponent;

class FPSCamGame :
    public Game
{

    HRESULT PrepareResources() override;
    HRESULT Update(float deltaTime) override;

    class CameraController* camControl = nullptr;
    class CameraOrbitController* camOrbitControl = nullptr;


    // CELESTIAL OBJECTS \\

    MeshComponent* sun;
    MeshComponent* mercury;
    MeshComponent* venus;
    MeshComponent* earth;
    MeshComponent* moon;
    MeshComponent* mars;
    MeshComponent* jupiter;
    MeshComponent* saturn;
    MeshComponent* uranus;
    MeshComponent* neptune;

    // CUBES \\

    MeshComponent* cube;
    MeshComponent* cube2;

};