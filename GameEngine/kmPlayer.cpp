#include "kmPlayer.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmCameraScript.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmInput.h"
#include "kmRigidbody.h"
#include "kmGroundScript.h"
#include "kmObject.h"
#include "kmPlayerEffet.h"
#include "kmMeshRenderer.h"

namespace km
{
	Player::Player()
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		//Idle
		std::shared_ptr<Texture> LeftIdle = Resources::Load<Texture>(L"LeftIdle", L"..\\Resources\\Knight\\Idle\\Knight_Idle_Left.png");
		std::shared_ptr<Texture> RightIdle = Resources::Load<Texture>(L"RightIdle", L"..\\Resources\\Knight\\Idle\\Knight_Idle_Right.png");

		//Walk
		std::shared_ptr<Texture> Leftwalk = Resources::Load<Texture>(L"Leftwalk", L"..\\Resources\\Knight\\Walk\\Knight_walk_Left.png");
		std::shared_ptr<Texture> Rightwalk = Resources::Load<Texture>(L"Rightwalk", L"..\\Resources\\Knight\\Walk\\Knight_walk_Right.png");

		//Fall
		std::shared_ptr<Texture> Fall_Left = Resources::Load<Texture>(L"Fall_Left", L"..\\Resources\\Knight\\Fall\\Left\\Fall_Left.png");
		std::shared_ptr<Texture> Fall_Right = Resources::Load<Texture>(L"Fall_Right", L"..\\Resources\\Knight\\Fall\\Right\\Fall_Right.png");

		//Jump
		std::shared_ptr<Texture> Jump_Left = Resources::Load<Texture>(L"Jump_Left", L"..\\Resources\\Knight\\Jump\\Left\\Jump_Left.png");
		std::shared_ptr<Texture> Jump_Right = Resources::Load<Texture>(L"Jump_Right", L"..\\Resources\\Knight\\Jump\\Right\\Jump_Right.png");

		//Double Jump
		std::shared_ptr<Texture> DoubleJump_Left = Resources::Load<Texture>(L"DoubleJumpLeft", L"..\\Resources\\Knight\\Double_Jump\\Knight_DoubleJump_Left.png");
		std::shared_ptr<Texture> DoubleJump_Right = Resources::Load<Texture>(L"DoubleJumpRight", L"..\\Resources\\Knight\\Double_Jump\\Knight_DoubleJump_Right.png");

		//Slash
		std::shared_ptr<Texture> UP_LeftAttack = Resources::Load<Texture>(L"LeftUpAttack", L"..\\Resources\\Knight\\Up_Attack\\Knight_Up_Attack_Left.png");
		std::shared_ptr<Texture> UP_RightAttack = Resources::Load<Texture>(L"RightUpAttack", L"..\\Resources\\Knight\\Up_Attack\\Knight_Up_Attack_Right.png");
		std::shared_ptr<Texture> LeftAttack = Resources::Load<Texture>(L"LeftAttack", L"..\\Resources\\Knight\\Attack\\Knight_Attack_Left.png");
		std::shared_ptr<Texture> RightAttack = Resources::Load<Texture>(L"RightAttack", L"..\\Resources\\Knight\\Attack\\Knight_Attack_Right.png");
		std::shared_ptr<Texture> Down_LeftAttack = Resources::Load<Texture>(L"LeftDownAttack", L"..\\Resources\\Knight\\Down_Attack\\Knight_Down_Attack_Left.png");
		std::shared_ptr<Texture> Down_RightAttack = Resources::Load<Texture>(L"RightDownAttack", L"..\\Resources\\Knight\\Down_Attack\\Knight_Down_Attack_Right.png");

		//Dash
		std::shared_ptr<Texture> LeftDash = Resources::Load<Texture>(L"LeftDash", L"..\\Resources\\Knight\\Dash\\Knight_Dash_Left.png");
		std::shared_ptr<Texture> RightDash = Resources::Load<Texture>(L"RightDash", L"..\\Resources\\Knight\\Dash\\Knight_Dash_Right.png");

