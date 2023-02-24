#pragma once
#include <wrl.h>

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")


#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0
#define CBSLOT_MATERIAL 1
#define CBSLOT_GRID 2

namespace sy::graphics
{
	enum class ShaderStage
	{
		VS,		
		HS,		
		DS,		
		GS,		
		PS,		
		CS,		
		Count,
	};

	enum class ValidationMode
	{
		Disabled,
		Enabled,
		GPU,
	};

	

	struct GpuBuffer
	{
		enum class eType
		{
			Buffer,
			Texture,
			UnknownType,
		} type = eType::UnknownType;

		D3D11_BUFFER_DESC desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};

	enum class CBType
	{
		Transform,
		Material,
		Grid,
		End,
	};

	enum class GPUParam
	{
		Int,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Matrix,
	};

	enum class SamplerType
	{
		Point,
		Linear,
		Anisotropic,
		End,
	};

	enum class RSType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		End,
	};

	enum class DSType
	{
		Less,
		Greater,
		NoWrite,
		None,
		End,
	};

	enum class BSType
	{
		Default,
		AlphaBlend,
		OneOne,
		End,
	};

	enum class RenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		End,
	};
}