#include "syTransform.h"
#include "syRenderrer.h"
#include "syCamera.h"

namespace sy
{
	Transform::Transform()
		: Component(ComponentType::Transform)
		, mFoward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
		, mScale(Vector3::One)
		, mRotation(Quaternion::Identity)
		, mPosition(Vector3::One)
		, mParent(nullptr)
	{

	}

	Transform::~Transform()
	{
	}

	void Transform::Start()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::FixedUpdate()
	{

		Matrix scale = Matrix::CreateScale(mScale);


		Matrix rotation;
		rotation = Matrix::CreateFromQuaternion(mRotation);


		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::SetConstantBuffer()
	{
		renderrer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = Camera::GetViewMatrix();
		trCb.projection = Camera::GetProjectionMatrix();

		ConstantBuffer* cb = renderrer::constantBuffers[(UINT)CBType::Transform];
		cb->Bind(&trCb);
		cb->SetPipline(ShaderStage::VS);
	}
}
