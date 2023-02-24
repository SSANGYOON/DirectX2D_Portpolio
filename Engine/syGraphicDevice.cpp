#include "syGraphicDevice.h"
#include "syApplication.h"
#include "syRenderrer.h"


extern sy::Application application;

namespace sy::graphics 
{
	GraphicDevice::GraphicDevice(ValidationMode validationMode)
	{
		/// <summary>
		/// 1. Device 와 SwapChain 생성한다.
		/// 2. 백버퍼에 실제로 렌더링할 렌더타겟 뷰를 생성해야한다.
		/// 3. 화면을 클리어 해줘야한다. 뷰포트를 생성해줘야 한다.
		/// 4. 매프레임마다 위에서 생성한 렌더타겟뷰에 렌더링해주어야한다.
		/// 5. Swapchain을 이용하여 최종 디바이스(디스플레이)에 화면을 그려줘야한다.
		/// </summary>
		/// <param name="validationMode"></param>

		HWND hwnd = application.GetHwnd();

		// Device, Device Context
		UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, DeviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf()
			, &FeatureLevel
			, mContext.GetAddressOf());

		// SwapChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		if (!CreateSwapChain(&swapChainDesc))
			return;

		// Get rendertarget for swapchain
		hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());

		// Create Rendertarget View
		hr = mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());



		D3D11_TEXTURE2D_DESC depthBuffer = {};
		depthBuffer.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthBuffer.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthBuffer.CPUAccessFlags = 0;

		depthBuffer.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBuffer.Width = application.GetWidth();
		depthBuffer.Height = application.GetHeight();
		depthBuffer.ArraySize = 1;

		depthBuffer.SampleDesc.Count = 1;
		depthBuffer.SampleDesc.Quality = 0;

		depthBuffer.MipLevels = 0;
		depthBuffer.MiscFlags = 0;

		// Depth Stencil Buffer
		if (!CreateTexture(&depthBuffer, mDepthStencilBuffer.GetAddressOf()))
			return;

		// Depth Stencil Buffer View
		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return;

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.0f, 0.0f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.0f, 1.0f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}

	GraphicDevice::~GraphicDevice()
	{
		renderrer::Release();
	}

	bool GraphicDevice::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* desc)
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pDXGIAdapter.GetAddressOf())))
			return false;

		if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pDXGIFactory.GetAddressOf())))
			return false;

		if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), desc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}

	bool GraphicDevice::CreateTexture(D3D11_TEXTURE2D_DESC* desc, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTexture2D)))
			return false;

		return true;
	}

	bool GraphicDevice::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT NumElements, const void* byteCode, SIZE_T bytecodeLength, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(desc, NumElements, byteCode, bytecodeLength, ppInputLayout)))
			return false;

		return true;
	}

	bool GraphicDevice::CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer)
	{
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
			return false;

		return true;
	}

	bool GraphicDevice::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
	{
		if (FAILED(mDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader)))
			return false;

		return true;
	}

	bool GraphicDevice::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
	{
		if (FAILED(mDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader)))
			return false;

		return true;
	}

	bool GraphicDevice::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;

		return true;
	}

	bool GraphicDevice::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
	{
		if (FAILED(mDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState)))
			return false;

		return true;
	}

	bool GraphicDevice::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState)
	{
		if (FAILED(mDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState)))
			return false;

		return true;
	}

	bool GraphicDevice::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState)
	{
		if (FAILED(mDevice->CreateBlendState(pBlendStateDesc, ppBlendState)))
			return false;

		return true;
	}

	void GraphicDevice::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		mContext->IASetPrimitiveTopology(topology);
	}

	void GraphicDevice::BindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}

	void GraphicDevice::BindVertexBuffer(UINT StartSlot
		, UINT NumBuffers
		, ID3D11Buffer* const* ppVertexBuffers
		, const UINT* pStrides
		, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
	}

	void GraphicDevice::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}

	void GraphicDevice::BindVertexShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
	{
		mContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
	}

	void GraphicDevice::BindPixelShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
	{
		mContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
	}

	void GraphicDevice::BindViewports(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}

	void GraphicDevice::BindConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
	}

	void GraphicDevice::SetConstantBuffer(ShaderStage stage, CBType type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case sy::graphics::ShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case sy::graphics::ShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case sy::graphics::ShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case sy::graphics::ShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case sy::graphics::ShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case sy::graphics::ShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		default:
			break;
		}
	}

	void GraphicDevice::SetShaderResource(ShaderStage stage, UINT slot
		, ID3D11ShaderResourceView* const* ppShaderResourceViews)
	{
		switch (stage)
		{
		case sy::graphics::ShaderStage::VS:
			mContext->VSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case sy::graphics::ShaderStage::HS:
			mContext->HSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case sy::graphics::ShaderStage::DS:
			mContext->DSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case sy::graphics::ShaderStage::GS:
			mContext->GSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case sy::graphics::ShaderStage::PS:
			mContext->PSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		case sy::graphics::ShaderStage::CS:
			mContext->CSSetShaderResources(slot, 1, ppShaderResourceViews);
			break;
		default:
			break;
		}
	}

	void GraphicDevice::BindSamplers(ShaderStage stage, UINT slot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		switch (stage)
		{
		case sy::graphics::ShaderStage::VS:
			mContext->VSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case sy::graphics::ShaderStage::HS:
			mContext->HSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case sy::graphics::ShaderStage::DS:
			mContext->DSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case sy::graphics::ShaderStage::GS:
			mContext->GSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case sy::graphics::ShaderStage::PS:
			mContext->PSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		case sy::graphics::ShaderStage::CS:
			mContext->CSSetSamplers(slot, NumSamplers, ppSamplers);
			break;
		default:
			break;
		}
	}

	void GraphicDevice::BindsSamplers(UINT slot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		mContext->VSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->HSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->DSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->GSSetSamplers(slot, NumSamplers, ppSamplers);
		mContext->PSSetSamplers(slot, NumSamplers, ppSamplers);
	}

	void GraphicDevice::BindRasterizerState(ID3D11RasterizerState* pRasterizerState)
	{
		mContext->RSSetState(pRasterizerState);
	}

	void GraphicDevice::BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState)
	{
		mContext->OMSetDepthStencilState(pDepthStencilState, 0);
	}

	void GraphicDevice::BindBlendState(ID3D11BlendState* pBlendState)
	{
		mContext->OMSetBlendState(pBlendState, nullptr, 0xffffffff);
	}

	void GraphicDevice::Clear()
	{
		// 화면 지워주기
		FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	void GraphicDevice::AdjustViewPorts()
	{
		// ViewPort, RenderTaget
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		mViewPort = { 0.0f, 0.0f, FLOAT(winRect.right - winRect.left), FLOAT(winRect.bottom - winRect.top), 0.0f, 1.0f };
		BindViewports(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}

	void GraphicDevice::Draw()
	{
		mContext->Draw(0, 0);
	}

	void GraphicDevice::DrawIndexed(UINT indexCount, UINT StartIndexLocation, UINT BaseVertexLocation)
	{
		mContext->DrawIndexed(indexCount, StartIndexLocation, BaseVertexLocation);
	}

	void GraphicDevice::Present()
	{
		mSwapChain->Present(0, 0);
	}
}