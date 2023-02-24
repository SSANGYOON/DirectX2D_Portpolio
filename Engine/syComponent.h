#pragma once
#include "syMath.h"
#include "syEntity.h"

namespace sy
{
	class GameObject;
	using namespace enums;
	using namespace math;
	class Component : public Entity
	{
	public:
		Component(ComponentType type);
		virtual ~Component();

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() = 0;

		ComponentType GetOrder() { return mType; };

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		GameObject* mOwner;
		ComponentType mType;
	};
}

