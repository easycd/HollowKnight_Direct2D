#pragma once
#include "GameEngine.h"
#include "kmGraphicDevice_Dx11.h"
#include "kmMesh.h"
#include "kmShader.h"
#include "kmConstantBuffer.h"

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

	extern Vertex vertexes[];
	extern km::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	void Release();
}

