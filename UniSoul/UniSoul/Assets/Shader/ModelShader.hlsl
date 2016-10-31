
float4x4 g_worldMatrix;
float4x4 g_viewMatrix;
float4x4 g_projectionMatrix;

texture g_Texture;
sampler g_TextureSampler =
sampler_state
{
	Texture = <g_Texture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_INPUT
{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};
/*!
*@brief	頂点シェーダー。
*@param[in]	In			入力頂点。
*@param[in]	hasSkin		スキンあり？
*/
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	//スキンなし。
	o.pos = mul(float4(In.pos.xyz, 1.0f), g_worldMatrix);
	o.pos = mul(float4(o.pos.xyz, 1.0f), g_viewMatrix);
	o.pos = mul(float4(o.pos.xyz, 1.0f), g_projectionMatrix);
	o.uv = In.uv;
	return o;
}

float4 PSMain(VS_OUTPUT In):COLOR
{
	float4 color = tex2D(g_TextureSampler, In.uv);
	color.w = 1.0f;
	return color;
}

technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
