#include "syLayer.h"


namespace sy
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Initalize()
	{
		for (std::shared_ptr<GameObject>& obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Start();
		}
	}

	void Layer::Update()
	{
		for (std::shared_ptr<GameObject>& obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (std::shared_ptr<GameObject>& obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->FixedUpdate();
		}
	}

	void Layer::Render()
	{
		for (std::shared_ptr<GameObject>& obj : mGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(std::shared_ptr<GameObject>(gameObject));
	}
}