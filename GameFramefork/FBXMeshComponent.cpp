#include "FBXMeshComponent.h"
#include "Camera.h"

HRESULT FBXMeshComponent::Initialize()
{
	
	HRESULT res = 0;

	res = CompileShaders(L"../../Shaders/MyVerySecondShader.hlsl");
	res = createInputLayout(3);
	res = createVertexBuffer();
	res = createIndexBuffer();
	res = CreateRastState(D3D11_CULL_NONE, D3D11_FILL_SOLID);
	
	return 0;
}

HRESULT FBXMeshComponent::addVertex(TexturedVertex v)
{	
	HRESULT res = 0;
	texturedVertices.push_back(v);
	return res;
}

HRESULT FBXMeshComponent::addVertex(XMFLOAT4 v)
{	
	vertices.push_back(v);
	return 0;
}

HRESULT FBXMeshComponent::addIndex(int index)
{
	HRESULT res = 0;
	indices.push_back(index);
	return res;
}

TexturedVertex& FBXMeshComponent::getVertex(size_t index)
{	
	return texturedVertices[index];
}

HRESULT FBXMeshComponent::Draw()
{
	HRESULT res = 0;

	Game* game = Game::Get();

	CBPerObject cbData;
	cbData.ObjectToWorld = game->GetCurrentCamera()->GetWorldToClipMatrix().Transpose() * GetWorldTransform().GetTransformMatrixTransposed();
	cbData.Color = Color;
	cbData.WorldToClip = game->GetCurrentCamera()->GetWorldToClipMatrix();
	cbData.CameraWorldPos = game->GetCurrentCamera()->GetWorldTransform().Position;
	cbData.NormalO2W = GetWorldTransform().GetNormalMatrixTransposed();
	cbData.Mat = { 0.1f, 0.5f, 1.0f, 0.8f };
	cbData.dirLight = DirLight();

	ComPtr<ID3D11SamplerState> defaultSamplerState = game->GetDefaultSamplerState();

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

	//textures

	if (mAlbedoSRV.Get() != nullptr)
	{
		game->Context->PSSetShaderResources(0, 1, mAlbedoSRV.GetAddressOf());
		game->Context->PSSetSamplers(0, 1, defaultSamplerState.GetAddressOf());
	}


	Game::Get()->Context->DrawIndexed(indices.size(), 0, 0);

	
	return res;
}

std::vector<D3D11_INPUT_ELEMENT_DESC> FBXMeshComponent::returnInputElements()
{

	std::vector <D3D11_INPUT_ELEMENT_DESC> inputElementsVector;

	inputElementsVector.push_back(
		D3D11_INPUT_ELEMENT_DESC
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		});

	inputElementsVector.push_back(
		D3D11_INPUT_ELEMENT_DESC
		{
			"NORMAL",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	);
	
	inputElementsVector.push_back(
		D3D11_INPUT_ELEMENT_DESC
		{
			"TEXCOORD",
			0,
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	);


	return inputElementsVector;
}


