#include "kmRoarEffect.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"

namespace km
{
	RoarEffect::RoarEffect()
	{
	}
	RoarEffect::~RoarEffect()
	{
	}
	void RoarEffect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Roar_Effect_On = Resources::Load<Texture>(L"Roar_Effect_On", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Effect\\Light_Circle\\LightCircle_On.png");
		std::shared_ptr<Texture> Roar_Effect_Start = Resources::Load<Texture>(L"Roar_Effect_Start", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Effect\\Light_Circle\\LightCircle_Start.png");
		std::shared_ptr<Texture> Roar_Effect_End = Resources::Load<Texture>(L"Roar_Effect_Start", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Effect\\Light_Circle\\LightCircle_End.png");

		mAnimation->Create(L"Roar_Effect_On", Roar_Effect_On, Vector2(0.0f, 0.0f), Vector2(344.0f, 344.0f), 4, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Roar_Effect_Start", Roar_Effect_Start, Vector2(0.0f, 0.0f), Vector2(374.0f, 387.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Roar_Effect_End", Roar_Effect_End, Vector2(0.0f, 0.0f), Vector2(479.0f, 479.0f), 1, Vector2(0.0f, 0.0f), 0.1f);


		GameObject::Initialize();
	}
	void RoarEffect::Update()
	{

		GameObject::Update();
	}
	void RoarEffect::Roar_Effect_On()
	{
		if (Roar_Effect_On_Check)
		{
			mAnimation->PlayAnimation(L"Roar_Effect_On", true);
			Roar_Effect_On_Check = false;
		}
	}
	void RoarEffect::Roar_Effect_Start()
	{
		if (Roar_Effect_Start_Check)
		{
			mAnimation->PlayAnimation(L"Roar_Effect_Start", true);
			Roar_Effect_Start_Check = false;
		}
	}
	void RoarEffect::Roar_Effect_End()
	{
		if (Roar_Effect_End_Check)
		{
			mAnimation->PlayAnimation(L"Roar_Effect_End", true);
			Roar_Effect_End_Check = false;
		}
	}
	void RoarEffect::Destroy()
	{
		object::Destroy(this);
	}
}