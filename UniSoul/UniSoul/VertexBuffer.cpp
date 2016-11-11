#include "stdafx.h"
#include "VertexBuffer.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

CVertexBuffer::CVertexBuffer() :
	m_pVB(nullptr),
	m_stride(0),
	m_numVertex(0),
	m_size(0)
{
}
CVertexBuffer::~CVertexBuffer()
{
	Release();
}
void CVertexBuffer::Create(
	int numVertex,
	int stride,
	const D3DVERTEXELEMENT9* vertexLayout,
	const void* pSrcVertexBuffer)
{
	Release();
	m_numVertex = numVertex;
	m_stride = stride;
	m_size = m_numVertex * m_stride;
	HRESULT hr = g_pd3dDevice->CreateVertexBuffer(
		numVertex * stride,
		0,
		0,
		D3DPOOL_DEFAULT,
		&m_pVB,
		NULL
	);
	if (pSrcVertexBuffer != nullptr) {
		//�\�[�X���w�肳��Ă���B
		//���_�o�b�t�@�����b�N���ăR�s�[�B
		void* pDstVertexBuffer;
		hr = m_pVB->Lock(0, 0, &pDstVertexBuffer, D3DLOCK_DISCARD);
		//�܂���ƃR�s�[�B

		memcpy(pDstVertexBuffer, pSrcVertexBuffer, m_size);
		m_pVB->Unlock();
	}
	//���_��`���쐬�B
	g_pd3dDevice->CreateVertexDeclaration(vertexLayout, &m_pVertexDecl);
}
void CVertexBuffer::Release()
{
	if (m_pVB != nullptr) {
		m_pVB->Release();
		m_pVB = nullptr;
	}
}
