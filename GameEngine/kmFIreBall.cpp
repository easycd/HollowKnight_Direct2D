#include "kmFIreBall.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"

namespace km
{
	FIreBall::FIreBall()
		: mTime(0.0f)
	{
	}

	FIreBall::~FIreBall()
	{
	}

	void FIreBall::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> FireBall = Resources::Load<Texture>(L"FireBall", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\FireBall\\FireBall.png");
		mAnimation->Create(L"FireBall", FireBall, Vector2(0.0f, 0.0f), Vector2(151.0f, 164.0f), 8, Vector2(0.0f, 0.0f), 0.1f);

		mTransform->SetScale(Vector3(0.12f, 0.12f, 0.0f));
		mCollider->SetSize(Vector2(0.6f, 0.6f));
		GameObject::Initialize();
	}

	void FIreBall::Update()
	{
		mTime += Time::DeltaTime();
		Pos = mTransform->GetPosition();

		if (mTime > 3.0f)
		{
			Destroy();
		}

		if (Set_Check0)
		{
			Pos.x -= 0.3f * Time::DeltaTime();
		}
		if (Set_Check1)
		{
			Pos.x += 0.3f * Time::DeltaTime();
		}
		if (Set_Check2)
		{
			Pos.x -= 0.3f * Time::DeltaTime();
		}
		if (Set_Check3)
		{
			Pos.x += 0.3f * Time::DeltaTime();
		}
		if (Set_Check4)
		{
			Pos.x -= 0.3f * Time::DeltaTime();
		}
		if (Set_Check5)
		{

		}
		if (Set_Check6)
		{

		}
		if (Set_Check7)
		{

		}
		if (Set_Check8)
		{
			Pos.x += 0.3f * Time::DeltaTime();
		}

		mTransform->SetPosition(Pos);

		GameObject::Update();
	}

	void FIreBall::Set0()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check0 = true;
	}

	void FIreBall::Set1()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check1 = true;
	}

	void FIreBall::Set2()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check2 = true;
	}

	void FIreBall::Set3()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check3 = true;
	}

	void FIreBall::Set4()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check4 = true;
	}

	void FIreBall::Set5()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check5 = true;
	}

	void FIreBall::Set6()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check6 = true;
	}

	void FIreBall::Set7()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check7 = true;
	}

	void FIreBall::Set8()
	{
		mAnimation->PlayAnimation(L"FireBall", true);
		Set_Check8 = true;
	}

	void FIreBall::Destroy()
	{
		object::Destroy(this);
	}
}