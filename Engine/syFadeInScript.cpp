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
		if (dtime < duration)
			dtime += Time::DeltaTime();
		else
			dtime = duration;
		float fraction = dtime / duration;
		std::shared_ptr<Material> material = GetOwner()->GetComponent<SpriteRenderrer>()->GetMaterial();
		
		material->SetData(GPUParam::Float, &fraction);
	}
	void FadeInScript::FixedUpdate()
	{
	}
	void FadeInScript::Render()
	{
	}
}