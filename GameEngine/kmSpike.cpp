#include "kmSpike.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"

namespace km
{
	Spike::Spike()
		:Spike_On_Timing(0.0f)
	{
	}
	Spike::~Spike()
	{
	}
	void Spike::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Vessel_Spike_On = Resources::Load<Texture>(L"Vessel_Spike_On", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Spike\\On\\Spike_On.png");
		std::shared_ptr<Texture> Vessel_Spike_End = Resources::Load<Texture>(L"Vessel_Spike_End", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Spike\\End\\Spike_End.png");

		mAnimation->Create(L"Vessel_Spike_On", Vessel_Spike_On, Vector2(0.0f, 0.0f), Vector2(262.0f, 839.0f), 7, Vector2(0.0f, 0.0f), 0.08f);
		mAnimation->Create(L"Vessel_Spike_End", Vessel_Spike_End, Vector2(0.0f, 0.0f), Vector2(262.0f, 839.0f), 15, Vector2(0.0f, 0.0f), 0.08f);

		mAnimation->CompleteEvent(L"Vessel_Spike_End") = std::bind(&Spike::Destroy, this);

		mTransform->SetScale(Vector3(0.25f, 0.9f, 0.0f));
		GameObject::Initialize();
	}
	void Spike::Update()
	{
		Spike_On_Timing += Time::DeltaTime();

		if (Spike_On_Timing > 1.0f)
			Spike_End();

		GameObject::Update();
	}
	void Spike::Spike_On()
	{
		if (Spike_On_Check)
		{
			mAnimation->PlayAnimation(L"Vessel_Spike_On", false);
			Spike_On_Check = false;
		}
	}
	void Spike::Spike_End()
	{
		if (Spike_End_Check)
		{
			mCollider = AddComponent<Collider2D>();
			mCollider->SetSize(Vector2(0.25f, 0.9f));
			mAnimation->PlayAnimation(L"Vessel_Spike_End", true);
			Spike_End_Check = false;
		}
	}

	void Spike::Destroy()
	{
		object::Destroy(this);
	}
}