#pragma once
#include "syComponent.h"
#include "syScript.h"
#include "syEntity.h"

namespace sy
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			ComponentType order = comp->GetOrder();

			if (order != ComponentType::Script)
			{
				mComponents[(UINT)order] = comp;
				mComponents[(UINT)order]->SetOwner(this);
			}
			else
			{
				mScripts.push_back(comp);
				comp->SetOwner(this);
			}

			return comp;
		}
		void AddComponent(Component* comp);

		template <typename T>
		T* GetComponent()
		{
			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					return comp;
			}

			return nullptr;
		}

		bool IsDead()
		{
			if (mState == eState::Dead)
				return true;

			return false;
		}
		void Pause() { mState = eState::Paused; }
		void Death() { mState = eState::Dead; }
		eState GetState() { return mState; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Component*> mScripts;
	};
}
