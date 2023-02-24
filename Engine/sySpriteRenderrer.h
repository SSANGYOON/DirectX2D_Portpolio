#pragma once

#include "syComponent.h"
#include "syMesh.h"
#include "syMaterial.h"
#include "syBaseRenderrer.h"

using namespace sy::graphics;
namespace sy
{
	class SpriteRenderrer : public BaseRenderrer
	{
	public:
		SpriteRenderrer();
		virtual ~SpriteRenderrer();

		virtual void Start() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}