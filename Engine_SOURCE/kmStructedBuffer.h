#pragma once
#include "kmEntity.h"
#include "kmGraphics.h"

namespace km::graphics
{
	class StructedBuffer : public GPUBuffer
	{
	public:
		StructedBuffer();
		~StructedBuffer();

		bool Create(UINT size, UINT stride, eSRVType type);
		void SetData(void* data, UINT stride);
		void Bind(eShaderStage stage, UINT slot);

		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		eSRVType mType;

		UINT mSize;
		UINT mStride;
	};
}