#include "syMesh.h"
#include "syRenderrer.h"
#include "syGraphicDevice.h"

namespace sy
{
	using namespace sy::graphics;
	Mesh::Mesh()
		: Resource(ResourceType::Mesh)
		, mVBDesc{}
		, mIBDesc{}
		, mIndexCount(0)
	{

	}

	Mesh::~Mesh()
	{

	}

	HRESULT Mesh::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool Mesh::CreateVertexBuffer(void* data, UINT count)
	{
		// 버텍스 버퍼
		mVBDesc.ByteWidth = sizeof(renderrer::Vertex) * count;
		mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mVBDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = data;

		if (!graphics::GetDevice()->CreateBuffer(&mVBDesc, &subData, mVertexBuffer.GetAddressOf()))
			return false;

		return true;
	}

	bool Mesh::CreateIndexBuffer(void* data, UINT count)
	{
		mIndexCount = count;
		mIBDesc.ByteWidth = sizeof(UINT) * count;
		mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIBDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData = {};
		subData.pSysMem = data;

		if (!GetDevice()->CreateBuffer(&mIBDesc, &subData, mIndexBuffer.GetAddressOf()))
			return false;

		return true;
	}

	void Mesh::BindBuffer()
	{
		// Input Assembeler 단계에 버텍스버퍼 정보 지정
		UINT stride = sizeof(renderrer::Vertex);
		UINT offset = 0;

		GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void Mesh::Render()
	{
		GetDevice()->DrawIndexed(mIndexCount, 0, 0);
	}
}