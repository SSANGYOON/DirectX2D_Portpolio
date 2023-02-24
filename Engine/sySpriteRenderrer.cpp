#include "sySpriteRenderrer.h"
#include "syGameObject.h"
#include "syTransform.h"

namespace sy
{
	SpriteRenderrer::SpriteRenderrer()
		: BaseRenderrer(ComponentType::SpriteRenderrer)
	{
	}

	SpriteRenderrer::~SpriteRenderrer()
	{
	}

	void SpriteRenderrer::Start()
	{
	}

	void SpriteRenderrer::Update()
	{
	}

	void SpriteRenderrer::FixedUpdate()
	{
	}

	void SpriteRenderrer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();

		GetMesh()->Render();

		GetMaterial()->Clear();
	}

}