#pragma once
#include "syScene.h"
#include "syLayer.h"
#include "syGameObject.h"
#include "sySceneManager.h"
#include "syTransform.h"

namespace sy::object
{
	template <typename T>
	static T* Instantiate(enums::LayerType type, Transform* parent = nullptr)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);
		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		if(parent)
			tr->SetParent(parent);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::LayerType type, Vector3 position, Vector3 rotation)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::LayerType type, Vector3 position, Vector3 rotation, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);
		tr->SetParent(parent);

		return gameObj;
	}

	void Destroy(GameObject* gameObject)
	{
		gameObject->Death();
	}
}