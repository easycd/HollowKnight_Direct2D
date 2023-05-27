#include "kmGraphicDevice_Dx11.h"
#include "kmApplication.h"
#include "kmRenderer.h"

extern km::Application application;

namespace km::graphics
{
	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		//도형 그리는 순서
		// 1. graphic device, context 생성

		// 2. 화면에 렌더링 할수 있게 도와주는
		// swapchain 생성

		// 3. rendertarget,view 생성하고 
		// 4. 깊이버퍼와 깊이버퍼 뷰 생성해주고

		// 5. 레더타겟 클리어 ( 화면 지우기 )
		// 6. present 함수로 렌더타겟에 있는 텍스쳐를
		//    모니터에 그려준다.

		// Device, Context 생성
		HWND hWnd = application.GetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		//GPU 할당 함수
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION //SDK버전을 가져온다.
			, mDevice.GetAddressOf(), &featureLevel
			, mContext.GetAddressOf());
		//.GetAddressof()는 포인터 변수의 주소를 가져온다.

		//SwapChain
		//SwapChain을 여러개 쓰면 한쪽 코어만 사용하지 않고 사용하지 않는 코어도 같이 사용하게 할 수 있다.
		//DXGI_SWAP_CHAIN_DESC는 어떤 스왑체인을 가져올건지 가리키는것 ex) 옵션
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {}; 
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;

		if(FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
		, (void**)mRenderTarget.GetAddressOf())))
			return;

		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get()
			, nullptr, mRenderTargetView.GetAddressOf());

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		depthStencilDesc.ArraySize = 1;

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MipLevels = 0;
		depthStencilDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;
		
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		mViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		BindViewPort(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}

	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{
	}
	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};

		dxgiDesc.OutputWindow = hWnd; //hWnd에 그려준다.
		dxgiDesc.Windowed = true;
		dxgiDesc.BufferCount = desc->BufferCount; //버퍼를 몇개를 사용할지
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxgiDesc.BufferDesc.Width = desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = desc->BufferDesc.Height;
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 240; //최대 프레임 설정
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1; //최소 프레임 설정
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		dxgiDesc.SampleDesc.Count = 1;
		dxgiDesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		//IDXGIDevice -> 이미지 데이터를 생성
		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;
		//IDXGIAdapter -> 모니터
		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;
		//IDXGIFactory -> 전체 화면시 처리해줌
		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;

		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &dxgiDesc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data)
	{

		if(FAILED(mDevice->CreateBuffer(desc, data, buffer)))
		return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateShader()
	{
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path(); //부모 경로
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl";

		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "main", "vs_5_0", 0, 0, &km::renderer::triangleVSBlob, &km::renderer::errorBlob);

		if (km::renderer::errorBlob)
		{
			OutputDebugStringA((char*)km::renderer::errorBlob->GetBufferPointer());
			km::renderer::errorBlob->Release();
		}

		mDevice->CreateVertexShader(km::renderer::triangleVSBlob->GetBufferPointer()
			, km::renderer::triangleVSBlob->GetBufferSize()
			, nullptr, &km::renderer::triangleVSShader);

		std::filesystem::path psPath(shaderPath.c_str());
		psPath += L"TrianglePS.hlsl";

		D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "ps_5_0", 0, 0, &km::renderer::trianglePSBlob, &km::renderer::errorBlob);

		if (km::renderer::errorBlob)
		{
			OutputDebugStringA((char*)km::renderer::errorBlob->GetBufferPointer());
			km::renderer::errorBlob->Release();
		}

		mDevice->CreatePixelShader(km::renderer::trianglePSBlob->GetBufferPointer()
			, km::renderer::trianglePSBlob->GetBufferSize()
			, nullptr, &km::renderer::trianglePSShader);

		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		mDevice->CreateInputLayout(arrLayout, 2
			, renderer::triangleVSBlob->GetBufferPointer()
			, renderer::triangleVSBlob->GetBufferSize()
			, &renderer::triangleLayout);

		return true;
	}

	bool GraphicDevice_Dx11::CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
	{
		D3D11_TEXTURE2D_DESC dxgiDesc = {};
		dxgiDesc.BindFlags = desc->BindFlags;
		dxgiDesc.Usage = desc->Usage;
		dxgiDesc.CPUAccessFlags = 0;

		dxgiDesc.Format = desc->Format;
		dxgiDesc.Width = desc->Width;
		dxgiDesc.Height = desc->Height;
		dxgiDesc.ArraySize = desc->ArraySize;

		dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
		dxgiDesc.SampleDesc.Quality = 0;

		dxgiDesc.MipLevels = desc->MipLevels; //오브젝트 크기가 커지거나 작아지면 픽셀이 깨지기 때문에 미리 텍스처 사이즈를 크기별로 만들어서 사용함.
		dxgiDesc.MiscFlags = desc->MiscFlags;

		if (FAILED(mDevice->CreateTexture2D(&dxgiDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;

		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return false;

		return true;
	}

	void GraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}

	void GraphicDevice_Dx11::Draw()
	{
		// render target clear
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);

		// viewport update
		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);
		mViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		BindViewPort(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

		// input assembler 정점데이터 정보 지정
		UINT vertexsize = sizeof(renderer::Vertex);
		UINT offset = 0;

		mContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexsize, &offset);
		mContext->IASetInputLayout(renderer::triangleLayout);
		mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//Bind VS, PS 

		mContext->VSSetShader(renderer::triangleVSShader, 0, 0);
		mContext->PSSetShader(renderer::trianglePSShader, 0, 0);

		// Draw Render Target
		mContext->Draw(3, 0);

		// 레더타겟에 있는 이미지를 화면에 그려준다
		mSwapChain->Present(0, 0);
	}

}