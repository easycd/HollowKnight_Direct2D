#include "kmGuidLight.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"

namespace km
{
	GuidLight::GuidLight()
	{
	}
	GuidLight::~GuidLight()
	{
	}
	void GuidLight::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> LightGuid_On = Resources::Load<Texture>(L"LightGuid_On", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Spear\\guid_Light\\GuidLight.png");
		mAnimation->Create(L"LightGuid_On", LightGuid_On, Vector2(0.0f, 0.0f), Vector2(88.0f, 500.0f), 3, Vector2(0.0f, 0.0f), 0.01f);

		GameObject::Initialize();
	}
	void GuidLight::Update()
	{

		GameObject::Update();
	}
	void GuidLight::On()
	{
		if (On_Check)
		{
			mAnimation->PlayAnimation(L"LightGuid_On", true);
			On_Check = false;
		}
	}
	void GuidLight::Destroy()
	{
		object::Destroy(this);
	}
}