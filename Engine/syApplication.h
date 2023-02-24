#pragma once
#include "syEngine.h"
#include "syGraphics.h"
#include "syGraphicDevice.h"

namespace sy
{
	class sy::graphics::GraphicDevice;
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		// Running main engine loop
		void Run();
		void Release();

		void SetWindow(HWND hwnd, UINT width, UINT height);
		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() { return mHwnd; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		bool initialized = false;
		std::unique_ptr<graphics::GraphicDevice> graphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mHeight;
		UINT mWidth;
	};
}

