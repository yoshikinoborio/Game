/*!
 * @brief	���C�e�B���O�֌W�̊֐��W
 */

#define NUM_DIFFUSE_LIGHT	4					//�f�B�t���[�Y���C�g�̐��B

struct SLight{
	float4	g_diffuseLightDirection[NUM_DIFFUSE_LIGHT];		//�f�B�t���[�Y���C�g�̌����B
	float4  g_diffuseLightColor[NUM_DIFFUSE_LIGHT];	//�f�B�t���[�Y���C�g�̃J���[�B
	float4  g_ambientLight;								//�A���r�G���g���C�g�B
};
SLight	g_light;		//���C�g�B

/*!
 *@brief	�f�B�t���[�Y���C�g���v�Z�B
 */	
float4 DiffuseLight(float3 normal)
{
	float4 color = 0.0f;
	color += max(0, -dot(normal,g_light.g_diffuseLightDirection[0])) * g_light.g_diffuseLightColor[0];
	color += max(0, -dot(normal,g_light.g_diffuseLightDirection[1])) * g_light.g_diffuseLightColor[1];
	color += max(0, -dot(normal,g_light.g_diffuseLightDirection[2])) * g_light.g_diffuseLightColor[2];
	color += max(0, -dot(normal,g_light.g_diffuseLightDirection[3])) * g_light.g_diffuseLightColor[3];
	color.xyz += g_light.g_ambientLight.xyz;
	color.a = 1.0f;
	return color;
}

/*!
 * @brief	�A���t�@�ɖ��ߍ��ދP�x���v�Z�B
 */
float CalcLuminance( float3 color )
{
	float luminance = dot( color.xyz, float3(0.2125f, 0.7154f, 0.0721f) );
	if(luminance > 1.0f ){
		luminance = 1.0f / luminance;
	}else{
		luminance = 0.0f;
	}
	return luminance;
}