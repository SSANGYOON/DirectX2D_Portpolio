#include "syCamera.h"
#include "syTransform.h"
#include "syGameObject.h"
#include "syApplication.h"
#include "syRenderrer.h"
#include "syScene.h"
#include "sySceneManager.h"
#include "syMaterial.h"
#include "syBaseRenderrer.h"

extern sy::Application application;

namespace sy
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(ComponentType::Camera)
		, mType(eProjectionType::Perspective)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mScale(1.0f)
	{
		EnableLayerMasks();
	}

	Camera::~Camera()
	{
	}

	void Camera::Start()
	{

		//RegisterCameraInRenderer();
	}

	void Camera::Update()
	{
	}

	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}

	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutout();
		renderTransparent();
	}

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// Crate Translate view matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);
		//회전 정보

		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;

		mView *= viewRotate;
	}

	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left) * mScale;
		float height = (winRect.bottom - winRect.top) * mScale;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH
			(
				XM_2PI / 6.0f
				, mAspectRatio
				, mNear
				, mFar
			);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNear, mFar);
		}
	}

	void Camera::RegisterCameraInRenderer()
	{
		renderrer::cameras.push_back(this);
	}

	void Camera::TurnLayerMask(LayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}

	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)LayerType::End; i++)
		{
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((LayerType)i);
				GameObjects gameObjects = layer.GetGameObjects();
				if (gameObjects.size() == 0)
					continue;

				for (std::shared_ptr<GameObject> obj : gameObjects)
				{
					pushGameObjectToRenderingModes(obj.get());
				}
			}
		}
	}

	void Camera::renderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderCutout()
	{
		for (GameObject* obj : mCutoutGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::renderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}

	void Camera::pushGameObjectToRenderingModes(GameObject* gameObj)
	{
		BaseRenderrer* renderrer
			= gameObj->GetComponent<BaseRenderrer>();
		if (renderrer == nullptr)
			return;

		std::shared_ptr<Material> material = renderrer->GetMaterial();
		//if (material == nullptr)
		//	continue;

		RenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case sy::graphics::RenderingMode::Opaque:
			mOpaqueGameObjects.push_back(gameObj);
			break;
		case sy::graphics::RenderingMode::CutOut:
			mCutoutGameObjects.push_back(gameObj);
			break;
		case sy::graphics::RenderingMode::Transparent:
			mTransparentGameObjects.push_back(gameObj);
			break;
		default:
			break;
		}
	}
}
