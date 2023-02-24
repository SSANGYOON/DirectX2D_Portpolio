#include "sySceneManager.h"
#include "syTransform.h"
#include "syMeshRenderrer.h"
#include "syRenderrer.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syPlayerScript.h"
#include "syCamera.h"
#include "syCameraScript.h"
#include "sySpriteRenderrer.h"
#include "syGridScript.h"
#include "syObject.h"
#include "syFadeInScript.h"
namespace sy
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mActiveScene = new Scene();
		mActiveScene->Initialize();

		// Grid Object
		GameObject* gridObject = object::Instantiate<GameObject>(LayerType::None);
		MeshRenderrer* gridMr = gridObject->AddComponent<MeshRenderrer>();
		gridMr->SetMesh(ResourceManager::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(ResourceManager::Find<Material>(L"GridMaterial"));
		gridObject->AddComponent<GridScript>();

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(LayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(LayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(LayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(LayerType::UI, true);

		// Light Object
		GameObject* spriteObj = object::Instantiate<GameObject>(LayerType::Player);
		spriteObj->SetName(L"LIGHT");
		Transform* spriteTr = spriteObj->GetComponent<Transform>();
		spriteTr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
		spriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

		SpriteRenderrer* sr = spriteObj->AddComponent<SpriteRenderrer>();
		std::shared_ptr<Mesh> mesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> spriteMaterial = ResourceManager::Find<Material>(L"SpriteMaterial");
		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);
		spriteObj->AddComponent<FadeInScript>();

		//SMILE RECT
		GameObject* obj = object::Instantiate<GameObject>(LayerType::Player);
		obj->SetName(L"SMILE");
		Transform* tr = obj->GetComponent<Transform>();
		tr->SetPosition(Vector3(-3.0f, 0.0f, 11.0f));
		tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2));
		tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		MeshRenderrer* mr = obj->AddComponent<MeshRenderrer>();
		std::shared_ptr<Material> mateiral = ResourceManager::Find<Material>(L"RectMaterial");
		mr->SetMaterial(mateiral);
		mr->SetMesh(mesh);
		obj->AddComponent<PlayerScript>();

		//SMILE RECT CHild
		GameObject* child = object::Instantiate<GameObject>(LayerType::Player);
		child->SetName(L"SMILE");
		Transform* childTr = child->GetComponent<Transform>();
		childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		childTr->SetParent(tr);
		

		MeshRenderrer* childMr = child->AddComponent<MeshRenderrer>();
		std::shared_ptr<Material> childmateiral = ResourceManager::Find<Material>(L"RectMaterial");
		childMr->SetMaterial(childmateiral);
		childMr->SetMesh(mesh);

		// HPBAR
		GameObject* hpBar = object::Instantiate<GameObject>(LayerType::Player);
		hpBar->SetName(L"HPBAR");
		Transform* hpBarTR = hpBar->GetComponent<Transform>();
		hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
		hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		SpriteRenderrer* hpsr = hpBar->AddComponent<SpriteRenderrer>();
		std::shared_ptr<Mesh> hpmesh = ResourceManager::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> hpspriteMaterial = ResourceManager::Find<Material>(L"UIMaterial");
		hpsr->SetMesh(hpmesh);
		hpsr->SetMaterial(hpspriteMaterial);

		//hpBar->Pause();

		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Release()
	{
		delete mActiveScene;
		mActiveScene = nullptr;
	}
}