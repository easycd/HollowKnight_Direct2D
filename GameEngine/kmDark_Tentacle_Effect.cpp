#include "kmDark_Tentacle_Effect.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"

namespace km
{
	Dark_Tentacle_Effect::Dark_Tentacle_Effect()
		:Destroy_Time(0.0f)
	{
	}
	Dark_Tentacle_Effect::~Dark_Tentacle_Effect()
	{
	}
	void Dark_Tentacle_Effect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Dark_Tentacle_Left = Resources::Load<Texture>(L"Dark_Tentacle_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Effect\\Dark_Whip_Pattern\\Left\\Dark_Whip_Left.png");
		std::shared_ptr<Texture> Dark_Tentacle_Right = Resources::Load<Texture>(L"Dark_Tentacle_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Effect\\Dark_Whip_Pattern\\Right\\Dark_Whip_Right.png");

		mAnimation->Create(L"Dark_Tentacle_Left", Dark_Tentacle_Left, Vector2(0.0f, 0.0f), Vector2(471.0f, 396.0f), 4, Vector2(0.0f, 0.0f), 0.1f);		
		mAnimation->Create(L"Dark_Tentacle_Right", Dark_Tentacle_Right, Vector2(0.0f, 0.0f), Vector2(471.0f, 396.0f), 4, Vector2(0.0f, 0.0f), 0.1f);	

		mTransform->SetScale(Vector3(0.4f, 0.4f, 0.0f));
		GameObject::Initialize();
	}
	void Dark_Tentacle_Effect::Update()
	{
		Destroy_Time += Time::DeltaTime();

		//if (Destroy_Time > 1.0f)
		//	Destroy();

		GameObject::Update();
	}
	void Dark_Tentacle_Effect::On_Left()
	{
		if (On_Left_Check)
		{
			mAnimation->PlayAnimation(L"Dark_Tentacle_Left", true);
			On_Left_Check = false;
		}
	}
	void Dark_Tentacle_Effect::On_Right()
	{
		if (On_Right_Check)
		{
			mAnimation->PlayAnimation(L"Dark_Tentacle_Right", true);
			On_Right_Check = false;
		}
	}
	void Dark_Tentacle_Effect::Destroy()
	{
		object::Destroy(this);
	}
}