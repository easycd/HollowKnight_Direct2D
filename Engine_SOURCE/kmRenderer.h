#pragma once
#include "GameEngine.h"
#include "kmGraphicDevice_Dx11.h"
#include "kmMesh.h"
#include "kmShader.h"
#include "kmConstantBuffer.h"
#include "kmCamera.h"
#include "kmLight.h"

using namespace km::math;
using namespace km::graphics;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
	};

	extern km::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<km::Light*> lights;
	extern km::Camera* mainCamera;
	extern std::vector<km::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void BindLights();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}

