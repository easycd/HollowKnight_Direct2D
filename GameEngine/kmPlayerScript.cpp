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

namespace km
{
	PlayerScript::PlayerScript()
		: direction(1)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Initialize()
	{
		at = GetOwner()->GetComponent<Animator>();
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

	
		at->PlayAnimation(L"Idle_Right", true);

		at->CompleteEvent(L"Focus_StartRight") = std::bind(&PlayerScript::Focus, this);
		//at->EndEvent(L"Focus_StartLeft") = std::bind(&PlayerScript::Focus, this);
		//at->EndEvent(L"Focus_Left") = std::bind(&PlayerScript::FocusOn, this);
		//at->EndEvent(L"Focus_Right") = std::bind(&PlayerScript::FocusOn, this);
		//at->EndEvent(L"Focus_EndLeft") = std::bind(&PlayerScript::Idle, this);
		//at->EndEvent(L"Focus_EndRight") = std::bind(&PlayerScript::Idle, this);
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
		tr = GetOwner()->GetComponent<Transform>();
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
	}
	void PlayerScript::Complete()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* other)
	{
		//GroundScript* gd = other->GetOwner()->GetComponent<GroundScript>();
		//if (gd != nullptr)
		//{
		//	mRigidbody->SetGround(true);
		//}
		int a = 0;
	}

	void PlayerScript::OnCollisionStay(Collider2D* other)
	{
		GroundScript* gd = other->GetOwner()->GetComponent<GroundScript>();
		if (gd != nullptr)
		{
			int a = 0;
		}
	}

	void PlayerScript::OnCollisionExit(Collider2D* other)
	{
		GroundScript* gd = other->GetOwner()->GetComponent<GroundScript>();
		if (gd != nullptr)
		{
			mRigidbody->SetGround(false);
		}
	}

	void PlayerScript::Idle()
	{
		mState = PlayerState::Idle;
		if (Input::GetKey(eKeyCode::LEFT))
		{
			mState = PlayerState::Move;
			at->PlayAnimation(L"walk_Left", true);
			direction = 0;
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			mState = PlayerState::Move;
			at->PlayAnimation(L"walk_Right", true);
			direction = 1;
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			if (Input::GetKeyDown(eKeyCode::X))
			{
				mState = PlayerState::DownAttack;
				if (direction == 0)
				{
					at->PlayAnimation(L"Down_Attack_Left", true);
				}
				else
				{
					at->PlayAnimation(L"Down_Attack_Right", true);
				}
			}
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			if (Input::GetKeyDown(eKeyCode::X))
			{
				mState = PlayerState::UpAttack;
				if (direction == 0)
				{
					at->PlayAnimation(L"Up_Attack_Left", true);
				}
				else
				{
					at->PlayAnimation(L"Up_Attack_Right", true);
				}
			}
		}
		else if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = PlayerState::Attack;
			if (direction == 0)
			{
				at->PlayAnimation(L"Attack_Left", true);
			}
			else
			{
				at->PlayAnimation(L"Attack_Right", true);
			}
		}
		else if (Input::GetKeyDown(eKeyCode::Z))
		{
			//Ground가 False일때 더블점프 할수 있게 구현하면 됨
			mState = PlayerState::DoubleJump;
			if (direction == 0)
			{
				at->PlayAnimation(L"DoubleJump_Left", true);
				VectorR velocity = mRigidbody->GetVelocity();
				velocity.y += 15.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
			}
			else
			{
				at->PlayAnimation(L"DoubleJump_Right", true);
				VectorR velocity = mRigidbody->GetVelocity();
				velocity.y += 15.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
			}
		}
		else if (Input::GetKeyDown(eKeyCode::Z))
		{
			////Ground가 False일때 더블점프 할수 있게 구현하면 됨
			//mState = PlayerState::DoubleJump;
			//if (direction == 0)
			//{
			//	at->PlayAnimation(L"DoubleJump_Left", true);
			//}
			//else
			//{
			//	at->PlayAnimation(L"DoubleJump_Right", true);
			//}
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			//mState = PlayerState::FocusStart;
			if (direction == 0)
			{
				at->PlayAnimation(L"Focus_StartLeft", true);
			}
			else
			{
				at->PlayAnimation(L"Focus_StartRight", true);
			}
		}
	}

	void PlayerScript::Move()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			mState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Left", true);
			direction = 0;
		}
		else if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Right", true);
			direction = 1;
		}

		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			direction = 0;
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			direction = 1;
		}

		if (Input::GetKey(eKeyCode::LSHFIT))
		{
			mState = PlayerState::Dash;
			if (direction == 0)
			{
				at->PlayAnimation(L"Dash_Left", true);
				VectorR velocity = mRigidbody->GetVelocity();
				velocity.x -= 8.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
			}
			else
			{
				at->PlayAnimation(L"Dash_Right", true);
				VectorR velocity = mRigidbody->GetVelocity();
				velocity.x += 8.0f;
				mRigidbody->SetVelocity(velocity);
				mRigidbody->SetGround(false);
			}
		}
	}

	void PlayerScript::Jump()
	{
		//if (Input::GetKeyUp(eKeyCode::Z))
		//{
		//	mState = PlayerState::Idle;
		//	if (direction == 0)
		//	{
		//		at->PlayAnimation(L"Idle_Left", true);
		//	}
		//	else
		//	{
		//		at->PlayAnimation(L"Idle_Right", true);
		//	}
		//}
	}

	void PlayerScript::DoubleJump()
	{
		if (Input::GetKeyUp(eKeyCode::Z))
		{
			mState = PlayerState::Idle;
			if (direction == 0)
			{
				at->PlayAnimation(L"Idle_Left", true);
			}
			else
			{
				at->PlayAnimation(L"Idle_Right", true);
			}
		}
	}

	void PlayerScript::Dash()
	{
		if (Input::GetKeyUp(eKeyCode::LSHFIT))
		{
			if (direction == 0)
			{
				mState = PlayerState::Idle;
				at->PlayAnimation(L"Idle_Left", true);
			}
			else
			{
				mState = PlayerState::Idle;
				at->PlayAnimation(L"Idle_Right", true);
			}
		}
	}

	void PlayerScript::UpAttack()
	{
		if (Input::GetKeyUp(eKeyCode::X))
		{
			mState = PlayerState::Idle;
			if (direction == 0)
			{
				at->PlayAnimation(L"Idle_Left", true);
			}
			else
			{
				at->PlayAnimation(L"Idle_Right", true);
			}
		}
	}

	void PlayerScript::Attack()
	{
		if (Input::GetKeyUp(eKeyCode::X))
		{
			mState = PlayerState::Idle;
			if (direction == 0)
			{
				at->PlayAnimation(L"Idle_Left", true);
			}
			else
			{
				at->PlayAnimation(L"Idle_Right", true);
			}
		}
	}
	void PlayerScript::DownAttack()
	{
		if (Input::GetKeyUp(eKeyCode::X))
		{
			mState = PlayerState::Idle;
			if (direction == 0)
			{
				at->PlayAnimation(L"Idle_Left", true);
			}
			else
			{
				at->PlayAnimation(L"Idle_Right", true);
			}
		}
	}
	void PlayerScript::FocusStart()
	{
		//mState = PlayerState::FocusStart;
		
		if (direction == 0)
		{
			at->PlayAnimation(L"Focus_StartLeft", true);
		}
		else
		{
			at->PlayAnimation(L"Focus_StartRight", true);
		}
		
		//if (Input::GetKeyUp(eKeyCode::A))
		//	FocusEnd();
		//if (Input::GetKeyUp(eKeyCode::A))
		//{
		//	mState = PlayerState::Idle;
		//	if (direction == 0)
		//	{
		//		at->PlayAnimation(L"Idle_Left", true);
		//	}
		//	else
		//	{
		//		at->PlayAnimation(L"Idle_Right", true);
		//	}
		//}
	}
	void PlayerScript::Focus()
	{
		if (Input::GetKeyUp(eKeyCode::A))
		{
			int a = 0;
		}
		//if (Input::GetKey(eKeyCode::A))
		//{
		//	if (direction == 0)
		//	{
		//		at->PlayAnimation(L"Focus_Left", false);
		//	}
		//	else
		//	{
		//		at->PlayAnimation(L"Focus_Right", false);
		//	}
		//}
		//else if(Input::GetKeyUp(eKeyCode::A))
		//{
		//	FocusEnd();
		//}
	}
	void PlayerScript::FocusOn()
	{
		mState = PlayerState::FocusOn;
		if (Input::GetKey(eKeyCode::A))
		{
			if (direction == 0)
			{
				at->PlayAnimation(L"Focus_OnLeft", false);
			}
			else
			{
				at->PlayAnimation(L"Focus_OnRight", false);
			}
		}
		else if (Input::GetKeyUp(eKeyCode::A))
		{
			FocusEnd();
		}
	}
	void PlayerScript::FocusEnd()
	{
		mState = PlayerState::FocusEnd;
		if (direction == 0)
		{
			at->PlayAnimation(L"Focus_OnLeft", false);
			mState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Left", true);
		}
		else
		{
			at->PlayAnimation(L"Focus_OnRight", false);
			mState = PlayerState::Idle;
			at->PlayAnimation(L"Idle_Right", true);
		}
	}
	void PlayerScript::Death()
	{

	}
}