#pragma once
#include "..\External\DirectXTex\Include\DirectXTex.h"
#include "syResource.h"
#include "syGraphicDevice.h"

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex.lib") 
#else 
#pragma comment(lib, "DirectXTex.lib") 
#endif


using namespace sy::enums;
namespace sy::graphics
{
	using namespace DirectX;
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;
		void BindShader(ShaderStage stage, UINT slot);
		void Clear();

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};

}
