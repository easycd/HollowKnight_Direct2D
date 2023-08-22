#include "kmMeshRenderer.h"
#include "kmGameObject.h"
#include "kmTransform.h"
#include "kmRenderer.h"
#include "kmAnimator.h"
#include "kmResources.h"

namespace km
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	void MeshRenderer::Initialize()
	{
	}
	void MeshRenderer::Update()
	{
	}
	void MeshRenderer::LateUpdate()
	{
	}
	void MeshRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->BindConstantBuffer();

		mMesh->BindBuffer();
		mMaterial->Binds();

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
		{
			animator->Binds();
		}

		mMesh->Render();

		mMaterial->Clear();
	}
}
