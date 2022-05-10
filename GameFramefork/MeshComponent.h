#pragma once

#include <wrl.h>
#include <d3d.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

#include "GameComponent.h"
#include "MathInclude.h"
#include "Transform.h"

using namespace Microsoft::WRL;
using namespace DirectX;


class MeshComponent : public GameComponent
{

private:

	ComPtr<ID3D11InputLayout> layout;

	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3DBlob> pixelShaderByteCode = nullptr;
	std::vector<XMFLOAT4> vertices;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3DBlob> vertexShaderByteCode = nullptr;
	std::vector<int> indices;
	
	ComPtr<ID3D11RasterizerState> rastState;

	ComPtr<ID3D11Buffer> vb;
	ComPtr<ID3D11Buffer> ib;

	Vector4 Color;

	HRESULT CompileShaders(const wchar_t * shaderFilePath);

public:

	MeshComponent(int* indices, size_t indices_size, XMFLOAT4* vertices, size_t vertices_size);
	virtual HRESULT Initialize() override;
	virtual HRESULT Draw() override;




};

