#include "MeshComponent.h"
#include "Game.h"

#include <d3dcompiler.h>
#include <iostream>
#include "Camera.h"

HRESULT MeshComponent::CompileShaders(const wchar_t * shaderFilePath)
{
	HRESULT res = 0;
	
	ComPtr<ID3DBlob> errorVertexCode = nullptr;
	res = D3DCompileFromFile(L"../../Shaders/MyVeryFirstShader.hlsl",
		nullptr,
		nullptr,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		vertexShaderByteCode.GetAddressOf(),
		errorVertexCode.GetAddressOf());

	if (FAILED(res)) {
		// error message if the shader fails to compile
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// if the file could not be found
		else
		{
			MessageBox(Game::Get()->Display->hWnd, L"../../Shaders/MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);
		}

		return E_FAIL;
	}

	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

	Microsoft::WRL::ComPtr<ID3DBlob> errorPixelCode = nullptr;
	res = D3DCompileFromFile(L"../../Shaders/MyVeryFirstShader.hlsl",
		Shader_Macros,
		nullptr,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		pixelShaderByteCode.GetAddressOf(),
		&errorPixelCode);

	if (FAILED(res)) {
		// error message if the shader fails to compile
		if (errorPixelCode) {
			char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// if the file could not be found
		else
		{
			MessageBox(Game::Get()->Display->hWnd, L"../../Shaders/MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);
		}

		return E_FAIL;
	}

	res = Game::Get()->Device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader);

	res = Game::Get()->Device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader);

	return res;
}

MeshComponent::MeshComponent(int* indices, size_t indices_size, XMFLOAT4* vertices, size_t vertices_size)
{
	HRESULT res;

	for (size_t i = 0; i < vertices_size; ++i) {
		this->vertices.push_back(vertices[i]);
	}
	
	
	for (size_t i = 0; i < indices_size; ++i) {
		this->indices.push_back(indices[i]);
	}




}

HRESULT MeshComponent::Initialize() {

	HRESULT res = 0;

	CompileShaders(L"../../Shaders/MyVeryFirstShader.hlsl");


	ComPtr<ID3DBlob> errorVertexCode = nullptr;
	res = D3DCompileFromFile(L"../../Shaders/MyVeryFirstShader.hlsl",
		nullptr,
		nullptr,
		"VSMain",
		"vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		vertexShaderByteCode.GetAddressOf(),
		errorVertexCode.GetAddressOf());

	if (FAILED(res)) {
		// error message if the shader fails to compile
		if (errorVertexCode) {
			char* compileErrors = (char*)(errorVertexCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// if the file could not be found
		else
		{
			MessageBox(Game::Get()->Display->hWnd, L"../../Shaders/MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);
		}

		return E_FAIL;
	}

	D3D_SHADER_MACRO Shader_Macros[] = { "TEST", "1", "TCOLOR", "float4(0.0f, 1.0f, 0.0f, 1.0f)", nullptr, nullptr };

	Microsoft::WRL::ComPtr<ID3DBlob> errorPixelCode = nullptr;
	res = D3DCompileFromFile(L"../../Shaders/MyVeryFirstShader.hlsl",
		Shader_Macros,
		nullptr,
		"PSMain",
		"ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		pixelShaderByteCode.GetAddressOf(),
		&errorPixelCode);

	if (FAILED(res)) {
		// error message if the shader fails to compile
		if (errorPixelCode) {
			char* compileErrors = (char*)(errorPixelCode->GetBufferPointer());

			std::cout << compileErrors << std::endl;
		}
		// if the file could not be found
		else
		{
			MessageBox(Game::Get()->Display->hWnd, L"../../Shaders/MyVeryFirstShader.hlsl", L"Missing Shader File", MB_OK);
		}

		return E_FAIL;
	}

	Game::Get()->Device->CreateVertexShader(
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		nullptr, &vertexShader);

	Game::Get()->Device->CreatePixelShader(
		pixelShaderByteCode->GetBufferPointer(),
		pixelShaderByteCode->GetBufferSize(),
		nullptr, &pixelShader);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		D3D11_INPUT_ELEMENT_DESC {
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0},
		D3D11_INPUT_ELEMENT_DESC {
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0}
	};

	Game::Get()->Device->CreateInputLayout(
		inputElements,
		2,
		vertexShaderByteCode->GetBufferPointer(),
		vertexShaderByteCode->GetBufferSize(),
		layout.GetAddressOf());

	


	D3D11_BUFFER_DESC vertexBufDesc = {};
	vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufDesc.CPUAccessFlags = 0;
	vertexBufDesc.MiscFlags = 0;
	vertexBufDesc.StructureByteStride = 0;
	vertexBufDesc.ByteWidth = sizeof(DirectX::XMFLOAT4) * vertices.size();

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = &vertices[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	
	Game::Get()->Device->CreateBuffer(&vertexBufDesc, &vertexData, vb.GetAddressOf());


	

	D3D11_BUFFER_DESC indexBufDesc = {};
	indexBufDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufDesc.CPUAccessFlags = 0;
	indexBufDesc.MiscFlags = 0;
	indexBufDesc.StructureByteStride = 0;
	indexBufDesc.ByteWidth = sizeof(int) * indices.size();

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = &indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	
	Game::Get()->Device->CreateBuffer(&indexBufDesc, &indexData, ib.GetAddressOf());

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FillMode = D3D11_FILL_SOLID;

	res = Game::Get()->Device->CreateRasterizerState(&rastDesc, rastState.GetAddressOf());

	Game::Get()->Context->RSSetState(rastState.Get());

	return res;
}

HRESULT MeshComponent::Draw()
{
	HRESULT res = 0;

	Game* game = Game::Get();

	// Update constant buffer with world matrix

	// todo: rename matrix or create a new constant buffer to house WorldToClipMatrix
	CBPerObject cbData;
	cbData.ObjectToWorld = game->GetCurrentCamera()->GetWorldToClipMatrix().Transpose() * GetWorldTransform().GetTransformMatrixTransposed();
	cbData.Color = Color;

	D3D11_MAPPED_SUBRESOURCE resource = {};
	res = Game::Get()->Context->Map(Game::Get()->GetPerObjectConstantBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);

	memcpy(resource.pData, &cbData, sizeof(cbData));

	Game::Get()->Context->Unmap(Game::Get()->GetPerObjectConstantBuffer().Get(), 0);

	UINT strides[] = { 32 };
	UINT offsets[] = { 0 };

	Game::Get()->Context->IASetInputLayout(layout.Get());
	Game::Get()->Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Game::Get()->Context->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R32_UINT, 0);
	Game::Get()->Context->IASetVertexBuffers(0, 1, vb.GetAddressOf(), strides, offsets);
	Game::Get()->Context->VSSetShader(vertexShader.Get(), nullptr, 0);
	Game::Get()->Context->PSSetShader(pixelShader.Get(), nullptr, 0);


	Game::Get()->Context->DrawIndexed(indices.size(), 0, 0);
	
	return res;
}

