#pragma once
#include "syEntity.h"
#include "syLayer.h"

namespace sy
{
	using namespace sy::enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Exit();

		void AddGameObject(GameObject* gameObj, const LayerType type);
		Layer& GetLayer(LayerType type) { return mLayers[(UINT)type]; }


	protected:
		std::vector<Layer> mLayers;
	};
}

