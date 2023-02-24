#pragma once
#include "syResource.h"
namespace sy
{
	class sySpriteAnimation :public Resource
	{
	public : 
		sySpriteAnimation();
		~sySpriteAnimation();

		virtual HRESULT Load(const std::wstring& path)

	};
}

