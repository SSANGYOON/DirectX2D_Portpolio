#include "syShader.h"
#include "syGraphicDevice.h"
#include "syRenderrer.h"

using namespace sy::graphics;

namespace sy
{
	Shader::Shader()
		: Resource(ResourceType::GraphicShader)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, mRSType(RSType::SolidBack)
		, mDSType(DSType::Less)
		, mBSType(BSType::AlphaBlend)
	{

	}

	Shader::~Shader()
	{

	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Shader::Create(ShaderStage stage, const std::wstring& file, const std::string& funcName)
	{
		mErrorBlob = nullptr;

		// Vertex Shader
		std::filesystem::path path = std::filesystem::current_path().parent_path();
		path += "\\SHADER_SOURCE\\";

		std::wstring shaderPath(path.c_str());
		shaderPath += file;

		if (stage == graphics::ShaderStage::VS)
		{
			D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
				, funcName.c_str(), "vs_5_0", 0, 0
				, mVSBlob.GetAddressOf()
				, mErrorBlob.GetAddressOf());

			if (mErrorBlob)
			{
				OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			}

			GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
				, mVSBlob->GetBufferSize()
				, nullptr
				, mVS.GetAddressOf());
		}
		else if (stage == graphics::ShaderStage::PS)
		{
			D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
				, funcName.c_str(), "ps_5_0", 0, 0
				, mPSBlob.GetAddressOf()
				, mErrorBlob.GetAddressOf());

			if (mErrorBlob)
			{
				OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
			}

			GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize()
				, nullptr
				, mPS.GetAddressOf());
		}
	}

	void Shader::Binds()
	{
		GetDevice()->BindPrimitiveTopology(mTopology);
		GetDevice()->BindInputLayout(mInputLayout.Get());

		GetDevice()->BindVertexShader(mVS.Get(), nullptr, 0);
		GetDevice()->BindPixelShader(mPS.Get(), nullptr, 0);

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rs = renderrer::rasterizerStates[(UINT)mRSType];
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> ds = renderrer::depthstencilStates[(UINT)mDSType];
		Microsoft::WRL::ComPtr<ID3D11BlendState> bs = renderrer::blendStates[(UINT)mBSType];

		GetDevice()->BindRasterizerState(rs.Get());
		GetDevice()->BindDepthStencilState(ds.Get());
		GetDevice()->BindBlendState(bs.Get());
	}

}

