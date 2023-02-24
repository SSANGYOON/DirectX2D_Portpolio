#pragma once
#include "syGraphics.h"


namespace sy::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer(CBType type);
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void Bind(void* data);
		void SetPipline(ShaderStage stage);

		//void SetType(eCBType type) { mType = type; }


	private:
		const CBType mType;
	};
}