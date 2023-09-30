#include "kmAirDash_Effect.h"
#include "kmAnimator.h"
#include "kmMeshRenderer.h"
#include "kmTransform.h"
#include "kmObject.h"
#include "kmResources.h"

namespace km
{
	AirDash_Effect::AirDash_Effect()
	{
	}

	AirDash_Effect::~AirDash_Effect()
	{
	}

	void AirDash_Effect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> AirDash_Effect = Resources::Load<Texture>(L"AirDash_Effect", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Gimm_Effect\\AirDash_Effect\\AirDash_Effect.png");
		mAnimation->Create(L"AirDash_Effect", AirDash_Effect, Vector2(0.0f, 0.0f), Vector2(450.0f, 573.0f), 1, Vector2(0.0f, 0.0f), 0.1f);

		mAnimation->CompleteEvent(L"AirDash_Effect") = std::bind(&AirDash_Effect::Destroy, this);

		mTransform->SetScale(Vector3(0.3f, 0.4f, 0.0f));
		GameObject::Initialize();
	}

	void AirDash_Effect::Update()
	{

		GameObject::Update();
	}

	void AirDash_Effect::PlayEffect()
	{
		mAnimation->PlayAnimation(L"AirDash_Effect", true);
	}

	void AirDash_Effect::Destroy()
	{
		object::Destroy(this);
	}

}
