#include "kmLightCircleobj_Guid.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"

#include "kmLightCircle.h"

namespace km
{
	LightCircleobj_Guid::LightCircleobj_Guid()
		: Guid_On_Timing(0.0f)
	{
	}
	LightCircleobj_Guid::~LightCircleobj_Guid()
	{
	}
	void LightCircleobj_Guid::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Guid_On = Resources::Load<Texture>(L"Guid_On", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Effect\\Light_Circle\\LightCircle_On.png");
		std::shared_ptr<Texture> Guid_End = Resources::Load<Texture>(L"Guid_End", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Effect\\Light_Circle\\LightCircle_End.png");

		mAnimation->Create(L"Guid_On", Guid_On, Vector2(0.0f, 0.0f), Vector2(344.0f, 344.0f), 4, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Guid_End", Guid_End, Vector2(0.0f, 0.0f), Vector2(479.0f, 479.0f), 1, Vector2(0.0f, 0.0f), 0.1f);

		mAnimation->CompleteEvent(L"Guid_End") = std::bind(&LightCircleobj_Guid::Destroy, this);

		mTransform->SetScale(Vector3(0.4f, 0.4f, 0.0f));
		GameObject::Initialize();
	}
	void LightCircleobj_Guid::Update()
	{
		mPos = mTransform->GetPosition();

		Guid_On_Timing += Time::DeltaTime();

		if (Guid_On_Timing > mTime)
			Guid_End();

		GameObject::Update();
	}
	void LightCircleobj_Guid::Guid_On()
	{
		if (Guid_On_Check)
		{
			mAnimation->PlayAnimation(L"Guid_On", false);
			Guid_On_Check = false;
		}
	}
	void LightCircleobj_Guid::Guid_End()
	{
		if (Guid_End_Check)
		{
			Circle();
			mAnimation->PlayAnimation(L"Guid_End", true);
			Guid_End_Check = false;
		}
	}
	void LightCircleobj_Guid::Circle()
	{
		mCircle = object::Instantiate<LightCircle>(eLayerType::BossObj);
		mCircle->GetComponent<Transform>()->SetPosition(mPos);
		mCircle->Circle_On();
	}
	void LightCircleobj_Guid::Destroy()
	{
		object::Destroy(this);
	}
}