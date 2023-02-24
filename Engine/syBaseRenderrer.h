#pragma once
#include "syComponent.h"
#include "syMesh.h"
#include "syMaterial.h"

namespace sy
{
	class BaseRenderrer : public Component
	{
	public:
		BaseRenderrer(ComponentType type);
		virtual ~BaseRenderrer();

		virtual void Start() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr <Material> shader) { mMaterial = shader; }
		std::shared_ptr<Mesh> GetMesh() { return mMesh; }
		std::shared_ptr<Material> GetMaterial() { return mMaterial; }

	protected:
		std::shared_ptr <Mesh> mMesh;
		std::shared_ptr <Material> mMaterial;
	};
}
