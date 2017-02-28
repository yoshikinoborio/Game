/*!
 *@brief	簡単なディフューズライティングのシェーダー。
 */


float4x4 g_worldMatrix;			//ワールド行列。
float4x4 g_viewMatrix;			//ビュー行列。
float4x4 g_projectionMatrix;	//プロジェクション行列。
float4x4 g_rotationMatrix;		//回転行列。法線を回転させるために必要になる。ライティングするなら必須。
float3 vEyePos;				//カメラの位置(ろーかるざひょう)

#define DIFFUSE_LIGHT_NUM	4		//ディフューズライトの数。
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//ディフューズライトの方向。
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//ディフューズライトのカラー。
float4	g_ambientLight;								//環境光。

texture g_diffuseTexture;		//ディフューズテクスチャ。
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float3	normal	: NORMAL0;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
	float3	normal	: TEXCOORD1;
	float3  Eye		: TEXCOORD2;
};

/*!
 *@brief	頂点シェーダー。
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	//座標変換
	float4 pos;
	pos = mul(In.pos, g_worldMatrix);		//モデルのローカル空間からワールド空間に変換。
	pos = mul(pos, g_viewMatrix);			//ワールド空間からビュー空間に変換。
	pos = mul(pos, g_projectionMatrix);	//ビュー空間から射影空間に変換。
	Out.pos = pos;
	//拡散光+環境光
	float amb = -g_diffuseLightDirection[0].w;
	float3 L = -g_diffuseLightDirection[0].xyz;//ローカルのライト座標
	Out.color = In.color * max(amb, dot(In.normal, -g_diffuseLightDirection[0].xyz));
	//鏡面反射用のベクトル
	Out.Eye = vEyePos - pos.xyz;

	Out.uv = In.uv;
	Out.normal = mul(In.normal, g_rotationMatrix);	//法線を回す。
	return Out;
}
/*!
 *@brief	ピクセルシェーダー。
 */
float4 PSMain(VS_OUTPUT In) : COLOR
{
	//ライトを計算。
	//float4 lig = 0.0f;
	//float t;
	//t = dot(-g_diffuseLightDirection[0].xyz, In.normal.xyz);
	//lig = max(0.0f, t);
	//lig.xyz = g_diffuseLightColor[0].xyz * t;

	float4 color = tex2D( g_diffuseTextureSampler, In.uv );
	//color.xyz *= lig;

	//float3 L = -g_diffuseLightDirection[0].xyz;
	//float3 H = normalize(L + normalize(In.Eye));//ハーフベクトル	
	//float3 N = normalize(In.normal);

	//In.color += color;

	//return In.color + pow(max(0.0f, dot(N, H)), 10.0f);
	return color;

}

technique SkinModel
{
	pass p0
	{
		VertexShader 	= compile vs_2_0 VSMain();
		PixelShader 	= compile ps_2_0 PSMain();
	}
}