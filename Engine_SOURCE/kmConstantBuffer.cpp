#include "kmConstantBuffer.h"
#include "kmGraphicDevice_Dx11.h"

namespace km::graphics
{
    ConstantBuffer::ConstantBuffer(const eCBType type)
        : GPUBuffer()
        , mType(type)
    {
    }

    ConstantBuffer::~ConstantBuffer()
    {
    }

    bool ConstantBuffer::Create(size_t size)
    {
        desc.ByteWidth = size;
        desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
        desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        km::graphics::GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

        return false;
    }

    void ConstantBuffer::SetData(void* data)
    {
        km::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
    }

    void ConstantBuffer::Bind(eShaderStage stage)
    {
        km::graphics::GetDevice()->BindConstantBuffer(stage, mType, buffer.Get());
    }
}