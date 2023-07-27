#include "kmPlayerScript.h"
#include "kmCameraScript.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmInput.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmRigidbody.h"

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

		std::shared_ptr<Texture> LeftAttack = Resources::Load<Texture>(L"LeftAttack", L"..\\Resources\\Knight\\Knight_Attack_Left.png");
		std::shared_ptr<Texture> RightAttack = Resources::Load<Texture>(L"RightAttack", L"..\\Resources\\Knight\\Knight_Attack_Right.png");

		std::shared_ptr<Texture> LeftDash = Resources::Load<Texture>(L"LeftDash", L"..\\Resources\\Knight\\Knight_Dash_Left.png");
		std::shared_ptr<Texture> RightDash = Resources::Load<Texture>(L"RightDash", L"..\\Resources\\Knight\\Knight_Dash_Right.png");

		at->Create(L"Idle_Left", LeftIdle, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 9);
		at->Create(L"Idle_Right", RightIdle, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 9);

		at->Create(L"walk_Left", Leftwalk, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8);
		at->Create(L"walk_Right", Rightwalk, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8);

		at->Create(L"Attack_Left", LeftAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);
		at->Create(L"Attack_Right", RightAttack, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);

		at->Create(L"Dash_Left", LeftDash, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 12);
		at->Create(L"Dash_Right", RightDash, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 12);

		at->PlayAnimation(L"Idle_Right", true);

		//VectorR velocity = mRigidbody->GetVelocity();

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
		case PlayerScript::PlayerState::Dash:
			Dash();
			break;
		case PlayerScript::PlayerState::Attack:
			Attack();
			break;
		default:
			break;
		}
	}
	void PlayerScript::Complete()
	{
	}

	void PlayerScript::Idle()
	{
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
		else if (Input::GetKeyDown(eKeyCode::C))
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
		else if (Input::GetKeyDown(eKeyCode::X))
		{
			mState = PlayerState::Jump;
			if (direction == 0)
			{
				at->PlayAnimation(L"walk_Left", true);
			}
			else
			{
				at->PlayAnimation(L"walk_Right", true);
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
			}
			else
			{
				at->PlayAnimation(L"Dash_Right", true);
			}
		}
	}

	void PlayerScript::Jump()
	{
		if (Input::GetKeyUp(eKeyCode::C))
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
				pos.x -= 2.0f;
				tr->SetPosition(pos);
				mState = PlayerState::Idle;
				at->PlayAnimation(L"Idle_Left", true);
			}
			else
			{
				pos.x += 2.0f;
				tr->SetPosition(pos);
				mState = PlayerState::Idle;
				at->PlayAnimation(L"Idle_Right", true);
			}
		}
	}

	void PlayerScript::Attack()
	{
		if (Input::GetKeyUp(eKeyCode::C))
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
}