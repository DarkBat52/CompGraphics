#pragma once

#include <wrl.h>
#include <d3d.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

#include "GameComponent.h"
#include "MathInclude.h"
#include "Transform.h"
#include "Game.h"

using namespace Microsoft::WRL;
using namespace DirectX;


class MeshComponent : public GameComponent
{

private:

	//ComPtr<ID3D11InputLayout> layout;

	//ComPtr<ID3D11PixelShader> pixelShader;
	//ComPtr<ID3DBlob> pixelShaderByteCode = nullptr;
	//

	//ComPtr<ID3D11VertexShader> vertexShader;
	//ComPtr<ID3DBlob> vertexShaderByteCode = nullptr;
	//
	//ComPtr<ID3D11RasterizerState> rastState;

	//ComPtr<ID3D11Buffer> vb;
	//ComPtr<ID3D11Buffer> ib;

	//Vector4 Color;

protected:

	ComPtr<ID3D11InputLayout> layout;

	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3DBlob> pixelShaderByteCode = nullptr;
	

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3DBlob> vertexShaderByteCode = nullptr;
	
	ComPtr<ID3D11RasterizerState> rastState;

	ComPtr<ID3D11Buffer> vb;
	ComPtr<ID3D11Buffer> ib;

	Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);

	std::vector<XMFLOAT4> vertices;
	std::vector<int> indices;

	HRESULT CompileShaders(const wchar_t * shaderFilePath);
	HRESULT CreateRastState(D3D11_CULL_MODE cullMode, D3D11_FILL_MODE fillMode);

	virtual std::vector<D3D11_INPUT_ELEMENT_DESC> returnInputElements();

	HRESULT createInputLayout(UINT numElements);

	virtual HRESULT createVertexBuffer();
	HRESULT createIndexBuffer();

	ComPtr<ID3D11ShaderResourceView> mAlbedoSRV = nullptr;

public:

	MeshComponent(int* indices, size_t indices_size, XMFLOAT4* vertices, size_t vertices_size);
	MeshComponent() = default;

	virtual HRESULT Initialize() override;
	virtual HRESULT SetVertsInds(int* indices, size_t indices_size, XMFLOAT4* vertices, size_t vertices_size);

	virtual HRESULT Draw() override;

	LitMaterial Mat;

	void SetAlbedoSRV(ComPtr<ID3D11ShaderResourceView> InAlbedoSRV);

	bool bCastShadow = true;


};

