/*!
 * @brief	�X�L�����f���V�F�[�_�[�B(4�{�[���X�L�j���O)
 */

//#include "LightingFunction.h"

//�X�L���s��B
#define MAX_MATRICES  26
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;
float4x4    g_mViewProj : VIEWPROJECTION;//�v���W�F�N�V�����s��B
float		g_numBone;			//���̐��B

float4x4	g_worldMatrix;			//!<���[���h�s��B
float4x4 	g_viewMatrix;			//�r���[�s��B
float4x4	g_rotationMatrix;		//!<��]�s��B
float4x4	g_viewMatrixRotInv;		//!<�J�����̉�]�s��̋t�s��B
float3 		vEyePos;			//�J�����̈ʒu�B	

#define DIFFUSE_LIGHT_NUM	4		//�f�B�t���[�Y���C�g�̐��B
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//�f�B�t���[�Y���C�g�̕����B
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̃J���[�B
float4	g_ambientLight;
int     g_ShadowReceiverFlag;		//�e�𗎂Ƃ��t���O�B
float4x4 g_mLVP;			//���C�g�r���[�v���W�F�N�V�����s��B //�����B

//bool g_isHasNormalMap;			//�@���}�b�v�ێ����Ă���H

texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
texture g_shadowTexture;		//�V���h�E�p�̃e�N�X�`���B
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


//�@���}�b�v�B
//texture g_normalTexture;		//�@���}�b�v�B
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
 * @brief	���͒��_
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
//  float3  Tangent	�@�@: TANGENT;		//�ڃx�N�g���B
    float3  Tex0            : TEXCOORD0;
};

/*!
 * @brief	�o�͒��_�B
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
//      float3	Tangent			: TEXCOORD1;	//�ڃx�N�g���B
	float4  lightViewPos_1	: TEXCOORD4;
};
/*!
 *@brief	���[���h���W�ƃ��[���h�@�����X�L���s�񂩂�v�Z����B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormalFromSkinMatrix( VS_INPUT In, out float3 Pos)//, out float3 Normal, out float3 Tangent )
{
	Pos = 0.0f;
	//Normal = 0.0f;
	//Tangent = 0.0f;
	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//�u�����h���[�g�B
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
 *@brief	���[���h���W�ƃ��[���h�@�����v�Z�B
 *@param[in]	In		���͒��_�B
 *@param[out]	Pos		���[���h���W�̊i�[��B
 *@param[out]	Normal	���[���h�@���̊i�[��B
 *@param[out]	Tangent	���[���h�ڃx�N�g���̊i�[��B
 */
void CalcWorldPosAndNormal( VS_INPUT In, out float3 Pos)//, out float3 Normal, out float3 Tangent )
{
	Pos = mul(In.Pos, g_worldMatrix );
	//Normal = mul(In.Normal, g_rotationMatrix );
	//Tangent = mul(In.Tangent, g_rotationMatrix );
}
/*!
 *@brief	���_�V�F�[�_�[�B
 *@param[in]	In			���͒��_�B
 *@param[in]	hasSkin		�X�L������H
 */
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	float3 Pos;//, Normal, Tangent;
	if(hasSkin){
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos);//, Normal, Tangent );
	}else{
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal(In, Pos);//, Normal, Tangent );
	}
  
	float4 worldpos = mul(In.Pos,g_worldMatrix);
	worldpos.w = 1.0f;

	o.lightViewPos_1 = mul(worldpos,g_mLVP );

	o.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
    //�g�U��+�����B
    float amb = -g_diffuseLightDirection[0].w;
    float3 L = -g_diffuseLightDirection[0].xyz;//���[�J���̃��C�g���W�B
    //o.color = In.color * max(amb, dot(In.normal, -g_diffuseLightDirection[0].xyz));
    //���ʔ��˗p�̃x�N�g��
    o.Eye = vEyePos - Pos.xyz;

    o.uv = In.uv;
    o.normal = mul(In.normal, g_rotationMatrix);	//�@�����񂷁B
    //o.Normal = normalize(Normal);
    //o.Tangent = normalize(Tangent);
    o.Tex0 = In.Tex0;
	return o;
}
/*!
 * @brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( VS_OUTPUT In ) : COLOR
{
	float4 posInLVP = In.lightViewPos_1;
	posInLVP.xyz /= posInLVP.w;

	//uv���W�ɕϊ��B
	float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
	float2 shadow_val = 1.0f;

	//���C�g���v�Z�B
	float4 lig = 0.0f;
	{
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			lig.xyz += max(0.0f, dot(In.normal.xyz, -g_diffuseLightDirection[i].xyz))
				* g_diffuseLightColor[i].xyz;
			//�X�y�L�������v�Z�B
			float3 L = -g_diffuseLightDirection[i].xyz;
				float3 H = normalize(L + normalize(In.Eye));//�n�[�t�x�N�g���B
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
*@brief	�e�p�s�N�Z���V�F�[�_�[�B
*/
float4 PSDrowToShadowMapMain(VS_OUTPUT In) : COLOR
{
	
	return float4(0.5f,0.5f,0.5f,1.0f);
}

/*!
 *@brief	�X�L�����胂�f���p�̃e�N�j�b�N�B
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
 *@brief	�X�L���Ȃ����f���p�̃e�N�j�b�N�B
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
*@brief		�X�L������e�p�̃e�N�j�b�N
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
*@brief	�X�L���Ȃ��e���f���p�̃e�N�j�b�N�B
*/
technique NoSkinModelDrowToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSDrowToShadowMapMain();
	}
}