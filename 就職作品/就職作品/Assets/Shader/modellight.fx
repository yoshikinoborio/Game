/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */

//#include "LightingFunction.h"

//スキン行列。
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;//プロジェクション行列。
float		g_numBone;			//骨の数。

float4x4	g_worldMatrix;			//!<ワールド行列。
float4x4 	g_viewMatrix;			//ビュー行列。
float4x4	g_rotationMatrix;		//!<回転行列。
float4x4	g_viewMatrixRotInv;		//!<カメラの回転行列の逆行列。
float3 		vEyePos;			//カメラの位置。	

#define DIFFUSE_LIGHT_NUM	4		//ディフューズライトの数。
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//ディフューズライトの方向。
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//ディフューズライトのカラー。
float4	g_ambientLight;
int     g_ShadowReceiverFlag;		//影を落とすフラグ。
float4x4 g_mLVP;			//ライトビュープロジェクション行列。 //環境光。

//bool g_isHasNormalMap;			//法線マップ保持している？

texture g_diffuseTexture;		//ディフューズテクスチャ。
texture g_shadowTexture;		//シャドウ用のテクスチャ。
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};

sampler g_shadowTextureSampler = 
sampler_state
{
	Texture = <g_shadowTexture>;
    MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
    AddressU = CLAMP;
	AddressV = CLAMP;
};


//法線マップ。
//texture g_normalTexture;		//法線マップ。
//sampler g_normalMapSampler = 
//sampler_state
//{
//	Texture = <g_normalTexture>;
//    MipFilter = NONE;
//    MinFilter = NONE;
//   MagFilter = NONE;
//    AddressU = Wrap;
//	AddressV = Wrap;
//};


/*!
 * @brief	入力頂点
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
	float4  BlendIndices    : BLENDINDICES;
	float4  color		: COLOR0;
	float4  normal		: NORMAL0;
	float2	uv		: TEXCOORD1;
	//float3  Normal          : NORMAL;
//  float3  Tangent	　　: TANGENT;		//接ベクトル。
    float3  Tex0            : TEXCOORD0;
};

/*!
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{
	float4  Pos     : POSITION;
	float4	color	: COLOR0;
	float2	uv	: TEXCOORD1;
	float3	normal	: TEXCOORD2;
	float3  Eye	: TEXCOORD3;
//      float3  Normal			: NORMAL;
        float2  Tex0   			: TEXCOORD0;
//      float3	Tangent			: TEXCOORD1;	//接ベクトル。
	float4  lightViewPos_1	: TEXCOORD4;
};
/*!
 *@brief	ワールド座標とワールド法線をスキン行列から計算する。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos)//, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	//Normal = 0.0f;
	//Tangent = 0.0f;
	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//ブレンドレート。
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    float LastWeight = 0.0f;
    for (int iBone = 0; iBone < g_numBone-1; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
       //Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        //Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 
    
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    //Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    //Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
}
/*!
 *@brief	ワールド座標とワールド法線を計算。
 *@param[in]	In		入力頂点。
 *@param[out]	Pos		ワールド座標の格納先。
 *@param[out]	Normal	ワールド法線の格納先。
 *@param[out]	Tangent	ワールド接ベクトルの格納先。
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos)//, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	//Normal = mul(In.Normal, g_rotationMatrix );
	//Tangent = mul(In.Tangent, g_rotationMatrix );
}
/*!
 *@brief	頂点シェーダー。
 *@param[in]	In			入力頂点。
 *@param[in]	hasSkin		スキンあり？
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos;//, Normal, Tangent;
	if(hasSkin){
		//スキンあり。
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos);//, Normal, Tangent );
	}else{
		//スキンなし。
		CalcWorldPosAndNormal(In, Pos);//, Normal, Tangent );
	}
  
	float4 worldpos = mul(In.Pos,g_worldMatrix);
	worldpos.w = 1.0f;

	o.lightViewPos_1 = mul(worldpos,g_mLVP );

	o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);	//ビュー空間から射影空間に変換。
    //拡散光+環境光。
    float amb = -g_diffuseLightDirection[0].w;
    float3 L = -g_diffuseLightDirection[0].xyz;//ローカルのライト座標。
    //o.color = In.color * max(amb, dot(In.normal, -g_diffuseLightDirection[0].xyz));
    //鏡面反射用のベクトル
    o.Eye = vEyePos - Pos.xyz;

    o.uv = In.uv;
    o.normal = mul(In.normal, g_rotationMatrix);	//法線を回す。
    //o.Normal = normalize(Normal);
    //o.Tangent = normalize(Tangent);
    o.Tex0 = In.Tex0;
	return o;
}
/*!
 * @brief	ピクセルシェーダー。
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 posInLVP = In.lightViewPos_1;
	posInLVP.xyz /= posInLVP.w;

	//uv座標に変換。
	float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
	float2 shadow_val = 1.0f;

	//ライトを計算。
	float4 lig = 0.0f;
	{
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			lig.xyz += max(0.0f, dot(In.normal.xyz, -g_diffuseLightDirection[i].xyz))
				* g_diffuseLightColor[i].xyz;
			//スペキュラを計算。
			float3 L = -g_diffuseLightDirection[i].xyz;
				float3 H = normalize(L + normalize(In.Eye));//ハーフベクトル。
				float3 N = normalize(In.normal);
				lig.xyz += pow(max(0.0f, dot(N, H)), 10.0f);
		}
		lig += g_ambientLight;
	}
	float4 color = tex2D(g_diffuseTextureSampler, In.Tex0);

	if(g_ShadowReceiverFlag==true)
	{
		if ((shadowMapUV.x > 0.0f && shadowMapUV.x <1.0f) && (shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f))
		{
			color *= tex2D(g_shadowTextureSampler, shadowMapUV);
		}
	}
	color.xyz *= lig;
	return color;
}

/*!
*@brief	影用ピクセルシェーダー。
*/
float4 PSDrowToShadowMapMain(VS_OUTPUT In) : COLOR
{
	
	return float4(0.5f,0.5f,0.5f,1.0f);
}

/*!
 *@brief	スキンありモデル用のテクニック。
 */
technique SkinModel
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(true);
        PixelShader = compile ps_3_0 PSMain();
    }
}
/*!
 *@brief	スキンなしモデル用のテクニック。
 */
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

/*
*@brief		スキンあり影用のテクニック
*/
technique SkinModelDrowToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSDrowToShadowMapMain();
	}
}

/*!
*@brief	スキンなし影モデル用のテクニック。
*/
technique NoSkinModelDrowToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSDrowToShadowMapMain();
	}
}