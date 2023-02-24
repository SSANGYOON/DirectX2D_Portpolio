#include "syMeshRenderrer.h"
#include "syGameObject.h"
#include "syTransform.h"

namespace sy
{
	MeshRenderrer::MeshRenderrer()
		: BaseRenderrer(ComponentType::MeshRenderrer)
	{
	}

	MeshRenderrer::~MeshRenderrer()
	{

	}

	void MeshRenderrer::Start()
	{
	}

	void MeshRenderrer::Update()
	{
	}

	void MeshRenderrer::FixedUpdate()
	{
	}

	void MeshRenderrer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();

		GetMesh()->Render();

		GetMaterial()->Clear();
	}
}