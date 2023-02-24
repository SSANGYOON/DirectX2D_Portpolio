#pragma once
#include "syScript.h"
#include "syTime.h"
namespace sy
{
	class FadeInScript : public Script
	{
	public:
		FadeInScript();
		virtual ~FadeInScript();

		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		float dtime;
		const float duration = 2.0f;
	};
}