		//Focus
		std::shared_ptr<Texture> FocusStartLeft = Resources::Load<Texture>(L"FocusStartLeft", L"..\\Resources\\Knight\\Start\\Knight_FocusStart_Left.png");
		std::shared_ptr<Texture> FocusStartRight = Resources::Load<Texture>(L"FocusStartRight", L"..\\Resources\\Knight\\Start\\Knight_FocusStart_Right.png");
		std::shared_ptr<Texture> FocusLeft = Resources::Load<Texture>(L"FocusLeft", L"..\\Resources\\Knight\\Loop\\Knight_Focus_Left.png");
		std::shared_ptr<Texture> FocusRight = Resources::Load<Texture>(L"FocusRight", L"..\\Resources\\Knight\\Loop\\Knight_Focus_Right.png");
		std::shared_ptr<Texture> FocusOnLeft = Resources::Load<Texture>(L"FocusOnLeft", L"..\\Resources\\Knight\\On\\Knight_FocusOn_Left.png");
		std::shared_ptr<Texture> FocusOnRight = Resources::Load<Texture>(L"FocusOnRight", L"..\\Resources\\Knight\\On\\Knight_FocusOn_Right.png");
		std::shared_ptr<Texture> FocusEndLeft = Resources::Load<Texture>(L"FocusEndLeft", L"..\\Resources\\Knight\\End\\Knight_FocusEnd_Left.png");
		std::shared_ptr<Texture> FocusEndRight = Resources::Load<Texture>(L"FocusEndRight", L"..\\Resources\\Knight\\End\\Knight_FocusEnd_Right.png");

		mAnimation->Create(L"Idle_Left", LeftIdle, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 9, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Idle_Right", RightIdle, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 9, Vector2(0.0f, -0.12f));

		mAnimation->Create(L"walk_Left", Leftwalk, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"walk_Right", Rightwalk, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8, Vector2(0.0f, -0.12f));

		mAnimation->Create(L"Fall_Left", Fall_Left, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Fall_Right", Fall_Right, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, -0.12f));

		mAnimation->Create(L"Jump_Left", Jump_Left, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, -0.12f), 0.03f);
		mAnimation->Create(L"Jump_Right", Jump_Right, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, -0.12f), 0.03f);

		mAnimation->Create(L"DoubleJump_Left", DoubleJump_Left, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8, Vector2(0.0f, -0.12f), 0.05f);
		mAnimation->Create(L"DoubleJump_Right", DoubleJump_Right, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8, Vector2(0.0f, -0.12f), 0.05f);

		mAnimation->Create(L"Up_Attack_Left", UP_LeftAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15, Vector2(0.0f, -0.12f), 0.02f);
		mAnimation->Create(L"Up_Attack_Right", UP_RightAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15, Vector2(0.0f, -0.12f), 0.02f);
		mAnimation->Create(L"Attack_Left", LeftAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15, Vector2(0.0f, -0.12f), 0.02f);
		mAnimation->Create(L"Attack_Right", RightAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15, Vector2(0.0f, -0.12f), 0.02f);
		mAnimation->Create(L"Down_Attack_Left", Down_LeftAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15, Vector2(0.0f, -0.12f), 0.02f);
		mAnimation->Create(L"Down_Attack_Right", Down_RightAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15, Vector2(0.0f, -0.12f), 0.02f);

		mAnimation->Create(L"Dash_Left", LeftDash, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 12, Vector2(0.0f, -0.12f), 0.02f);
		mAnimation->Create(L"Dash_Right", RightDash, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 12, Vector2(0.0f, -0.12f), 0.02f);

		mAnimation->Create(L"Focus_StartLeft", FocusStartLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 7, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Focus_StartRight", FocusStartRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 7, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Focus_Left", FocusLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 10, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Focus_Right", FocusRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 10, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Focus_OnLeft", FocusOnLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 11, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Focus_OnRight", FocusOnRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 11, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Focus_EndLeft", FocusEndLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 3, Vector2(0.0f, -0.12f));
		mAnimation->Create(L"Focus_EndRight", FocusEndRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 3, Vector2(0.0f, -0.12f));

		mAnimation->CompleteEvent(L"Jump_Left") = std::bind(&Player::Jump_End, this);
		mAnimation->CompleteEvent(L"Jump_Right") = std::bind(&Player::Jump_End, this);

		mAnimation->CompleteEvent(L"DoubleJump_Left") = std::bind(&Player::DoubleJump_End, this);
		mAnimation->CompleteEvent(L"DoubleJump_Right") = std::bind(&Player::DoubleJump_End, this);

		mAnimation->CompleteEvent(L"Attack_Left") = std::bind(&Player::Attack_End, this);
		mAnimation->CompleteEvent(L"Attack_Right") = std::bind(&Player::Attack_End, this);
		mAnimation->CompleteEvent(L"Up_Attack_Left") = std::bind(&Player::Attack_End, this);
		mAnimation->CompleteEvent(L"Up_Attack_Right") = std::bind(&Player::Attack_End, this);
		mAnimation->CompleteEvent(L"Down_Attack_Left") = std::bind(&Player::Attack_End, this);
		mAnimation->CompleteEvent(L"Down_Attack_Right") = std::bind(&Player::Attack_End, this);

