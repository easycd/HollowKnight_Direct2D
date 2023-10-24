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
		:Move_Timing(0.0f)
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

		std::shared_ptr<Texture> LightGuid_00 = Resources::Load<Texture>(L"LightGuid_On", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Spear\\Guid_Light\\00.png");
		std::shared_ptr<Texture> LightGuid_01 = Resources::Load<Texture>(L"LightGuid_On", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Spear\\Guid_Light\\01.png");
		std::shared_ptr<Texture> LightGuid_02 = Resources::Load<Texture>(L"LightGuid_On", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Spear\\Guid_Light\\02.png");

		mAnimation->Create(L"LightGuid_00", LightGuid_00, Vector2(0.0f, 0.0f), Vector2(68.0f, 500.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"LightGuid_01", LightGuid_01, Vector2(0.0f, 0.0f), Vector2(80.0f, 500.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"LightGuid_02", LightGuid_02, Vector2(0.0f, 0.0f), Vector2(80.0f, 500.0f), 1, Vector2(0.0f, 0.0f), 0.1f);

		mAnimation->CompleteEvent(L"LightGuid_01") = std::bind(&GuidLight::GuidLight_01, this);

		mTransform->SetScale(Vector3(0.1f, 6.0f, 0.0f));
		GameObject::Initialize();
	}
	void GuidLight::Update()
	{
		Move_Timing += Time::DeltaTime();

		if (Move_Timing > 2.0f)
			Destroy();

		GameObject::Update();
	}

	void GuidLight::GuidLight_00()
	{
		if (GuidLight_01_Check)
		{
			mAnimation->PlayAnimation(L"LightGuid_01", true);
			GuidLight_01_Check = false;
		}
	}

	void GuidLight::GuidLight_01()
	{
		if (GuidLight_02_Check)
		{
			mAnimation->PlayAnimation(L"LightGuid_02", true);
			GuidLight_02_Check = false;
		}
	}

	void GuidLight::GuidLight_02()
	{
	}

	void GuidLight::Destroy()
	{
		object::Destroy(this);
	}
}