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
		//디스플레이 어댑터를 나타내는 장치만든는 함수
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
		swapChainDesc.BufferCount = 2; //버퍼 갯수
		swapChainDesc.BufferDesc.Width = application.GetWidth(); //후면 버퍼 너비
		swapChainDesc.BufferDesc.Height = application.GetHeight(); //후면 버퍼 높이

		//그래픽 디바이스와 연결된 윈도우와의 교환체인 생성
		if (!CreateSwapChain(&swapChainDesc, hWnd))
			return;

		mRenderTarget = std::make_shared<Texture>();
		mDepthStencil = std::make_shared<Texture>();

		Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTarget = nullptr;
		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)renderTarget.GetAddressOf())))
			return;
		mRenderTarget->SetTexture(renderTarget);

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget->GetTexture().Get()
			, nullptr, renderTargetView.GetAddressOf());
		mRenderTarget->SetRTV(renderTargetView);

		//D3D11_TEXTURE2D_DESC -> 깊이 정보를 담는 2차원 텍스처
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL; //자원을 파이프라인에 어떤 식으로 묶을 것인지를 지정하는 하나 이상의 플래그들을 OR로 결합해서 지정한다.
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; //텍스처의 용도를 뜻하는 필드
		depthStencilDesc.CPUAccessFlags = 0; //CPU가 자원에 접근하는 방식을 결정하는 플래그들을 지정
		                                     //자원을 기록해야 하는 경우 _WRITE, 읽어야 하는 경우 _READ, 쓰기 접근이 가능해야하는 경우 _DYNAMIC과 STAGING
		                                     //깊이, 스텐실 버퍼의 경우, GPU깊이 스텐실 버퍼를 읽고 쓸 뿐 CPU는 전혀 접근하지 않을 경우 0

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT; //텍셀의 형식을 뜻하는 필드로, DXGI_FORMAT 열거형의 값들 중 하나를 지정한다. 깊이스텐실 버퍼의 경우에 나온 형식들 중 하나를 사용해야 한다.
		depthStencilDesc.Width = application.GetWidth(); //텍스처의 너비
		depthStencilDesc.Height = application.GetHeight(); //텍스처의 높이
		depthStencilDesc.ArraySize = 1; //텍스처 배열의 텍스처 갯수. 깊이, 스텐실 버퍼의 경우에는 텍스처 하나만 필요

		depthStencilDesc.SampleDesc.Count = 1; //다중 표본 갯수의 품질 수준을 서술하는 구조체
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MipLevels = 0; //밉맵 수준의 갯수. 깊이, 스탠실 버퍼를 위한 텍스처에서는 밉맵 수준이 하나만 있으면 된다.
		depthStencilDesc.MiscFlags = 0;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer = nullptr;
		if (!CreateTexture2D(&depthStencilDesc, nullptr, depthStencilBuffer.GetAddressOf()))
			return;
		mDepthStencil->SetTexture(depthStencilBuffer);

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView = nullptr;
		if (!CraeteDepthStencilView(depthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf()))
			return;
		mDepthStencil->SetDSV(mDepthStencilView);

		//사각형의 위치와 크기를 나타내는 구조체
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		//그래픽 출력을 화면에 표시하기 위해 렌더링되는 영역을 정의하는 구조체
		mViewPort =
		{
			0.0f, 0.0f //뷰포트의 왼쪽 상단 모서리의 X좌표, Y좌표
			, (float)(winRect.right - winRect.left) //뷰포트의 너비
			, (float)(winRect.bottom - winRect.top) //뷰포트의 높이
			, 0.0f, 1.0f //뷰포트의 최소 깊이 값, 최대 깊이 값
		};

		BindViewPort(&mViewPort); // 설정할 뷰포트
		//OMSetRenderTargets(렌더타겟의 수, 렌더타겟 뷰의 배열, 깊이 스텐실 버퍼)
		mContext->OMSetRenderTargets(1, mRenderTarget->GetRTV().GetAddressOf(), mDepthStencil->GetDSV().Get());
	}

	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{
	}

	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};

		dxgiDesc.OutputWindow = hWnd; //hWnd에 그려준다.
		dxgiDesc.Windowed = true; //창모드면 true, 전체화면모드면 false
		dxgiDesc.BufferCount = desc->BufferCount; //교환 사슬이 사용할 버퍼의 갯수, 이중 버퍼링에서는 2개
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; // DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD; //스왑체인의 동작 방식 설정. DXGI_SWAP_EFFECT_DISCARD -> 후면 버퍼를 폐기하고 새로운 프레임을 그려 넣음.

		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //후면버퍼와 프론트 버퍼의 사용 방식을 제어. DXGI_USAGE_RENDER_TARGET_OUTPUT -> 후면 버퍼는 렌더 타겟으로 사용되고, 프론트 버퍼는 화면에 출력
		dxgiDesc.BufferDesc.Width = desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = desc->BufferDesc.Height;
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 240; //최대 프레임 설정
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1; //최소 프레임 설정
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED; //스왑체인의 후면 버퍼 크기 조정 방식. DXGI_MODE_SCALING_UNSPECIFIED -> 크기 조정 방식이 지정되지 않았음을 나타냄 이 경우 후면 버퍼의 크기는 자동으로 조정되지 않음.
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //스완 체인의 후면 버퍼의 스캔라인 순서 지정. DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED -> 후면 버퍼의 스캔 라인 순서는 자동으로 설정.

		dxgiDesc.SampleDesc.Count = 1; //스왑체인의 후면 버퍼에서 사용되는 멀티 샘플링 수준을 지정. 값이 높을수록 더 많은 샘플이 사용되어 품질이 향상 ex) 1, 2, 4, 8
		dxgiDesc.SampleDesc.Quality = 0; //멀티 샘플링의 수준을 지정하는 값

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

	bool GraphicDevice_Dx11::CreateTexture2D(const D3D11_TEXTURE2D_DESC* desc, void* data, ID3D11Texture2D** ppTexture2D)
	{
		if (FAILED(mDevice->CreateTexture2D(desc, nullptr, ppTexture2D)))
			return false;

		return true;
	}

	//인자 값이 fail때 오류 확인하기 위한 함수
	bool GraphicDevice_Dx11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(pInputElementDescs, NumElements
			, byteCode->GetBufferPointer()
			, byteCode->GetBufferSize()
			, ppInputLayout)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data)
	{

		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode)
	{
		ID3DBlob* errorBlob = nullptr;
		D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, funcName.c_str(), version.c_str(), 0, 0, ppCode, &errorBlob);

		if (errorBlob)
		{
			OutputDebugStringA((char*)(errorBlob->GetBufferPointer()));
			errorBlob->Release();
			errorBlob = nullptr;
		}

		return false;
	}

	bool GraphicDevice_Dx11::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader)
	{
		if (FAILED(mDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, nullptr, ppVertexShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader)
	{
		if (FAILED(mDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, nullptr, ppPixelShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ComputeShader** ppComputeShader)
	{
		if (FAILED(mDevice->CreateComputeShader(pShaderBytecode, BytecodeLength, nullptr, ppComputeShader)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateRasterizeState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
	{
		if (FAILED(mDevice->CreateRasterizerState(pRasterizerDesc, ppRasterizerState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState)
	{
		if (FAILED(mDevice->CreateDepthStencilState(pDepthStencilDesc, ppDepthStencilState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState)
	{
		if (FAILED(mDevice->CreateBlendState(pBlendStateDesc, ppBlendState)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CraeteDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
	{
		if (FAILED(mDevice->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
	{
		if (FAILED(mDevice->CreateShaderResourceView(pResource, pDesc, ppSRView)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
	{
		if (FAILED(mDevice->CreateRenderTargetView(pResource, pDesc, ppRTView)))
			return false;

		return true;
	}

	bool GraphicDevice_Dx11::CreateUnordedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView)
	{
		if (FAILED(mDevice->CreateUnorderedAccessView(pResource, pDesc, ppUAView)))
			return false;

		return true;
	}

	void GraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}

	void GraphicDevice_Dx11::BindRasterizeState(ID3D11RasterizerState* pRasterizerState)
	{
		mContext->RSSetState(pRasterizerState);
	}

	void GraphicDevice_Dx11::BindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState)
	{
		mContext->OMSetDepthStencilState(pDepthStencilState, 0);
	}

	void GraphicDevice_Dx11::BindBlendState(ID3D11BlendState* pBlendState)
	{
		mContext->OMSetBlendState(pBlendState, nullptr, 0xffffffff);
	}

	void GraphicDevice_Dx11::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		mContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
	}

	void GraphicDevice_Dx11::BindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}

	void GraphicDevice_Dx11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
	{
		mContext->IASetPrimitiveTopology(Topology);
	}

	void GraphicDevice_Dx11::BindVertexBuffer(UINT StartSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(StartSlot, 1, ppVertexBuffers, pStrides, pOffsets);
	}

	void GraphicDevice_Dx11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}

	void GraphicDevice_Dx11::BindVertexShader(ID3D11VertexShader* pVetexShader)
	{
		mContext->VSSetShader(pVetexShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindPixelShader(ID3D11PixelShader* pPixelShader)
	{
		mContext->PSSetShader(pPixelShader, 0, 0);
	}

	void GraphicDevice_Dx11::BindComputeShader(ID3D11ComputeShader* pComputeShader)
	{
		mContext->CSSetShader(pComputeShader, 0, 0);
	}

	void GraphicDevice_Dx11::Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ)
	{
		mContext->Dispatch(ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ);
	}

	void GraphicDevice_Dx11::SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		memcpy(subRes.pData, data, size); //메모리 복사
		mContext->Unmap(buffer, 0); //메모리 해제
	}

	void GraphicDevice_Dx11::BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}

	void GraphicDevice_Dx11::BindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
	}

	void GraphicDevice_Dx11::BindBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, size);
		mContext->Unmap(buffer, 0);
	}

	void GraphicDevice_Dx11::BindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::HS:
			mContext->HSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::DS:
			mContext->DSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::GS:
			mContext->GSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::PS:
			mContext->PSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::CS:
			mContext->CSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}

	void GraphicDevice_Dx11::BindUnorderedAccess(UINT slot, ID3D11UnorderedAccessView** ppUnorderedAccessViews, const UINT* pUAVInitialCounts)
	{
		mContext->CSSetUnorderedAccessViews(slot, 1, ppUnorderedAccessViews, pUAVInitialCounts);
	}

	void GraphicDevice_Dx11::BindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplers)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::HS:
			mContext->HSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::DS:
			mContext->DSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::GS:
			mContext->GSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::PS:
			mContext->PSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::CS:
			mContext->CSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}

	void GraphicDevice_Dx11::ClearTarget()
	{
		// render target clear
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTarget->GetRTV().Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencil->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		mContext->OMSetRenderTargets(1, mRenderTarget->GetRTV().GetAddressOf(), mDepthStencil->GetDSV().Get());
	}

	void GraphicDevice_Dx11::UpdateViewPort()
	{
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
	}
	void GraphicDevice_Dx11::Draw()
	{
	
	}

	void GraphicDevice_Dx11::Present()
	{
		// 렌더타겟에 있는 이미지를 화면에 그려준다
		mSwapChain->Present(0, 0);
	}
}