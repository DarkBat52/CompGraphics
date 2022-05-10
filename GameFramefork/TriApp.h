#pragma once
#include "Game.h"


class TriApp :
    public Game
{
    friend int main();

public:

    std::vector<XMFLOAT4> vertices;

private:
    
    TriApp();

public:

    HRESULT PrepareResources() override;

};

