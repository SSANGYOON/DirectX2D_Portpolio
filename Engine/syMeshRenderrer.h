#pragma once
#include "syComponent.h"
#include "syMesh.h"
#include "syMaterial.h"
#include "syBaseRenderrer.h"

using namespace sy::graphics;
namespace sy
{
	class MeshRenderrer : public BaseRenderrer
	{
	public:
		MeshRenderrer();
		virtual ~MeshRenderrer();

		virtual void Start() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}