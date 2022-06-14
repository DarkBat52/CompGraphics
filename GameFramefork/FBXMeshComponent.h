#pragma once
#include "MeshComponent.h"

#pragma pack(push, 4)
struct TexturedVertex
{
    Vector3 Position;
    Vector3 Normal;
    Vector2 TexCoord;
};
#pragma pack(pop)

class FBXMeshComponent :
    public MeshComponent
{
public:

    virtual HRESULT Initialize() override;
    HRESULT addVertex(TexturedVertex v);
    HRESULT addVertex(XMFLOAT4 v);
    HRESULT addIndex(int index);
    TexturedVertex& getVertex(size_t index);

    virtual HRESULT Draw() override;

protected:
    virtual std::vector<D3D11_INPUT_ELEMENT_DESC> returnInputElements() override;

private:
    std::vector<TexturedVertex> texturedVertices;

};

