#pragma once
#include "GameEngine.h"
#include "kmGraphicDevice_Dx11.h"
#include "kmMesh.h"
#include "kmShader.h"
#include "kmConstantBuffer.h"

using namespace km::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern km::Mesh* mesh;
	extern km::Shader* shader;
	extern km::graphics::ConstantBuffer* constantBuffer;

	void Initialize();
	void Release();
}

