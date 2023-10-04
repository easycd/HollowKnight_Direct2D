#include "kmPlayerEffet.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmMeshRenderer.h"
#include "kmObject.h"
#include "kmPlayer.h"

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

		std::shared_ptr<Texture> Basic_Slash_Left = Resources::Load<Texture>(L"Basic_Slash_Left", L"..\\Resources\\Knight\\Effect\\Slash\\Left\\Slash_Left.png");
		std::shared_ptr<Texture> Basic_Slash_Right = Resources::Load<Texture>(L"Basic_Slash_Right", L"..\\Resources\\Knight\\Effect\\Slash\\Right\\Slash_Right.png");

		std::shared_ptr<Texture> UP_Slash_Left = Resources::Load<Texture>(L"UP_Slash_Left", L"..\\Resources\\Knight\\Effect\\Up_Slash\\Left\\UP_Slash_Left.png");
		std::shared_ptr<Texture> UP_Slash_Right = Resources::Load<Texture>(L"UP_Slash_Right", L"..\\Resources\\Knight\\Effect\\Up_Slash\\Right\\UP_Slash_Right.png");

		std::shared_ptr<Texture> Down_Slash_Left = Resources::Load<Texture>(L"Down_Slash_Left", L"..\\Resources\\Knight\\Effect\\Down_Slash\\Left\\Down_Slash_Left.png");
		std::shared_ptr<Texture> Down_Slash_Right = Resources::Load<Texture>(L"Down_Slash_Right", L"..\\Resources\\Knight\\Effect\\Down_Slash\\Right\\Down_Slash_Right.png");


		at->Create(L"Basic_Slash_Left", Basic_Slash_Left, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, 0.0f), 0.05f);
		at->Create(L"Basic_Slash_Right", Basic_Slash_Right, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, 0.0f), 0.05f);

		at->Create(L"UP_Slash_Left", UP_Slash_Left, Vector2(0.0f, 0.0f), Vector2(169.0f, 192.0f), 6, Vector2(0.0f, 0.0f), 0.05f);
		at->Create(L"UP_Slash_Right", UP_Slash_Right, Vector2(0.0f, 0.0f), Vector2(169.0f, 192.0f), 6, Vector2(0.0f, 0.0f), 0.05f);

		at->Create(L"Down_Slash_Left", Down_Slash_Left, Vector2(0.0f, 0.0f), Vector2(182.0f, 209.0f), 6, Vector2(0.0f, 0.0f), 0.05f);
		at->Create(L"Down_Slash_Right", Down_Slash_Right, Vector2(0.0f, 0.0f), Vector2(182.0f, 209.0f), 6, Vector2(0.0f, 0.0f), 0.05f);

		at->CompleteEvent(L"Basic_Slash_Left") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"Basic_Slash_Right") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"UP_Slash_Left") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"UP_Slash_Right") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"Down_Slash_Left") = std::bind(&PlayerEffet::Destroy, this);
		at->CompleteEvent(L"Down_Slash_Right") = std::bind(&PlayerEffet::Destroy, this);


		GameObject::Initialize();
	}

	void PlayerEffet::Update()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		if (Slash_Left_Check)
		{
			mTransform->SetScale(Vector3(0.4f, 0.3f, 0.0f));
			mTransform->SetPosition(Vector3(mPlayerPos.x - 0.05f, mPlayerPos.y, 0.0f));
		}
		
		if (Slash_Right_Check)
		{
			mTransform->SetScale(Vector3(0.4f, 0.3f, 0.0f));
			mTransform->SetPosition(Vector3(mPlayerPos.x + 0.15f, mPlayerPos.y, 0.0f));
		}
		
		if (UP_Slash_Left_Check)
		{
			mTransform->SetScale(Vector3(0.2f, 0.3f, 0.0f));
			mTransform->SetPosition(Vector3(mPlayerPos.x, mPlayerPos.y, 0.0f));
		}
		
		if (UP_Slash_Right_Check)
		{
			mTransform->SetScale(Vector3(0.2f, 0.3f, 0.0f));
			mTransform->SetPosition(Vector3(mPlayerPos.x, mPlayerPos.y, 0.0f));
		}
		
		if (Down_Slash_Left_Check)
		{
			mTransform->SetScale(Vector3(0.2f, 0.3f, 0.0f));
			mTransform->SetPosition(Vector3(mPlayerPos.x, mPlayerPos.y, 0.0f));
		}
		
		if (Down_Slash_Right_Check)
		{
			mTransform->SetScale(Vector3(0.2f, 0.3f, 0.0f));
			mTransform->SetPosition(Vector3(mPlayerPos.x, mPlayerPos.y, 0.0f));
		}


		GameObject::Update();
	}

	void PlayerEffet::Slash_Left()
	{
		at->PlayAnimation(L"Basic_Slash_Left", true);
		Slash_Left_Check = true;
	}

	void PlayerEffet::Slash_Right()
	{
		at->PlayAnimation(L"Basic_Slash_Right", true);
		Slash_Right_Check = true;
	}

	void PlayerEffet::UP_Slash_Left()
	{
		at->PlayAnimation(L"UP_Slash_Left", true);
		UP_Slash_Left_Check = true;
	}

	void PlayerEffet::UP_Slash_Right()
	{
		at->PlayAnimation(L"UP_Slash_Left", true);
		UP_Slash_Right_Check = true;
	}

	void PlayerEffet::Down_Slash_Left()
	{
		at->PlayAnimation(L"Down_Slash_Left", true);
		Down_Slash_Left_Check = true;
	}

	void PlayerEffet::Down_Slash_Right()
	{
		at->PlayAnimation(L"Down_Slash_Left", true);
		Down_Slash_Right_Check = true;
	}

	void PlayerEffet::Destroy()
	{
		object::Destroy(this);
	}
}


