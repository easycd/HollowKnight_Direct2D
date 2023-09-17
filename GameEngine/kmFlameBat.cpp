#include "kmFlameBat.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"
#include "kmCollisionManager.h"

namespace km
{
	FlameBat::FlameBat()
		: mDirection(0)
		, mTime(0.0f)
		, mExport_Timing(0.0f)
		, mGetDir(0)
	{
	}
	FlameBat::~FlameBat()
	{
	}
	void FlameBat::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Flame_Left_On = Resources::Load<Texture>(L"Flame_Left_On", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\FlameBat\\FlameBat_On\\Left\\FlameBat_Left_On.png");
		std::shared_ptr<Texture> Flame_Right_On = Resources::Load<Texture>(L"Flame_Right_On", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\FlameBat\\FlameBat_On\\Right\\FlameBat_Right_On.png");
		std::shared_ptr<Texture> Flame_Left_Loop = Resources::Load<Texture>(L"Flame_Left_Loop", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\FlameBat\\FlameBat_Loop\\Left\\FlameBat_Left_Loop.png");
		std::shared_ptr<Texture> Flame_Right_Loop = Resources::Load<Texture>(L"Flame_Right_Loop", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\FlameBat\\FlameBat_Loop\\Right\\FlameBat_Right_Loop.png");

		mAnimation->Create(L"Flame_Left_On", Flame_Left_On, Vector2(0.0f, 0.0f), Vector2(340.0f, 246.0f), 5, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Flame_Right_On", Flame_Right_On, Vector2(0.0f, 0.0f), Vector2(340.0f, 246.0f), 5, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Flame_Left_Loop", Flame_Left_Loop, Vector2(0.0f, 0.0f), Vector2(340.0f, 246.0f), 4, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Flame_Right_Loop", Flame_Right_Loop, Vector2(0.0f, 0.0f), Vector2(340.0f, 246.0f), 4, Vector2(0.0f, 0.0f), 0.1f);

		mAnimation->CompleteEvent(L"Flame_Left_On") = std::bind(&FlameBat::Loop, this);
		mAnimation->CompleteEvent(L"Flame_Right_On") = std::bind(&FlameBat::Loop, this);

		//mAnimation->CompleteEvent(L"Flame_Left_Loop") = std::bind(&FlameBat::Destroy, this);
		//mAnimation->CompleteEvent(L"Flame_Right_Loop") = std::bind(&FlameBat::Destroy, this);
		
		mTransform->SetScale(Vector3(0.15f, 0.15f, 0.0f));
		mCollider->SetSize(Vector2(0.6f, 0.5f));

		GameObject::Initialize();
	}

	void FlameBat::Update()
	{
		mTime += Time::DeltaTime();

		if (mDirection == 0)
		{
			mFlamePos = mTransform->GetPosition();
			mFlamePos.x -= 0.6f * Time::DeltaTime();
			mTransform->SetPosition(mFlamePos);
		}

		if (mDirection == 1)
		{
			mFlamePos = mTransform->GetPosition();
			mFlamePos.x += 0.6f * Time::DeltaTime();
			mTransform->SetPosition(mFlamePos);
		}

		if (mTime > 3.0f)
			Destroy();

		GameObject::Update();
	}
	void FlameBat::OnCollisionEnter(Collider2D* other)
	{

	}
	void FlameBat::OnCollisionStay(Collider2D* other)
	{

	}

	void FlameBat::OnCollisionExit(Collider2D* other)
	{

	}

	void FlameBat::On_Left()
	{
		if (On_Check)
		{
			mAnimation->PlayAnimation(L"Flame_Left_On", true);
			On_Check = false;
			mDirection = 0;
		}
	}
	void FlameBat::On_Right()
	{
		if (On_Check)
		{
			mAnimation->PlayAnimation(L"Flame_Right_On", true);
			On_Check = false;
			mDirection = 1;
		}
	}

	void FlameBat::Loop()
	{
		if (Loop_Check && mDirection == 0)
		{
			mAnimation->PlayAnimation(L"Flame_Left_Loop", true);
			Loop_Check = false;
		}

		if (Loop_Check && mDirection == 1)
		{
			mAnimation->PlayAnimation(L"Flame_Right_Loop", true);
			Loop_Check = false;
		}
	}
	void FlameBat::Destroy()
	{
		object::Destroy(this);
	}
}