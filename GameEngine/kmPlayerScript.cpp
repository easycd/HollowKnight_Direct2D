#include "kmPlayerScript.h"
#include "kmCameraScript.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmInput.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmRigidbody.h"
#include "kmGroundScript.h"
#include "kmObject.h"

#include "kmPlayerEffet.h"

#include "kmMeshRenderer.h"

namespace km
{
	PlayerScript::PlayerScript()
		: mTime(0.0f)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		at = GetOwner()->GetComponent<Animator>();
		tr = GetOwner()->GetComponent<Transform>();
		//at->CompleteEvent(L"Idle") = std::bind(&PlayerScript::Complete, this);

		std::shared_ptr<Texture> LeftIdle = Resources::Load<Texture>(L"LeftIdle", L"..\\Resources\\Knight\\Knight_Idle_Left.png");
		std::shared_ptr<Texture> RightIdle = Resources::Load<Texture>(L"RightIdle", L"..\\Resources\\Knight\\Knight_Idle_Right.png");

		std::shared_ptr<Texture> Leftwalk = Resources::Load<Texture>(L"Leftwalk", L"..\\Resources\\Knight\\Knight_walk_Left.png");
		std::shared_ptr<Texture> Rightwalk = Resources::Load<Texture>(L"Rightwalk", L"..\\Resources\\Knight\\Knight_walk_Right.png");

		std::shared_ptr<Texture> DoubleJump_Left = Resources::Load<Texture>(L"DoubleJumpLeft", L"..\\Resources\\Knight\\Knight_DoubleJump_Left.png");
		std::shared_ptr<Texture> DoubleJump_Right = Resources::Load<Texture>(L"DoubleJumpRight", L"..\\Resources\\Knight\\Knight_DoubleJump_Right.png");

		std::shared_ptr<Texture> UP_LeftAttack = Resources::Load<Texture>(L"LeftUpAttack", L"..\\Resources\\Knight\\Knight_Up_Attack_Left.png");
		std::shared_ptr<Texture> UP_RightAttack = Resources::Load<Texture>(L"RightUpAttack", L"..\\Resources\\Knight\\Knight_Up_Attack_Right.png");
		std::shared_ptr<Texture> LeftAttack = Resources::Load<Texture>(L"LeftAttack", L"..\\Resources\\Knight\\Knight_Attack_Left.png");
		std::shared_ptr<Texture> RightAttack = Resources::Load<Texture>(L"RightAttack", L"..\\Resources\\Knight\\Knight_Attack_Right.png");
		std::shared_ptr<Texture> Down_LeftAttack = Resources::Load<Texture>(L"LeftDownAttack", L"..\\Resources\\Knight\\Knight_Down_Attack_Left.png");
		std::shared_ptr<Texture> Down_RightAttack = Resources::Load<Texture>(L"RightDownAttack", L"..\\Resources\\Knight\\Knight_Down_Attack_Right.png");

		std::shared_ptr<Texture> LeftDash = Resources::Load<Texture>(L"LeftDash", L"..\\Resources\\Knight\\Knight_Dash_Left.png");
		std::shared_ptr<Texture> RightDash = Resources::Load<Texture>(L"RightDash", L"..\\Resources\\Knight\\Knight_Dash_Right.png");

		std::shared_ptr<Texture> FocusStartLeft = Resources::Load<Texture>(L"FocusStartLeft", L"..\\Resources\\Knight\\Knight_FocusStart_Left.png");
		std::shared_ptr<Texture> FocusStartRight = Resources::Load<Texture>(L"FocusStartRight", L"..\\Resources\\Knight\\Knight_FocusStart_Right.png");
		std::shared_ptr<Texture> FocusLeft = Resources::Load<Texture>(L"FocusLeft", L"..\\Resources\\Knight\\Knight_Focus_Left.png");
		std::shared_ptr<Texture> FocusRight = Resources::Load<Texture>(L"FocusRight", L"..\\Resources\\Knight\\Knight_Focus_Right.png");
		std::shared_ptr<Texture> FocusOnLeft = Resources::Load<Texture>(L"FocusOnLeft", L"..\\Resources\\Knight\\Knight_FocusOn_Left.png");
		std::shared_ptr<Texture> FocusOnRight = Resources::Load<Texture>(L"FocusOnRight", L"..\\Resources\\Knight\\Knight_FocusOn_Right.png");
		std::shared_ptr<Texture> FocusEndLeft = Resources::Load<Texture>(L"FocusEndLeft", L"..\\Resources\\Knight\\Knight_FocusEnd_Left.png");
		std::shared_ptr<Texture> FocusEndRight = Resources::Load<Texture>(L"FocusEndRight", L"..\\Resources\\Knight\\Knight_FocusEnd_Right.png");

