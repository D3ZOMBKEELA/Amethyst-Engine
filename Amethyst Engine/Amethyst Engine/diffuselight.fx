matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
Texture2D shaderTexture;

float4 diffuseColor;
float3 lightDirection;

SamplerState SampleType
{
    Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VertexInputType
{
    float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

PixelInputType LightVertexShader(VertexInputType input)
{
    PixelInputType output;

	input.position.w = 1.0F;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	output.normal = mul(input.normal, (float3x3)worldMatrix);

	output.normal = normalize(output.normal);

	return output;
}

float4 LightPixelShader(PixelInputType input) : SV_Target
{
    float4 textureColor;
	float3 lightDir;
	float lightIntensity;
	float4 color;

	textureColor = shaderTexture.Sample(SampleType, input.tex);

	lightDir = -lightDirection;

	lightIntensity = saturate(dot(input.normal, lightDir));

	color = saturate(diffuseColor * lightIntensity);

	color = color * textureColor;

	return color;
}

technique10 DiffuseLightTechnique
{
    pass pass0
	{
	    SetVertexShader(CompileShader(vs_4_0, LightVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, LightPixelShader()));
		SetGeometryShader(NULL);
	}
}