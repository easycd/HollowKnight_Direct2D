#include "kmFireBallSkill.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"
#include "kmPlayer.h"

namespace km
{
	FireBallSkill::FireBallSkill()
	{
	}
	FireBallSkill::~FireBallSkill()
	{
	}
	void FireBallSkill::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Knight_FireBall_Left = Resources::Load<Texture>(L"Knight_FireBall_Left", L"..\\Resources\\Knight\\FireBallObj\\Knight_FireBall_Left.png");
		std::shared_ptr<Texture> Knight_FireBall_Right = Resources::Load<Texture>(L"Knight_FireBall_Right", L"..\\Resources\\Knight\\FireBallObj\\Knight_FireBall_Right.png");
		std::shared_ptr<Texture> FireBall_Loop_Left = Resources::Load<Texture>(L"FireBall_Loop_Left", L"..\\Resources\\Knight\\FireBallObj\\FireBall_Loop_Left.png");
		std::shared_ptr<Texture> FireBall_Loop_Right = Resources::Load<Texture>(L"FireBall_Loop_Right", L"..\\Resources\\Knight\\FireBallObj\\FireBall_Loop_Right.png");
		
		mAnimation->Create(L"Knight_FireBall_Left", Knight_FireBall_Left, Vector2(0.0f, 0.0f), Vector2(504.0f, 157.0f), 6, Vector2(0.0f, 0.0f), 0.05f);
		mAnimation->Create(L"Knight_FireBall_Right", Knight_FireBall_Right, Vector2(0.0f, 0.0f), Vector2(504.0f, 157.0f), 6, Vector2(0.0f, 0.0f), 0.05f);
		mAnimation->Create(L"FireBall_Loop_Left", FireBall_Loop_Left, Vector2(0.0f, 0.0f), Vector2(504.0f, 157.0f), 4, Vector2(0.0f, 0.0f), 0.05f);
		mAnimation->Create(L"FireBall_Loop_Right", FireBall_Loop_Right, Vector2(0.0f, 0.0f), Vector2(504.0f, 157.0f), 4, Vector2(0.0f, 0.0f), 0.05f);

		mAnimation->CompleteEvent(L"Knight_FireBall_Left") = std::bind(&FireBallSkill::Left_Loop, this);
		mAnimation->CompleteEvent(L"Knight_FireBall_Right") = std::bind(&FireBallSkill::Right_Loop, this);

		mTransform->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		GameObject::Initialize();
	}
	void FireBallSkill::Update()
	{
		//mPlayer = SceneManager::GetPlayer();
		//mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		if (mDirection == eDirection::Left)
		{
			mPos.x -=  2.0f * Time::DeltaTime();
		}

		if (mDirection == eDirection::Right)
		{
			mPos.x += 2.0f * Time::DeltaTime();
		}

		mTransform->SetPosition(Vector3(mPos.x, mPos.y, 0.0f));
		GameObject::Update();
	}
	void FireBallSkill::Left_On()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mDirection = eDirection::Left;
		mPos = mPlayerPos;
		mAnimation->PlayAnimation(L"Knight_FireBall_Left", true);
	}

	void FireBallSkill::Right_On()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mDirection = eDirection::Right;
		mPos = mPlayerPos;
		mAnimation->PlayAnimation(L"Knight_FireBall_Right", true);
	}

	void FireBallSkill::Left_Loop()
	{
		mDirection = eDirection::Left;
		mAnimation->PlayAnimation(L"FireBall_Loop_Left", true);
	}

	void FireBallSkill::Right_Loop()
	{
		mDirection = eDirection::Right;
		mAnimation->PlayAnimation(L"FireBall_Loop_Right", true);
	}

	void FireBallSkill::Destroy()
	{
		object::Destroy(this);
	}
}