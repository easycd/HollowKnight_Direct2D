#include "kmDarkWhip.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"

namespace km
{
	DarkWhip::DarkWhip()
	{
	}
	DarkWhip::~DarkWhip()
	{
	}
	void DarkWhip::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> DarkWhip_Up_Left = Resources::Load<Texture>(L"DarkWhip_Up_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Dark_Whip\\Left\\DarkWhip_Obj_Up_Left.png");
		std::shared_ptr<Texture> DarkWhip_Up_Right = Resources::Load<Texture>(L"DarkWhip_Up_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Dark_Whip\\Right\\DarkWhip_Obj_Up_Right.png");
		std::shared_ptr<Texture> DarkWhip_Down_Left = Resources::Load<Texture>(L"DarkWhip_Down_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Dark_Whip\\Left\\DarkWhip_Obj_Down_Left.png");
		std::shared_ptr<Texture> DarkWhip_Down_Right = Resources::Load<Texture>(L"DarkWhip_Down_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Dark_Whip\\Right\\DarkWhip_Obj_Down_Right.png");

		mAnimation->Create(L"DarkWhip_Up_Left", DarkWhip_Up_Left, Vector2(0.0f, 0.0f), Vector2(483.0f, 501.0f), 9, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"DarkWhip_Up_Right", DarkWhip_Up_Right, Vector2(0.0f, 0.0f), Vector2(483.0f, 501.0f), 9, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"DarkWhip_Down_Left", DarkWhip_Down_Left, Vector2(0.0f, 0.0f), Vector2(483.0f, 501.0f), 9, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"DarkWhip_Down_Right", DarkWhip_Down_Right, Vector2(0.0f, 0.0f), Vector2(483.0f, 501.0f), 9, Vector2(0.0f, 0.0f), 0.1f);


		mAnimation->CompleteEvent(L"DarkWhip_Up_Left") = std::bind(&DarkWhip::Destroy, this);
		mAnimation->CompleteEvent(L"DarkWhip_Up_Right") = std::bind(&DarkWhip::Destroy, this);
		mAnimation->CompleteEvent(L"DarkWhip_Down_Left") = std::bind(&DarkWhip::Destroy, this);
		mAnimation->CompleteEvent(L"DarkWhip_Down_Right") = std::bind(&DarkWhip::Destroy, this);

		mCollider->SetSize(Vector2(0.75f, 0.4f));
		mTransform->SetScale(Vector3(0.75f, 0.4f, 0.0f));
		GameObject::Initialize();
	}
	void DarkWhip::Update()
	{

		GameObject::Update();
	}
	void DarkWhip::DarkWhip_On_Up_Left()
	{
		if (DarkWhip_On_Up_Left_Check)
		{
			mAnimation->PlayAnimation(L"DarkWhip_Up_Left", true);
			DarkWhip_On_Up_Left_Check = false;
		}
		mCollider->SetCenter(Vector2(-0.1f, 0.0f));
	}
	void DarkWhip::DarkWhip_On_Up_Right()
	{
		if (DarkWhip_On_Up_Right_Check)
		{
			mAnimation->PlayAnimation(L"DarkWhip_Up_Right", true);
			DarkWhip_On_Up_Right_Check = false;
		}
		mCollider->SetCenter(Vector2(0.1f, 0.0f));
	}
	void DarkWhip::DarkWhip_On_Down_Left()
	{
		if (DarkWhip_On_Down_Left_Check)
		{
			mAnimation->PlayAnimation(L"DarkWhip_Down_Left", true);
			DarkWhip_On_Down_Left_Check = false;
		}
		mCollider->SetCenter(Vector2(-0.1f, 0.0f));
	}
	void DarkWhip::DarkWhip_On_Down_Right()
	{
		if (DarkWhip_On_Down_Right_Check)
		{
			mAnimation->PlayAnimation(L"DarkWhip_Down_Right", true);
			DarkWhip_On_Down_Right_Check = false;
		}
		mCollider->SetCenter(Vector2(0.1f, 0.0f));
	}
	void DarkWhip::Destroy()
	{
		object::Destroy(this);
	}
}