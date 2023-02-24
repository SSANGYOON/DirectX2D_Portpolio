#include "syFadeInScript.h"
#include "sySpriteRenderrer.h"
#include "syGameObject.h"

namespace sy
{
	FadeInScript::FadeInScript()
		:dtime(0)
	{
	}
	FadeInScript::~FadeInScript()
	{
	}
	void FadeInScript::Start()
	{
		dtime = 0;
	}
	void FadeInScript::Update()
	{
		dtime += Time::DeltaTime();
		float alpha = 1.0f;
		switch (state)
		{
		case sy::FadeInScript::FADEIN:
			if (dtime >= fadeIn)
			{
				dtime -= fadeIn;
				state = FadeInScript::IDLE;
				alpha = 1.0f;
			}
			else
			{
				alpha = dtime / fadeIn;
			}
			break;
		case sy::FadeInScript::IDLE:
			if (dtime >= Idle)
			{
				dtime -= Idle;
				state = FadeInScript::FADEOUT;
				alpha = (fadeOut - dtime) / fadeOut;
			}
			else
			{
				alpha = 1;
			}
			break;
		case sy::FadeInScript::FADEOUT:
			if (dtime >= fadeOut)
			{
				dtime = fadeOut;
			}
			alpha = (fadeOut - dtime) / fadeOut;
			break;
		default:
			break;
		}
		std::shared_ptr<Material> material = GetOwner()->GetComponent<SpriteRenderrer>()->GetMaterial();
		
		material->SetData(GPUParam::Float, &alpha);
	}
	void FadeInScript::FixedUpdate()
	{
	}
	void FadeInScript::Render()
	{
	}
}