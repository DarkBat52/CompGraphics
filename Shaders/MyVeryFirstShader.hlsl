struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

struct DirLight
{
	float3 direction;
	float intensity;
	float4 color;
	matrix WorldToLightClip;
};

struct LitMaterial
{
	float ambientCoef;
	float specularCoef;
	float specularExponent;
	float diffuseCoef;
};

cbuffer CBPerObject : register(b1)
{
	matrix ObjectToWorld;
	float4 Color;
	matrix NormalO2W;
	LitMaterial Mat;
	matrix WorldToClip;
	DirLight dirLight;
	float3 CameraWorldPos;
};

PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;

	output.pos = mul(input.pos, ObjectToWorld);;
	output.col = input.col;

	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	float4 col = input.col;

	return col;
}