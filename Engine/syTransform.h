#pragma once
#include "syComponent.h"

namespace sy {
    class Transform : public Component
    {
	public:
		Transform();
		virtual ~Transform();

		virtual void Start() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
		void SetConstantBuffer();

		void SetParent(Transform* parent) { mParent = parent; }
		Transform* GetParent() { return mParent; }

		Vector3 GetPosition() { return mPosition; };
		Quaternion GetRotation() { return mRotation; };
		Vector3 GetScale() { return mScale; };

		void SetPosition(Vector3 position) { mPosition = position; };
		void SetRotation(Quaternion rotation) { mRotation = rotation; };
		void SetScale(Vector3 scale) { mScale = scale; };

		Vector3 Foward() { return mFoward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

	private:
		Transform* mParent;
		Vector3 mFoward;
		Vector3 mRight;
		Vector3 mUp;
		Vector3 mPosition;
		Quaternion mRotation;
		Vector3 mScale;
		Matrix mWorld;
    };
}