		mAnimation->CompleteEvent(L"Dash_Left") = std::bind(&Player::Dash_End, this);
		mAnimation->CompleteEvent(L"Dash_Right") = std::bind(&Player::Dash_End, this);
			
		mTransform->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		mTransform->SetPosition (Vector3(0.0f, 0.5f, 0.0f));
		mDirection = eDirection::Right;

		Collider2D* collider = AddComponent<Collider2D>();
		collider->SetSize(Vector2(0.18f, 0.7f));



		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(0.1f);
		VectorR velocity = mRigidbody->GetVelocity();
		velocity.y = - 0.5f;
		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);

		mAnimation->PlayAnimation(L"Idle_Right", true);
		GameObject::Initialize();
	}
	void Player::Update()
	{
		mPlayerPos = mTransform->GetPosition();

		switch (mState)
		{
		case Player::ePlayerState::Idle:
			Idle();
			break;
		case Player::ePlayerState::Move:
			Move();
			break;
		case Player::ePlayerState::Jump:
			Jump();
			break;
		case Player::ePlayerState::DoubleJump:
			DoubleJump();
			break;
		case Player::ePlayerState::Fall:
			Fall();
			break;
		case Player::ePlayerState::Dash:
			Dash();
			break;
		case Player::ePlayerState::UpAttack:
			UpAttack();
			break;
		case Player::ePlayerState::Attack:
			Attack();
			break;
		case Player::ePlayerState::DownAttack:
			DownAttack();
			break;
		//case Player::ePlayerState::FocusStart:
		//	FocusStart();
		//	break;
		//case Player::ePlayerState::Focus:
		//	Focus();
		//	break;
		//case Player::ePlayerState::FocusOn:
		//	FocusOn();
		//	break;
		//case Player::ePlayerState::FocusEnd:
		//	FocusEnd();
		//	break;
		//case Player::ePlayerState::Death:
		//	Death();
		//	break;
		default:
			break;
		}

		if (Ground_Check == false && Fall_Delay == false && Jump_Delay == false && DoubleJump_Delay == false)
			mState = ePlayerState::Fall;

		if (Ground_Check && Fall_Check)
			mState = ePlayerState::Idle;


		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
	void Player::Complete()
	{
	}

	void Player::OnCollisionEnter(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());

		if (gd != nullptr)
		{
			mRigidbody->SetGround(true);
			Ground_Check = true;
		}
	}

	void Player::OnCollisionStay(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		if (gd != nullptr)
		{
			mRigidbody->SetGround(true);
			Ground_Check = true;
		}
	}

	void Player::OnCollisionExit(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		if (gd != nullptr)
		{
			mRigidbody->SetGround(false);
			Ground_Check = false;
		}
	}


	void Player::Idle()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		//좌우 이동
		if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Move;

			if (mDirection == eDirection::Left)
				mAnimation->PlayAnimation(L"walk_Left", true);

			if (mDirection == eDirection::Right)
				mAnimation->PlayAnimation(L"walk_Right", true);
		}

		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpAttack;
			UpAttack_Check = true;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = ePlayerState::DownAttack;
			DownAttack_Check = true;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Attack;
			Attack_Check = true;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = ePlayerState::Jump;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::LSHFIT))
		{
			mState = ePlayerState::Dash;
			Dash_Check = true;
			return;
		}

		Fall_Check = false;
		Fall_Ani_Check = true;
		Fall_Dash_Check = true;
	}

	void Player::Move()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		//if (Input::GetKey(eKeyCode::LEFT))
		//{
		//	mPlayerPos.x -= 1.0f * Time::DeltaTime();
		//}
		//
		//if (Input::GetKey(eKeyCode::RIGHT))
		//{
		//	mPlayerPos.x += 1.0f * Time::DeltaTime();
		//}

		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Idle;
			if (mDirection == eDirection::Left)
				mAnimation->PlayAnimation(L"Idle_Left", true);
			else if (mDirection == eDirection::Right)
				mAnimation->PlayAnimation(L"Idle_Right", true);
		}

		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = ePlayerState::UpAttack;
			UpAttack_Check = true;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = ePlayerState::DownAttack;
			DownAttack_Check = true;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = ePlayerState::Attack;
			Attack_Check = true;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = ePlayerState::Jump;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::LSHFIT))
		{
			mState = ePlayerState::Dash;
			Dash_Check = true;
			return;
		}

		mTransform->SetPosition(mPlayerPos);

		VectorR velocity = mRigidbody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -0.8f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 0.8f;
		mRigidbody->SetVelocity(velocity);
	}

	void Player::Jump()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		mState = ePlayerState::Jump;

		if (Jump_Check)
		{
			if (mDirection == eDirection::Left)
			{
				mAnimation->PlayAnimation(L"Jump_Left", true);
			}

			if (mDirection == eDirection::Right)
			{
				mAnimation->PlayAnimation(L"Jump_Right", true);
			}
			Jump_Check = false;
			Jump_Delay = true;
		}

		VectorR velocity = mRigidbody->GetVelocity();
		velocity.y = 1.5f;
		
		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);
		
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -0.8f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 0.8f;
		
		mRigidbody->SetVelocity(velocity);
	}

	void Player::DoubleJump()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		mState = ePlayerState::DoubleJump;

		if (Double_Jump_Check)
		{
			if (mDirection == eDirection::Left)
			{
				mAnimation->PlayAnimation(L"DoubleJump_Left", true);
			}

			if (mDirection == eDirection::Right)
			{
				mAnimation->PlayAnimation(L"DoubleJump_Right", true);
			}
			Double_Jump_Check = false;
		}


		VectorR velocity = mRigidbody->GetVelocity();
		velocity.y = 0.7f;

		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);

		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -0.8f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 0.8f;

		mRigidbody->SetVelocity(velocity);
	}

	void Player::Dash()
	{
		if(Dash_Check)
		{
			mState = ePlayerState::Dash;

			if (mDirection == eDirection::Left)
			{
				mSavePos = mPlayerPos;
				mAnimation->PlayAnimation(L"Dash_Left", true);
				mRigidbody->SetGround(true);
				
			}

			if (mDirection == eDirection::Right)
			{
				mSavePos = mPlayerPos;
				mAnimation->PlayAnimation(L"Dash_Right", true);
				mRigidbody->SetGround(true);
			}

			Dash_Check = false;
		}

		VectorR velocity = mRigidbody->GetVelocity();
		if (mDirection == eDirection::Left)
		{
			if (mPlayerPos.x > mSavePos.x - 0.000001f)
			{
				velocity.x = -3.0f;
			}
		}
		if (mDirection == eDirection::Right)
		{
			if (mPlayerPos.x < mSavePos.x + 0.000001f)
			{
				velocity.x = 3.0f;
			}
		}
		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetMass(0.1f);
		Fall_Delay = false;
	}

	void Player::Fall()
	{
		if (Fall_Ani_Check)
		{
			if (mDirection == eDirection::Left)
				mAnimation->PlayAnimation(L"Fall_Left", true);
			if (mDirection == eDirection::Right)
				mAnimation->PlayAnimation(L"Fall_Right", true);

			Fall_Ani_Check = false;
		}

		//Ground 충돌 시 Idle
		if (Ground_Check)
		{
			if (mDirection == eDirection::Left)
				mAnimation->PlayAnimation(L"Idle_Left", true);
			else if (mDirection == eDirection::Right)
				mAnimation->PlayAnimation(L"Idle_Right", true);
		}

		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			Fall_Delay = true;
			UpAttack_Check = true;
			mState = ePlayerState::UpAttack;
		}

		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			Fall_Delay = true;
			DownAttack_Check = true;
			mState = ePlayerState::DownAttack;
		}

		if (Input::GetKey(eKeyCode::LEFT) && Input::GetKey(eKeyCode::X))
		{
			Fall_Delay = true;
			Attack_Check = true;
			mState = ePlayerState::Attack;
		}

		if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKey(eKeyCode::X))
		{
			Fall_Delay = true;
			Attack_Check = true;
			mState = ePlayerState::Attack;
		}

		if (Input::GetKey(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::LSHFIT))
		{
			Fall_Delay = true;
			Dash_Check = true;
			Fall_Dash_Check = false;
			mState = ePlayerState::Dash;
			return;
		}

		if (Input::GetKey(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::LSHFIT))
		{
			Fall_Delay = true;
			Dash_Check = true;
			Fall_Dash_Check = false;
			mState = ePlayerState::Dash;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::LSHFIT))
		{
			Fall_Delay = true;
			Dash_Check = true;
			Fall_Dash_Check = false;
			mState = ePlayerState::Dash;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			DoubleJump_Delay = true;
			mState = ePlayerState::DoubleJump;
			return;
		}

		Fall_Check = true;

		VectorR velocity = mRigidbody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT) && Fall_Dash_Check)
			velocity.x = -0.8f;
		if (Input::GetKey(eKeyCode::RIGHT) && Fall_Dash_Check)
			velocity.x = 0.8f;
		mRigidbody->SetVelocity(velocity);
	}

	void Player::UpAttack()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (UpAttack_Check)
		{
			mState = ePlayerState::UpAttack;

			if (mDirection == eDirection::Left)
			{
				mUpSlash_Effect = object::Instantiate<PlayerEffet>(eLayerType::Effect);
				mUpSlash_Effect->UP_Slash_Left();
				mAnimation->PlayAnimation(L"Up_Attack_Left", true);
			}

			if (mDirection == eDirection::Right)
			{
				mUpSlash_Effect = object::Instantiate<PlayerEffet>(eLayerType::Effect);
				mUpSlash_Effect->UP_Slash_Right();
				mAnimation->PlayAnimation(L"Up_Attack_Right", true);
			}

			UpAttack_Check = false;
		}

		VectorR velocity = mRigidbody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -0.8f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 0.8f;
		mRigidbody->SetVelocity(velocity);

		Fall_Delay = false;
	}

	void Player::Attack()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (Attack_Check)
		{
			mState = ePlayerState::Attack;

			if (mDirection == eDirection::Left)
			{
				mSlash_Effect = object::Instantiate<PlayerEffet>(eLayerType::Effect);
				mSlash_Effect->Slash_Left();
				mAnimation->PlayAnimation(L"Attack_Left", true);
				Attack_Check = false;
			}

			if (mDirection == eDirection::Right)
			{
				mSlash_Effect = object::Instantiate<PlayerEffet>(eLayerType::Effect);
				mSlash_Effect->Slash_Right();
				mAnimation->PlayAnimation(L"Attack_Right", true);
				Attack_Check = false;
			}
		}

		VectorR velocity = mRigidbody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -0.8f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 0.8f;
		mRigidbody->SetVelocity(velocity);

		Fall_Delay = false;
	}

	void Player::DownAttack()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			mDirection = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			mDirection = eDirection::Right;

		if (DownAttack_Check)
		{
			mState = ePlayerState::UpAttack;

			if (mDirection == eDirection::Left)
			{
				mDownSlash_Effect = object::Instantiate<PlayerEffet>(eLayerType::Effect);
				mDownSlash_Effect->Down_Slash_Left();
				mAnimation->PlayAnimation(L"Down_Attack_Left", true);
			}

			if (mDirection == eDirection::Right)
			{
				mDownSlash_Effect = object::Instantiate<PlayerEffet>(eLayerType::Effect);
				mDownSlash_Effect->Down_Slash_Right();
				mAnimation->PlayAnimation(L"Down_Attack_Right", true);
			}

			DownAttack_Check = false;
		}

		VectorR velocity = mRigidbody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x = -0.8f;
		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x = 0.8f;
		mRigidbody->SetVelocity(velocity);

		Fall_Delay = false;
	}

	void Player::Jump_End()
	{
		if (mDirection == eDirection::Left)
		{
			mState = ePlayerState::Idle;
			mAnimation->PlayAnimation(L"Idle_Left", true);
		}

		if (mDirection == eDirection::Right)
		{
			mState = ePlayerState::Idle;
			mAnimation->PlayAnimation(L"Idle_Right", true);
		}
		Jump_Check = true;
		Jump_Delay = false;
	}

	void Player::DoubleJump_End()
	{
		if (mDirection == eDirection::Left)
		{
			mState = ePlayerState::Idle;
			mAnimation->PlayAnimation(L"Idle_Left", true);
		}

		if (mDirection == eDirection::Right)
		{
			mState = ePlayerState::Idle;
			mAnimation->PlayAnimation(L"Idle_Right", true);
		}
		Double_Jump_Check = true;
		DoubleJump_Delay = false;
	}

	void Player::Dash_End()
	{
		mRigidbody->SetGround(false);

		if (mDirection == eDirection::Left)
		{
			mState = ePlayerState::Idle;
			mAnimation->PlayAnimation(L"Idle_Left", true);
		}
		if (mDirection == eDirection::Right)
		{
			mState = ePlayerState::Idle;
			mAnimation->PlayAnimation(L"Idle_Right", true);
		}
	}

	void Player::Attack_End()
	{
		if (mDirection == eDirection::Left)
		{
			mState = ePlayerState::Idle;
			mAnimation->PlayAnimation(L"Idle_Left", true);
		}
		if (mDirection == eDirection::Right)
		{
			mState = ePlayerState::Idle;
			mAnimation->PlayAnimation(L"Idle_Right", true);
		}
	}
}