matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;

struct VertexInputType
{
    float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float4 color : COLOR;
};

PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;

	input.position.w = 1.0F;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.color = input.color;

	return output;
}

float4 ColorPixelShader(PixelInputType input) : SV_Target
{
    return input.color;
}

technique10 ColorTechnique
{
    pass pass0
	{
	    SetVertexShader(CompileShader(vs_4_0, ColorVertexShader()));
		SetPixelShader(CompileShader(ps_4_0, ColorPixelShader()));
		SetGeometryShader(NULL);
	}
}