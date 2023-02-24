#pragma once
#include "syComponent.h"

namespace sy
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		//std::vector<Script*> mScripts;
		//state jump;
		//state Attack;
	};
}