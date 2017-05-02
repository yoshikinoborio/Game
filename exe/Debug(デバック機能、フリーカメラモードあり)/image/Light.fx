/*!
 *@brief	�ȒP�ȃf�B�t���[�Y���C�e�B���O�̃V�F�[�_�[�B
 */


float4x4 g_worldMatrix;			//���[���h�s��B
float4x4 g_viewMatrix;			//�r���[�s��B
float4x4 g_projectionMatrix;	//�v���W�F�N�V�����s��B
float4x4 g_rotationMatrix;		//��]�s��B�@������]�����邽�߂ɕK�v�ɂȂ�B���C�e�B���O����Ȃ�K�{�B
float3 vEyePos;				//�J�����̈ʒu(��[���邴�Ђ傤)

#define DIFFUSE_LIGHT_NUM	4		//�f�B�t���[�Y���C�g�̐��B
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//�f�B�t���[�Y���C�g�̕����B
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//�f�B�t���[�Y���C�g�̃J���[�B
float4	g_ambientLight;								//�����B

texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
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
 *@brief	���_�V�F�[�_�[�B
 */
VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT Out;
	//���W�ϊ�
	float4 pos;
	pos = mul(In.pos, g_worldMatrix);		//���f���̃��[�J����Ԃ��烏�[���h��Ԃɕϊ��B
	pos = mul(pos, g_viewMatrix);			//���[���h��Ԃ���r���[��Ԃɕϊ��B
	pos = mul(pos, g_projectionMatrix);	//�r���[��Ԃ���ˉe��Ԃɕϊ��B
	Out.pos = pos;
	//�g�U��+����
	float amb = -g_diffuseLightDirection[0].w;
	float3 L = -g_diffuseLightDirection[0].xyz;//���[�J���̃��C�g���W
	Out.color = In.color * max(amb, dot(In.normal, -g_diffuseLightDirection[0].xyz));
	//���ʔ��˗p�̃x�N�g��
	Out.Eye = vEyePos - pos.xyz;

	Out.uv = In.uv;
	Out.normal = mul(In.normal, g_rotationMatrix);	//�@�����񂷁B
	return Out;
}
/*!
 *@brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain(VS_OUTPUT In) : COLOR
{
	//���C�g���v�Z�B
	//float4 lig = 0.0f;
	//float t;
	//t = dot(-g_diffuseLightDirection[0].xyz, In.normal.xyz);
	//lig = max(0.0f, t);
	//lig.xyz = g_diffuseLightColor[0].xyz * t;

	float4 color = tex2D( g_diffuseTextureSampler, In.uv );
	//color.xyz *= lig;

	//float3 L = -g_diffuseLightDirection[0].xyz;
	//float3 H = normalize(L + normalize(In.Eye));//�n�[�t�x�N�g��	
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