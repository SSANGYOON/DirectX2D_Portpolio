#include "syMaterial.h"

namespace sy::graphics
{
    Material::Material()
        : Resource(ResourceType::Material)
        , mMode(RenderingMode::Opaque)
    {

    }

    Material::~Material()
    {

    }

    HRESULT Material::Load(const std::wstring& path)
    {



        return E_NOTIMPL;
    }

    void Material::SetData(GPUParam param, void* data)
    {
        switch (param)
        {
        case sy::graphics::GPUParam::Int:
            mCB.iData = *static_cast<int*>(data);
            break;
        case sy::graphics::GPUParam::Float:
            mCB.fData = *static_cast<float*>(data);
            break;
        case sy::graphics::GPUParam::Vector2:
            mCB.xy = *static_cast<Vector2*>(data);
            break;
        case sy::graphics::GPUParam::Vector3:
            mCB.xyz = *static_cast<Vector3*>(data);
            break;
        case sy::graphics::GPUParam::Vector4:
            mCB.xyzw = *static_cast<Vector4*>(data);
            break;
        case sy::graphics::GPUParam::Matrix:
            mCB.matrix = *static_cast<Matrix*>(data);
            break;
        default:
            break;
        }

    }

    void Material::Bind()
    {
        if (mTexture)
            mTexture->BindShader(ShaderStage::PS, 0);

        ConstantBuffer* pCB = renderrer::constantBuffers[(UINT)CBType::Material];
        pCB->Bind(&mCB);
        pCB->SetPipline(ShaderStage::VS);
        pCB->SetPipline(ShaderStage::PS);

        mShader->Binds();
    }

    void Material::Clear()
    {
        mTexture->Clear();
    }
}
