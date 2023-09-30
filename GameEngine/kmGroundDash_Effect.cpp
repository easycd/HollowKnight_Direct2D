#include "kmGroundDash_Effect.h"
#include "kmAnimator.h"
#include "kmMeshRenderer.h"
#include "kmTransform.h"
#include "kmObject.h"
#include "kmResources.h"


namespace km
{
	GroundDash_Effect::GroundDash_Effect()
	{
	}

	GroundDash_Effect::~GroundDash_Effect()
	{
	}

	void GroundDash_Effect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> GroundDash_Effect_Left = Resources::Load<Texture>(L"GroundDash_Effect_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Gimm_Effect\\GroundDash_Effect\\Left\\GroundDash_Effect_Left.png");
		std::shared_ptr<Texture> GroundDash_Effect_Right = Resources::Load<Texture>(L"GroundDash_Effect_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Gimm_Effect\\GroundDash_Effect\\Right\\GroundDash_Effect_Right.png");
		mAnimation->Create(L"GroundDash_Effect_Left", GroundDash_Effect_Left, Vector2(0.0f, 0.0f), Vector2(832.0f, 369.0f), 6, Vector2(0.0f, 0.0f), 0.07f);
		mAnimation->Create(L"GroundDash_Effect_Right", GroundDash_Effect_Right, Vector2(0.0f, 0.0f), Vector2(832.0f, 369.0f), 6, Vector2(0.0f, 0.0f), 0.07f);

		mAnimation->CompleteEvent(L"GroundDash_Effect_Left") = std::bind(&GroundDash_Effect::Destroy, this);
		mAnimation->CompleteEvent(L"GroundDash_Effect_Right") = std::bind(&GroundDash_Effect::Destroy, this);

		mTransform->SetScale(Vector3(0.4f, 0.3f, 0.0f));
		GameObject::Initialize();
	}

	void GroundDash_Effect::Update()
	{

		GameObject::Update();
	}

	void GroundDash_Effect::PlayEffect_Left()
	{
		mAnimation->PlayAnimation(L"GroundDash_Effect_Left", true);
	}

	void GroundDash_Effect::PlayEffect_Right()
	{
		mAnimation->PlayAnimation(L"GroundDash_Effect_Right", true);
	}

	void GroundDash_Effect::Destroy()
	{
		object::Destroy(this);
	}
}