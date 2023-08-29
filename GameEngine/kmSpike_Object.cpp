#include "kmSpike_Object.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"

namespace km
{
	Spike_Object::Spike_Object()
		: mSpike_On_Delay(0.0f)
	{
	}

	Spike_Object::~Spike_Object()
	{
	}

	void Spike_Object::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Spike_On_Delay = Resources::Load<Texture>(L"Spike_On_Delay", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\Spike\\Spike_On_Delay\\Spike_On_Delay.png");
		std::shared_ptr<Texture> Spike_On = Resources::Load<Texture>(L"Spike_On", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\Spike\\Spike_On\\Spike_On.png");
		std::shared_ptr<Texture> Spike_Shot = Resources::Load<Texture>(L"Spike_Shot", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\Spike\\Spike_Shot\\Spike_Shot.png");
		std::shared_ptr<Texture> Spike_Loop = Resources::Load<Texture>(L"Spike_Loop", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\Spike\\Spike_Loop\\Spike_Loop.png");
		std::shared_ptr<Texture> Spike_Remove = Resources::Load<Texture>(L"Spike_Remove", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\Spike\\Spkile_Remove\\Spike_Remove.png");
		std::shared_ptr<Texture> Spike_End = Resources::Load<Texture>(L"Spike_End", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Object\\Spike\\Spike_End\\Spike_End.png");
		
		mAnimation->Create(L"Spike_On_Delay", Spike_On_Delay, Vector2(0.0f, 0.0f), Vector2(148.0f, 569.0f), 3, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Spike_On", Spike_On, Vector2(0.0f, 0.0f), Vector2(148.0f, 569.0f), 4, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Spike_Shot", Spike_Shot, Vector2(0.0f, 0.0f), Vector2(148.0f, 1313.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Spike_Loop", Spike_Loop, Vector2(0.0f, 0.0f), Vector2(148.0f, 941.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Spike_Remove", Spike_Remove, Vector2(0.0f, 0.0f), Vector2(148.0f, 793.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Spike_End", Spike_End, Vector2(0.0f, 0.0f), Vector2(148.0f, 569.0f), 1, Vector2(0.0f, 0.0f), 0.1f);

		//mAnimation->CompleteEvent(L"Spike_On") = std::bind(&Spike_Object::Spike_Shot, this);
		//mAnimation->CompleteEvent(L"Spike_Shot") = std::bind(&Spike_Object::Spike_Loop, this);
		//mAnimation->CompleteEvent(L"Spike_Remove") = std::bind(&Spike_Object::Spike_End, this);
		//mAnimation->CompleteEvent(L"Spike_End") = std::bind(&Spike_Object::Destroy, this);


		mTransform->SetPosition(Vector3(0.0f, -0.25f, 0.1f));
		mTransform->SetScale(Vector3(0.1f, 0.7f, 0.0f));

		mCollider->SetSize(Vector2(0.7f, 0.8f));
		GameObject::Initialize();
	}

	void Spike_Object::Update()
	{
		if (Spike_On_Delay_Time_Check)
		{
			mSpike_On_Delay += Time::DeltaTime();

			if (mSpike_On_Delay > 1.0f)
			{
				mSpike_On_Delay = 0.0f;
				Spike_On();
			}
		}

		if (Spike_Loop_Delay_Time_Check)
		{
			mSpike_Loop_Delay += Time::DeltaTime();

			if (mSpike_Loop_Delay > 3.0f)
			{
				mSpike_Loop_Delay = 0.0f;
				Spike_Remove();
			}
		}


		GameObject::Update();
	}

	void Spike_Object::Spike_On_Delay()
	{
		if (Spike_On_Delay_Check)
		{
			mAnimation->PlayAnimation(L"Spike_On_Delay", false);
			Spike_On_Delay_Time_Check = true;
		}
	}

	void Spike_Object::Spike_On()
	{
		Spike_On_Delay_Time_Check = false;

		if (Spike_On_Check)
		{
			mAnimation->PlayAnimation(L"Spike_On", true);
			Spike_On_Check = false;
		}

	}

	void Spike_Object::Spike_Shot()
	{
		if (Spike_Shot_Check)
		{
			mAnimation->PlayAnimation(L"Spike_Shot", true);
			Spike_Shot_Check = false;
		}
	}

	void Spike_Object::Spike_Loop()
	{
		if (Spike_Loop_Check)
		{
			mAnimation->PlayAnimation(L"Spike_Loop", false);
			Spike_Loop_Check = false;
			Spike_Loop_Delay_Time_Check = true;
		}
	}
	void Spike_Object::Spike_Remove()
	{
		Spike_Loop_Delay_Time_Check = false;
		if (Spike_Remove_Check)
		{
			mAnimation->PlayAnimation(L"Spike_Remove", true);
			Spike_Remove_Check = false;
		}
	}

	void Spike_Object::Spike_End()
	{
		if (Spike_End_Check)
		{
			mAnimation->PlayAnimation(L"Spike_End", true);
			Spike_End_Check = false;
		}
	}

	void Spike_Object::Destroy()
	{
		object::Destroy(this);
	}

}
