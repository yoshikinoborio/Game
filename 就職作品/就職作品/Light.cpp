#include "stdafx.h"
#include "Light.h"

Light::Light()
{
	ZeroMemory(m_diffuseLightDirection, sizeof(m_diffuseLightDirection));
	ZeroMemory(m_diffuseLightColor, sizeof(m_diffuseLightColor));
	m_ambientLight = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
}

Light::~Light()
{
}

void Light::Initialize()
{
	//�f�B�t���[�Y���C�g�B
	m_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_diffuseLightDirection[1] = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_diffuseLightDirection[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_diffuseLightDirection[3] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	//�f�B�t���[�Y���C�g�J���[�B
	m_diffuseLightColor[0] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_diffuseLightColor[1] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_diffuseLightColor[2] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_diffuseLightColor[3] = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);

	//�����B
	m_ambientLight = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
}


void Light::Update()
{
	
}