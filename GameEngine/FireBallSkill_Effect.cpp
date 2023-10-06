#include "FireBallSkill_Effect.h"
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
	FireBallSkill_Effect::FireBallSkill_Effect()
	{
	}
	FireBallSkill_Effect::~FireBallSkill_Effect()
	{
	}

	void FireBallSkill_Effect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> FireBallEffect_Left = Resources::Load<Texture>(L"FireBallEffect_Left", L"..\\Resources\\Knight\\Effect\\FireBall_Effect\\Left\\FireBallEffect_Left.png");
		std::shared_ptr<Texture> FireBallEffect_Right = Resources::Load<Texture>(L"FireBallEffect_Right", L"..\\Resources\\Knight\\Effect\\FireBall_Effect\\Right\\FireBallEffect_Right.png");

		mAnimation->Create(L"FireBallEffect_Left", FireBallEffect_Left, Vector2(0.0f, 0.0f), Vector2(306.0f, 306.0f), 8, Vector2(0.0f, 0.0f), 0.05f);
		mAnimation->Create(L"FireBallEffect_Right", FireBallEffect_Right, Vector2(0.0f, 0.0f), Vector2(306.0f, 306.0f), 8, Vector2(0.0f, 0.0f), 0.05f);

		mAnimation->CompleteEvent(L"FireBallEffect_Left") = std::bind(&FireBallSkill_Effect::Destroy, this);
		mAnimation->CompleteEvent(L"FireBallEffect_Right") = std::bind(&FireBallSkill_Effect::Destroy, this);

		mTransform->SetScale(Vector3(0.4f, 0.5f, 0.0f));
		GameObject::Initialize();
	}
	void FireBallSkill_Effect::Update()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		if(Left_Check)
			mTransform->SetPosition(Vector3(mPlayerPos.x - 0.1f, mPlayerPos.y, 0.0f));

		if (Right_Check)
			mTransform->SetPosition(Vector3(mPlayerPos.x + 0.1f, mPlayerPos.y, 0.0f));

		GameObject::Update();
	}
	void FireBallSkill_Effect::FireBallSkill_Left()
	{
		Left_Check = true;
		mAnimation->PlayAnimation(L"FireBallEffect_Left", true);
	}
	void FireBallSkill_Effect::FireBallSkill_Right()
	{
		Right_Check = true;
		mAnimation->PlayAnimation(L"FireBallEffect_Right", true);
	}
	void FireBallSkill_Effect::Destroy()
	{
		object::Destroy(this);
	}
}