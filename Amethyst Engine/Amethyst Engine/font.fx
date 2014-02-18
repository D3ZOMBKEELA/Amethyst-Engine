matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
Texture2D shaderTexture;

float4 pixelColor;

SamplerState SampleType
{
    Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

BlendState AlphaBlendingState
{
    BlendEnable[0] = TRUE;
	DestBlend = INV_SRC_ALPHA;
};

struct VertexInputType
{
    float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

PixelInputType FontVertexShader(VertexInputType input)
{
    PixelInputType output;

	input.position.w = 1.0F;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	return output;
}

float4 FontPixelShader(PixelInputType input) : SV_Target
{
    float4 color;

	color = shaderTexture.Sample(SampleType, input.tex);

	if(color.r == 0.0F)
	{
	    color.a = 0.0F;
	}
	else
	{
	    color.a = 1.0F;
		color = color * pixelColor;
	}

	return color;
}

technique10 FontTechnique
{
    pass pass0
	{
	    SetBlendState(AlphaBlendingState, float4(0.0F, 0.0F, 0.0F, 0.0F), 0xFFFFFFFF);
		SetVertexShader(CompileShader(vs_4_0, FontVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, FontPixelShader()));
		SetGeometryShader(NULL);
	}
}