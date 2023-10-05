#include "DoubleJump_Effect.h"
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
	DoubleJump_Effect::DoubleJump_Effect()
	{
	}
	DoubleJump_Effect::~DoubleJump_Effect()
	{
	}
	void DoubleJump_Effect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Double_Jump_Left = Resources::Load<Texture>(L"Double_Jump_Left", L"..\\Resources\\Knight\\Effect\\Double_Jump_Effect\\Left\\Double_Jump_Left.png");
		std::shared_ptr<Texture> Double_Jump_Right = Resources::Load<Texture>(L"Double_Jump_Right", L"..\\Resources\\Knight\\Effect\\Double_Jump_Effect\\Right\\Double_Jump_Right.png");

		mAnimation->Create(L"Double_Jump_Left", Double_Jump_Left, Vector2(0.0f, 0.0f), Vector2(383.0f, 356.0f), 6, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Double_Jump_Right", Double_Jump_Right, Vector2(0.0f, 0.0f), Vector2(383.0f, 356.0f), 6, Vector2(0.0f, 0.0f), 0.1f);

		mAnimation->CompleteEvent(L"Double_Jump_Left") = std::bind(&DoubleJump_Effect::Destroy, this);
		mAnimation->CompleteEvent(L"Double_Jump_Right") = std::bind(&DoubleJump_Effect::Destroy, this);

		mTransform->SetScale(Vector3(0.3f, 0.3f, 0.0f));
		GameObject::Initialize();
	}
	void DoubleJump_Effect::Update()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mTransform->SetPosition(Vector3(mPlayerPos.x, mPlayerPos.y, 1.0f));

		GameObject::Update();
	}
	void DoubleJump_Effect::DoubleJump_Left()
	{
		mAnimation->PlayAnimation(L"Double_Jump_Left", true);
	}
	void DoubleJump_Effect::DoubleJump_Right()
	{
		mAnimation->PlayAnimation(L"Double_Jump_Right", true);
	}
	void DoubleJump_Effect::Destroy()
	{
		object::Destroy(this);
	}
}