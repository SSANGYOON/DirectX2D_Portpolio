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
		enum FadeState
		{
			FADEIN,
			IDLE,
			FADEOUT
		};
	private:

		FadeState state;
		float dtime;
		const float fadeIn = 2.0f;
		const float Idle = 7.0f;
		const float fadeOut = 2.0f;
	};
}