		at->Create(L"Idle_Left", LeftIdle, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 9);
		at->Create(L"Idle_Right", RightIdle, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 9);

		at->Create(L"walk_Left", Leftwalk, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8);
		at->Create(L"walk_Right", Rightwalk, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8);

		at->Create(L"DoubleJump_Left", DoubleJump_Left, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8);
		at->Create(L"DoubleJump_Right", DoubleJump_Right, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8);

		at->Create(L"Up_Attack_Left", UP_LeftAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);
		at->Create(L"Up_Attack_Right", UP_RightAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);
		at->Create(L"Attack_Left", LeftAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);
		at->Create(L"Attack_Right", RightAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);
		at->Create(L"Down_Attack_Left", Down_LeftAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);
		at->Create(L"Down_Attack_Right", Down_RightAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);

		at->Create(L"Dash_Left", LeftDash, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 12);
		at->Create(L"Dash_Right", RightDash, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 12);

		at->Create(L"Focus_StartLeft", FocusStartLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 7);
		at->Create(L"Focus_StartRight", FocusStartRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 7);
		at->Create(L"Focus_Left", FocusLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 10);
		at->Create(L"Focus_Right", FocusRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 10);
		at->Create(L"Focus_OnLeft", FocusOnLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 11);
		at->Create(L"Focus_OnRight", FocusOnRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 11);
		at->Create(L"Focus_EndLeft", FocusEndLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 3);
		at->Create(L"Focus_EndRight", FocusEndRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 3);

	
		//at->PlayAnimation(L"Idle_Right", true);
		Direction = eDirection::Right;

