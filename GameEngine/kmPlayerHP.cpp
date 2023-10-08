#include "kmPlayerHP.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmObject.h"
#include "kmMeshRenderer.h"
#include "kmPlayer.h"
#include "kmCameraScript.h"

namespace km
{
	PlayerHP::PlayerHP()
		: mDistance(0.0f)
	{
	}
	PlayerHP::~PlayerHP()
	{
	
	}

	void PlayerHP::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Empty_State = Resources::Load<Texture>(L"Empty_State", L"..\\Resources\\UI\\HP\\Empty\\Empty.png");
		std::shared_ptr<Texture> Idle_State = Resources::Load<Texture>(L"Idle_State", L"..\\Resources\\UI\\HP\\Idle\\Health_Idle.png");
		std::shared_ptr<Texture> Break_State = Resources::Load<Texture>(L"Break_State", L"..\\Resources\\UI\\HP\\Break\\Health_Break.png");
		std::shared_ptr<Texture> Refill_State = Resources::Load<Texture>(L"Refill_State", L"..\\Resources\\UI\\HP\\Refill\\Health_Refill.png");

		mAnimation->Create(L"Empty_State", Empty_State, Vector2(0.0f, 0.0f), Vector2(126.0f, 167.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Idle_State", Idle_State, Vector2(0.0f, 0.0f), Vector2(126.0f, 167.0f), 45, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Break_State", Break_State, Vector2(0.0f, 0.0f), Vector2(126.0f, 167.0f), 6, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Refill_State", Refill_State, Vector2(0.0f, 0.0f), Vector2(126.0f, 167.0f), 6, Vector2(0.0f, 0.0f), 0.1f);

		mAnimation->CompleteEvent(L"Break_State") = std::bind(&PlayerHP::Empty, this);
		mAnimation->CompleteEvent(L"Refill_State") = std::bind(&PlayerHP::Idle, this);

		mTransform->SetScale(Vector3(0.07f, 0.1f, 0.0f));
		GameObject::Initialize();
	}

	void PlayerHP::Update()
	{
		mCamraScript = SceneManager::GetCamera();
		mCameraPos = mCamraScript->GetOwner()->GetComponent<Transform>()->GetPosition();

		mTransform->SetPosition(Vector3(mCameraPos.x - 0.52f + mDistance, mCameraPos.y + 0.33f, 0.0f));
		GameObject::Update();

		GameObject::Update();
	}

	void PlayerHP::Empty()
	{
		mAnimation->PlayAnimation(L"Empty_State", true);
	}
	
	void PlayerHP::Idle()
	{
		mAnimation->PlayAnimation(L"Idle_State", true);
	}
	
	void PlayerHP::Break()
	{
		mAnimation->PlayAnimation(L"Break_State", true);
	}
	
	void PlayerHP::Refill()
	{
		mAnimation->PlayAnimation(L"Refill_State", true);
	}
}