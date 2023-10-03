#include "kmPlayerEffet.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmMeshRenderer.h"
#include "kmObject.h"

namespace km
{
	PlayerEffet::PlayerEffet()
		:mTime(0.0f)
	{

	}
	PlayerEffet::~PlayerEffet()
	{
	}

	void PlayerEffet::Initialize()
	{
		mTransform = GetComponent<Transform>();
		at = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Slash_Left = Resources::Load<Texture>(L"Slash_Left", L"..\\Resources\\Knight\\Effect\\Slash\\Left\\Slash_Left.png");
		std::shared_ptr<Texture> Slash_Right = Resources::Load<Texture>(L"Slash_Right", L"..\\Resources\\Knight\\Effect\\Slash\\Right\\Slash_Right.png");

		std::shared_ptr<Texture> UP_Slash_Left = Resources::Load<Texture>(L"UP_Slash_Left", L"..\\Resources\\Knight\\Effect\\Up_Slash\\Left\\UP_Slash_Left.png");
		std::shared_ptr<Texture> UP_Slash_Right = Resources::Load<Texture>(L"UP_Slash_Right", L"..\\Resources\\Knight\\Effect\\Up_Slash\\Right\\UP_Slash_Right.png");

		std::shared_ptr<Texture> Down_Slash_Left = Resources::Load<Texture>(L"Down_Slash_Left", L"..\\Resources\\Knight\\Effect\\Down_Slash\\Left\\Down_Slash_Left.png");
		std::shared_ptr<Texture> Down_Slash_Right = Resources::Load<Texture>(L"Down_Slash_Right", L"..\\Resources\\Knight\\Effect\\Down_Slash\\Right\\Down_Slash_Right.png");


		at->Create(L"Slash_Left", Slash_Left, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, 0.0f), 0.1f);
		at->Create(L"Slash_Left", Slash_Left, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, 0.0f), 0.1f);

		at->Create(L"UP_Slash_Left", UP_Slash_Left, Vector2(0.0f, 0.0f), Vector2(169.0f, 192.0f), 6, Vector2(0.0f, 0.0f), 0.1f);
		at->Create(L"UP_Slash_Left", UP_Slash_Left, Vector2(0.0f, 0.0f), Vector2(169.0f, 192.0f), 6, Vector2(0.0f, 0.0f), 0.1f);

		at->Create(L"Down_Slash_Left", Down_Slash_Left, Vector2(0.0f, 0.0f), Vector2(182.0f, 209.0f), 6, Vector2(0.0f, 0.0f), 0.1f);
		at->Create(L"Down_Slash_Left", Down_Slash_Left, Vector2(0.0f, 0.0f), Vector2(182.0f, 209.0f), 6, Vector2(0.0f, 0.0f), 0.1f);

		at->CompleteEvent(L"Slash_Left") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"Slash_Left") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"UP_Slash_Left") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"UP_Slash_Left") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"Down_Slash_Left") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"Down_Slash_Left") = std::bind(&PlayerEffet::Destroy, this);


		GameObject::Initialize();
	}

	void PlayerEffet::Update()
	{


		GameObject::Update();
	}

	void PlayerEffet::Slash_Left()
	{
		at->PlayAnimation(L"Slash_Left", true);
	}

	void PlayerEffet::Slash_Right()
	{
		at->PlayAnimation(L"Slash_Right", true);
	}

	void PlayerEffet::UP_Slash_Left()
	{
		at->PlayAnimation(L"UP_Slash_Left", true);
	}

	void PlayerEffet::UP_Slash_Right()
	{
		at->PlayAnimation(L"UP_Slash_Left", true);
	}

	void PlayerEffet::Down_Slash_Left()
	{
		at->PlayAnimation(L"Down_Slash_Left", true);
	}

	void PlayerEffet::Down_Slash_Right()
	{
		at->PlayAnimation(L"Down_Slash_Left", true);
	}

	void PlayerEffet::Destroy()
	{
		object::Destroy(this);
	}
}