		Collider2D* collider = GetOwner()->AddComponent<Collider2D>();
		mRigidbody = GetOwner()->AddComponent<Rigidbody>();
		mRigidbody->SetMass(0.1f);
		VectorR velocity = mRigidbody->GetVelocity();
		velocity.y -= 0.2f;

		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);
	}
	void PlayerScript::Update()
	{
		pos = tr->GetPosition();

		switch (mState)
		{
		case PlayerScript::PlayerState::Idle:
			Idle();
			break;
		case PlayerScript::PlayerState::Move:
			Move();
			break;
		case PlayerScript::PlayerState::Jump:
			Jump();
			break;
		case PlayerScript::PlayerState::DoubleJump:
			DoubleJump();
			break;
		case PlayerScript::PlayerState::Fall:
			Fall();
			break;
		case PlayerScript::PlayerState::Dash:
			Dash();
			break;
		case PlayerScript::PlayerState::UpAttack:
			UpAttack();
			break;
		case PlayerScript::PlayerState::Attack:
			Attack();
			break;
		case PlayerScript::PlayerState::DownAttack:
			DownAttack();
			break;
		case PlayerScript::PlayerState::FocusStart:
			FocusStart();
			break;
		case PlayerScript::PlayerState::Focus:
			Focus();
			break;
		case PlayerScript::PlayerState::FocusOn:
			FocusOn();
			break;
		case PlayerScript::PlayerState::FocusEnd:
			FocusEnd();
			break;
		case PlayerScript::PlayerState::Death:
			Death();
			break;
		default:
			break;
		}

		//if (mRigidbody->GetGround() == false)
		//{
		//	if ((mState != PlayerState::Dash) && (mState != PlayerState::Jump)
		//		&& (mState != PlayerState::DoubleJump) && (mState != PlayerState::Attack) 
		//		&& (mState != PlayerState::UpAttack) && (mState != PlayerState::DownAttack)
		//		&& (mState != PlayerState::Death))
		//	{
		//		mState = PlayerState::Fall;
		//		idle_Check = false;
		//	}
		//}
	}
	void PlayerScript::Complete()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{
		//GroundScript* gd = other->GetOwner()->GetComponent<GroundScript>();
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());

		if (gd != nullptr)
		{
			mRigidbody->SetGround(true);
		}
		int a = 0;
	}

	void PlayerScript::OnCollisionStay(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		if (gd != nullptr)
		{
			int a = 0;
		}
	}

	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		if (gd != nullptr)
		{
			mRigidbody->SetGround(false);
		}
	}

	void PlayerScript::Idle()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (idle_Check == false)
		{
			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Idle_Left", true);
			if (Direction == eDirection::Right)
				at->PlayAnimation(L"Idle_Right", true);

			idle_Check = true;
			ActionInitialize();
		}

		//좌우 이동
		if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mState = PlayerState::Move;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"walk_Left", true);

			if (Direction == eDirection::Right)
				at->PlayAnimation(L"walk_Right", true);

			idle_Check = false;
		}

		//일반 공격
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = PlayerState::Attack;
			idle_Check = false;
		}

		//하단 공격
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
				mState = PlayerState::DownAttack;
				idle_Check = false;
		}

		//상단공격
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
				mState = PlayerState::UpAttack;
				idle_Check = false;
		}

		// 점프
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = PlayerState::Jump;
			idle_Check = false;
		}

		// 대시키 입력시 dash 상태로 변경
		if (Input::GetKeyDown(eKeyCode::LSHFIT))
		{
			mState = PlayerState::Dash;
			idle_Check = false;
			return;
		}

		//체력회복
		if (Input::GetKey(eKeyCode::A))
		{
			FocusStart();

			idle_Check = false;
		}
	}

	void PlayerScript::Move()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (Input::GetKeyUp(eKeyCode::LEFT) || Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Idle_Left", true);

			if (Direction == eDirection::Right)
				at->PlayAnimation(L"Idle_Right", true);
		}

		//일반 공격
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = PlayerState::Attack;
		}

		//하단 공격
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = PlayerState::DownAttack;
		}

		//상단공격
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = PlayerState::UpAttack;
		}

		// 점프
		if (Input::GetKeyDown(eKeyCode::Z))
		{
			mState = PlayerState::Jump;
		}

		// 대시키 입력시 dash 상태로 변경
		if (Input::GetKeyDown(eKeyCode::LSHFIT))
		{
			mState = PlayerState::Dash;
		}

		//체력회복
		if (Input::GetKey(eKeyCode::A))
		{
			FocusStart();
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 3.0f * Time::DeltaTime();
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 3.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void PlayerScript::Jump()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (jump_Check == false)
		{
			switch (Direction)
			{
			case eDirection::Left:
				at->PlayAnimation(L"Idle_Left", false);
				jump_Check = true;
				break;
			case eDirection::Right:
				at->PlayAnimation(L"Idle_Right", false);
				jump_Check = true;
				break;
			defualt:
				break;
			}

			VectorR velocity = mRigidbody->GetVelocity();
			velocity.y += 8.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
		}

		// 더블점프
		if (Input::GetKeyDown(eKeyCode::Z) && double_jump_Check == false)
		{
			mState = PlayerState::DoubleJump;
			double_jump_Check = false;
			return;
		}

		// Dash
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = PlayerState::Dash;
			double_jump_Check = false;
			return;
		}

		// Attack
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = PlayerState::Attack;
			double_jump_Check = false;
			return;
		}

		// Up Attack
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = PlayerState::UpAttack;
			double_jump_Check = false;
			return;
		}

		// Down Attack
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = PlayerState::DownAttack;
			double_jump_Check = false;
			return;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.1f)
		{
			mTime = 0.0f;
			Jump_End_Event();
		}

		VectorR velocity = mRigidbody->GetVelocity();
		if (Input::GetKey(eKeyCode::LEFT))
			velocity.x -= 0.001f;

		if (Input::GetKey(eKeyCode::RIGHT))
			velocity.x += 0.001f;

		mRigidbody->SetVelocity(velocity);
	}

	void PlayerScript::DoubleJump()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (double_jump_Check == false)
		{
			switch (Direction)
			{
			case eDirection::Left:	// left
				at->PlayAnimation (L"Idle_Left", false);
				double_jump_Check = true;
				break;

			case eDirection::Right:	// right
				at->PlayAnimation(L"Idle_Right", false);
				double_jump_Check = true;
				break;

			default:
				break;
			}

			VectorR velocity = mRigidbody->GetVelocity();
			velocity.y += 8.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
		}

		// 더블점프
		if (Input::GetKeyDown(eKeyCode::Z) && double_jump_Check == false)
		{
			mState = PlayerState::DoubleJump;
			double_jump_Check = false;
			return;
		}

		// Dash
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = PlayerState::Dash;
			double_jump_Check = false;
			return;
		}

		// Attack
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = PlayerState::Attack;
			double_jump_Check = false;
			return;
		}

		// Up Attack
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = PlayerState::UpAttack;
			double_jump_Check = false;
			return;
		}

		// Down Attack
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = PlayerState::DownAttack;
			double_jump_Check = false;
			return;
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::LEFT))
		{
			mState = PlayerState::Idle;
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.2f)
		{
			mTime = 0.0f;
			Double_Jump_End_Event();
		}
	}

	void PlayerScript::Dash()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (dash_jump_Check == false)
		{
			switch (Direction)
			{
			case eDirection::Left:	// left
				at->PlayAnimation(L"Dash_Left", false);
				dash_jump_Check = true;
				break;

			case eDirection::Right:	// right
				at->PlayAnimation(L"Dash_Right", false);
				dash_jump_Check = true;
				break;

			default:
				break;
			}
		}

		velocity = mRigidbody->GetVelocity();
		if (Direction == eDirection::Left)
		{
			velocity.x -= 8.0f;
		}
		if (Direction == eDirection::Right)
		{
			velocity.x += 8.0f;
		}
		mRigidbody->SetVelocity(velocity);
	}

	void PlayerScript::UpAttack()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (up_attack_Check == false)
		{
			switch (Direction)
			{
			case eDirection::Left:	// left
				at->PlayAnimation(L"Up_Attack_Left", false);
				up_attack_Check = true;
				break;

			case eDirection::Right:	// right
				at->PlayAnimation(L"Up_Attack_Right", false);
				up_attack_Check = true;
				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.2f)
		{
			mTime = 0.0f;
			Up_Attack_End_Evnet();
		}
	}

	void PlayerScript::Attack()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (attack_Check == false)
		{
			if (Direction == eDirection::Left)
			{
				at->PlayAnimation(L"Attack_Left", true);
				attack_Check = true;
			}
			else if (Direction == eDirection::Right)
			{
				//Effect = object::Instantiate<PlayerEffet>(eLayerType::Effect);
				//Effect->Normal_Attack_Effect();
				
				at->PlayAnimation(L"Attack_Right", true);
				attack_Check = true;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.2f)
		{
			mTime = 0.0f;
			Attack_End_Event();
		}
	}

	void PlayerScript::Fall()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (fall_Check == false)
		{
			switch (Direction)
			{
			case eDirection::Left:	// left
				at->PlayAnimation(L"Idle_Left", false);
				fall_Check = true;
				break;

			case eDirection::Right:	// right
				at->PlayAnimation(L"Idle_Right", false);
				fall_Check = true;
				break;

			default:
				break;
			}

			ActionInitialize();
		}

		// 더블점프
		if (Input::GetKeyDown(eKeyCode::Z) && double_jump_Check == false)
		{
			mState = PlayerState::DoubleJump;
			fall_Check = false;
			return;
		}

		// Dash
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mState = PlayerState::Dash;
			fall_Check = false;
			return;
		}

		// Up Attack
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::UP))
		{
			mState = PlayerState::UpAttack;
			fall_Check = false;
			return;
		}

		// Down Attack
		if (Input::GetKeyDown(eKeyCode::X) && Input::GetKey(eKeyCode::DOWN))
		{
			mState = PlayerState::DownAttack;
			fall_Check = false;
			return;
		}

		// Attack
		if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = PlayerState::Attack;
			fall_Check = false;
		}

		if (Input::GetKey(eKeyCode::LEFT) || Input::GetKey(eKeyCode::RIGHT))
		{
			mState = PlayerState::Idle;
		}
	}

	void PlayerScript::DownAttack()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (down_attack_Check == false)
		{
			switch (Direction)
			{
			case eDirection::Left:	// left
				at->PlayAnimation(L"Down_Attack_Left", true);
				down_attack_Check = true;
				break;

			case eDirection::Right:	// right
				at->PlayAnimation(L"Down_Attack_Right", true);
				down_attack_Check = true;
				break;

			default:
				break;
			}
		}

		mTime += Time::DeltaTime();
		if (mTime >= 0.2f)
		{
			mTime = 0.0f;
			Down_Attack_End_Event();
		}
	}
	void PlayerScript::FocusStart()
	{		
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		mState = PlayerState::FocusStart;
		if (Input::GetKey(eKeyCode::A))
		{
				at->PlayAnimation(L"Focus_StartLeft", true);
		}
	}
	void PlayerScript::Focus()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

		if (Input::GetKeyUp(eKeyCode::A))
		{
			int a = 0;
		}

	}
	void PlayerScript::FocusOn()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

	}
	void PlayerScript::FocusEnd()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;


	}
	void PlayerScript::Death()
	{
		if (Input::GetKey(eKeyCode::LEFT))
			Direction = eDirection::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			Direction = eDirection::Right;

	}
	void PlayerScript::ActionInitialize()
	{
		idle_Check = false;
		jump_Check = false;
		double_jump_Check = false;
		dash_jump_Check = false;
		up_attack_Check   = false;
		attack_Check      = false;
		down_attack_Check = false;
	}

	void PlayerScript::Up_Attack_End_Evnet()
	{
		switch (mRigidbody->GetGround())
		{
		case true:
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Idle_Left", true);
			else if (Direction == eDirection::Right)
				at->PlayAnimation(L"Idle_Right", true);
			break;

		case false:
			mState = PlayerState::Fall;
			break;

		default:
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Knight_Idleleft", true);
			else if (Direction == eDirection::Right)
				at->PlayAnimation(L"Knight_Idleright", true);
			break;
		}
	}
	void PlayerScript::Attack_End_Event()
	{
		//switch (mRigidbody->GetGround())
		switch (mRigidbody->GetGround())
		{
		case true:
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Idle_Left", true);
			else if (Direction == eDirection::Right)
				at->PlayAnimation(L"Idle_Right", true);
			break;

		case false:
			mState = PlayerState::Fall;
			break;

		default:
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Knight_Idleleft", true);
			else if (Direction == eDirection::Right)
				at->PlayAnimation(L"Knight_Idleright", true);
			break;
		}
	}

	void PlayerScript::Down_Attack_End_Event()
	{
		switch (mRigidbody->GetGround())
		{
		case true:
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Idle_Left", true);
			else if (Direction == eDirection::Right)
				at->PlayAnimation(L"Idle_Right", true);
			break;

		case false:
			mState = PlayerState::Fall;
			break;

		default:
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Knight_Idleleft", true);
			else if (Direction == eDirection::Right)
				at->PlayAnimation(L"Knight_Idleright", true);
			break;
		}
	}

	void PlayerScript::Jump_End_Event()
	{
		switch (mRigidbody->GetGround())
		{
		case true:
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Idle_Left", true);
			else if (Direction == eDirection::Right)
				at->PlayAnimation(L"Idle_Right", true);
			break;

		case false:
			mState = PlayerState::Fall;
			break;

		default:
			mState = PlayerState::Idle;

			if (Direction == eDirection::Left)
				at->PlayAnimation(L"Knight_Idleleft", true);
			else if (Direction == eDirection::Right)
				at->PlayAnimation(L"Knight_Idleright", true);
			break;
		}
	}

	void PlayerScript::Double_Jump_End_Event()
	{
		mState = PlayerState::Fall;

		if (Direction == eDirection::Left)
			at->PlayAnimation(L"Idle_Left", true);
		else if (Direction == eDirection::Right)
			at->PlayAnimation(L"Idle_Right", true);
	}
}