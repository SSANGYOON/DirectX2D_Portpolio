#pragma once
#include "syEntity.h"
#include "syGameObject.h"
namespace sy
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObject);
		const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() { return mGameObjects; }

	private:
		std::vector<std::shared_ptr<GameObject>> mGameObjects;
	};

	typedef const std::vector<std::shared_ptr<GameObject>>& GameObjects;
}
