#pragma once
#include "syEntity.h"

using namespace sy::enums;
namespace sy
{
	class Resource : public Entity
	{
	public:
		Resource(ResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetKey() { return mKey; }
		const std::wstring& GetPath() { return mPath; }

		void SetKey(const std::wstring& key) { mKey = key; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mKey;
		std::wstring mPath;
		ResourceType mType;
	};
}