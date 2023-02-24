#pragma once
#include "syResource.h"
#include "syShader.h"
#include "syTexture.h"
#include "syRenderrer.h"

using namespace sy::renderrer;
namespace sy::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(GPUParam param, void* data);
		void Bind();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		std::shared_ptr<Shader> GetShader() { return mShader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		std::shared_ptr<Texture> GetTexture() { return mTexture; }

		RenderingMode GetRenderingMode() { return mMode; }
		void SetRenderingMode(RenderingMode mode) { mMode = mode; }

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;
		MaterialCB mCB;
		RenderingMode mMode;
	};
}