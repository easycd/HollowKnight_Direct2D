#include "kmMaterial.h"


namespace km::graphics
{
	Material::Material()
		: Resource(km::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
		, mMode(eRenderingMode::Opaque)
	{

	}

	Material::~Material()
	{

	}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::Binds()
	{
		if (mTexture)
			mTexture->BindShaderResource(eShaderStage::PS, 0);

		if (mShader)
			mShader->Binds();
	}

	void Material::Clear()
	{
		mTexture->Clear();
	}
}
