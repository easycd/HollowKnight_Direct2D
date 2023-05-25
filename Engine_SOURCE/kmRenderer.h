#pragma once
#include "GameEngine.h"
#include "kmGraphicDevice_Dx11.h"

using namespace km::math;
namespace km::renderer
{
	struct Vertex
	{
		Vector2 pos;
		Vector2 color;
	};

	extern Vertex vertexes[];
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;

	void Initialize();
}

