#include "syApplication.h"
#include "syRenderrer.h"
#include "syTime.h"
#include "syInput.h"
#include "sySceneManager.h"
#include "syResourceManager.h"

namespace sy
{
	using namespace graphics;

	Application::Application()
	{

	}

	Application::~Application()
	{
		SceneManager::Release();
	}

	void Application::Initialize()
	{
		Time::Initialize();
		Input::Initialize();

		renderrer::Initialize();
		SceneManager::Initialize();
	}

	// ���� ���� ĳ���� �̵� ��� 
	// CPU UPDATE
	void Application::Update()
	{
		Time::Update();
		Input::Update();

		SceneManager::Update();
	}

	// GPU update
	void Application::FixedUpdate()
	{
		SceneManager::FixedUpdate();
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		//SceneManager::Render();
		renderrer::Render();

		//graphicDevice->Render();
		graphicDevice->Present();
	}

	// Running main engine loop
	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Application::Release()
	{
		ResourceManager::deleteTest();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = width;
			mHeight = height;


			ValidationMode vaildationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice>();
			graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
	}