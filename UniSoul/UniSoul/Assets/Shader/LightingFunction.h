/*!
 * @brief	ライティング関係の関数集
 */

#define NUM_DIFFUSE_LIGHT	4					//ディフューズライトの数。

struct SLight{
	float4	g_diffuseLightDirection[NUM_DIFFUSE_LIGHT];		//ディフューズライトの向き。
	float4  g_diffuseLightColor[NUM_DIFFUSE_LIGHT];	//ディフューズライトのカラー。
	float4  g_ambientLight;								//アンビエントライト。
};
SLight	g_light;		//ライト

/*!
 *@brief	ディフューズライトを計算。
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
 * @brief	アルファに埋め込む輝度を計算。
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