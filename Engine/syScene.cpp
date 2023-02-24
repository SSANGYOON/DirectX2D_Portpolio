#include "syScene.h"

namespace sy
{
	Scene::Scene()
	{
		mLayers.resize((UINT)LayerType::End);
	}
	Scene::~Scene()
	{

	}
	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initalize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::Exit()
	{
	}
	void Scene::AddGameObject(GameObject* gameObj, const LayerType type)
	{
		mLayers[(UINT)type].AddGameObject(gameObj);
	}
}