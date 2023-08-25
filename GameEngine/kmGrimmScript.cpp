#include "kmGrimmScript.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmGroundScript.h"
#include "kmObject.h"
#include "kmRigidbody.h"
#include "kmGroundScript.h"

namespace km
{
	GrimmScript::GrimmScript()
		:mTime(0.0f)
		,Test(true)
	{
	}
	GrimmScript::~GrimmScript()
	{
	}

	void GrimmScript::Initialize()
	{
		mAnimation = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		std::shared_ptr<Texture> Idle = Resources::Load<Texture>(L"Idle", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Idle\\Idle.png");
		std::shared_ptr<Texture> Death = Resources::Load<Texture>(L"Death", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Death\\Death.png");

		//TelePort
		std::shared_ptr<Texture> Tele_Out = Resources::Load<Texture>(L"Tele_Out", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOut\\Tele_Out.png");
		std::shared_ptr<Texture> Tele_In = Resources::Load<Texture>(L"Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOn\\Tele_In.png");

		//AirDash
		std::shared_ptr<Texture> AirDash_Attack_On = Resources::Load<Texture>(L"AirDash_Attack_On", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\On\\AirDashOn.png");

		std::shared_ptr<Texture> AirDash_Attack1_Left = Resources::Load<Texture>(L"AirDash_Attack1_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Grimm_AirDash_Attack1\\Left\\AirDash_Attack1_Left.png");
		std::shared_ptr<Texture> AirDash_Attack1_Right = Resources::Load<Texture>(L"AirDash_Attack1_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Grimm_AirDash_Attack1\\Right\\AirDash_Attack1_Right.png");
		std::shared_ptr<Texture> AirDash_Attack2_Left = Resources::Load<Texture>(L"AirDash_Attack2_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Grimm_AirDash_Attack2\\Left\\AirDash_Attack2_Left.png");
		std::shared_ptr<Texture> AirDash_Attack2_Right = Resources::Load<Texture>(L"AirDash_Attack2_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Grimm_AirDash_Attack2\\Right\\AirDash_Attack2_Right.png");

		std::shared_ptr<Texture> AirDash_Lend_Left = Resources::Load<Texture>(L"AirDash_Lend_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\1_Land\\Left\\AirDashLand_Left.png");
		std::shared_ptr<Texture> AirDash_Lend_Right = Resources::Load<Texture>(L"AirDash_Lend_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\1_Land\\Right\\AirDashLand_Right.png");
		std::shared_ptr<Texture> AirDash_Attack_Left = Resources::Load<Texture>(L"AirDash_Attack_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\2_Attack\\Left\\AirDash_Attack_Left.png");
		std::shared_ptr<Texture> AirDash_Attack_Right = Resources::Load<Texture>(L"AirDash_Attack_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\2_Attack\\Right\\AirDash_Attack_Right.png");
		std::shared_ptr<Texture> AirDash_Stop_Left = Resources::Load<Texture>(L"AirDash_Stop_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\3_Stop\\Left\\AirDash_Stop_Left.png");
		std::shared_ptr<Texture> AirDash_Stop_Right = Resources::Load<Texture>(L"AirDash_Stop_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\3_Stop\\Right\\AirDash_Stop_Right.png");

		//Balloon
		std::shared_ptr<Texture> Balloon_Start = Resources::Load<Texture>(L"Balloon_Start", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Balloon\\start\\Balloon_Start.png");
		std::shared_ptr<Texture> Balloon_Loop = Resources::Load<Texture>(L"Balloon_Loop", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Balloon\\loop\\Balloon_Loop.png");

		//CapSpike
		std::shared_ptr<Texture> CapSpike_Start = Resources::Load<Texture>(L"CapSpike_Start", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Capspike\\On\\Capspike_On.png");
		std::shared_ptr<Texture> CapSpike_Loop = Resources::Load<Texture>(L"CapSpike_Loop", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Capspike\\Loop\\Capspike_Loop.png");
		std::shared_ptr<Texture> CapSpike_End = Resources::Load<Texture>(L"CapSpike_End", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Capspike\\End\\Capspike_End.png");

		//Cast
		std::shared_ptr<Texture> Cast_Left = Resources::Load<Texture>(L"Cast_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Cast\\Left\\Grimm_Cast_Left.png");
		std::shared_ptr<Texture> Cast_Right = Resources::Load<Texture>(L"Cast_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Cast\\Right\\Grimm_Cast_Right.png");

		//Slash
		std::shared_ptr<Texture> Slash_On_Left = Resources::Load<Texture>(L"Slash_On_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\On\\Left\\Slash_On_Left.png");
		std::shared_ptr<Texture> Slash_On_Right = Resources::Load<Texture>(L"Slash_On_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\On\\Right\\Slash_On_Right.png");
		std::shared_ptr<Texture> Slash_Left = Resources::Load<Texture>(L"Slash_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Slash\\Left\\Slash_Left.png");
		std::shared_ptr<Texture> Slash_Right = Resources::Load<Texture>(L"Slash_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Slash\\Right\\Slash_Right.png");
		std::shared_ptr<Texture> Up_Slash_Left = Resources::Load<Texture>(L"Up_Slash_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack\\Left\\Up_Slash_Left.png");
		std::shared_ptr<Texture> Up_Slash_Right = Resources::Load<Texture>(L"Up_Slash_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack\\Right\\Up_Slash_Right.png");

		mAnimation->Create(L"Idle", Idle, Vector2(0.0f, 0.0f), Vector2(264.0f, 441.0f), 12);
		mAnimation->Create(L"Death", Death, Vector2(0.0f, 0.0f), Vector2(489.0f, 525.0f), 3);
		mAnimation->Create(L"Tele_Out", Tele_Out, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6);
		mAnimation->Create(L"Tele_In", Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5);
		mAnimation->Create(L"AirDash_Attack_On", AirDash_Attack_On, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6);
		mAnimation->Create(L"AirDash_Attack1_Left", AirDash_Attack1_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 7);
		mAnimation->Create(L"AirDash_Attack1_Right", AirDash_Attack1_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 7);
		mAnimation->Create(L"AirDash_Attack2_Left", AirDash_Attack2_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 3);
		mAnimation->Create(L"AirDash_Attack2_Right", AirDash_Attack2_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 3);
		mAnimation->Create(L"AirDash_Lend_Left", AirDash_Lend_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4);
		mAnimation->Create(L"AirDash_Lend_Right", AirDash_Lend_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4);
		mAnimation->Create(L"AirDash_Attack_Left", AirDash_Attack_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4);
		mAnimation->Create(L"AirDash_Attack_Right", AirDash_Attack_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4);
		mAnimation->Create(L"AirDash_Stop_Left", AirDash_Stop_Left, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 3);
		mAnimation->Create(L"AirDash_Stop_Right", AirDash_Stop_Right, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 3);
		mAnimation->Create(L"Balloon_Start", Balloon_Start, Vector2(0.0f, 0.0f), Vector2(521.0f, 576.0f), 5);
		mAnimation->Create(L"Balloon_Loop", Balloon_Loop, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 3);
		mAnimation->Create(L"CapSpike_Start", CapSpike_Start, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 10);
		mAnimation->Create(L"CapSpike_Loop", CapSpike_Loop, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 3);
		mAnimation->Create(L"CapSpike_End", CapSpike_End, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 7);
		mAnimation->Create(L"Cast_Left", Cast_Left, Vector2(0.0f, 0.0f), Vector2(546.0f, 444.0f), 8);
		mAnimation->Create(L"Cast_Right", Cast_Right, Vector2(0.0f, 0.0f), Vector2(546.0f, 444.0f), 8);
		mAnimation->Create(L"Slash_On_Left", Slash_On_Left, Vector2(0.0f, 0.0f), Vector2(342.0f, 438.0f), 4);
		mAnimation->Create(L"Slash_On_Right", Slash_On_Right, Vector2(0.0f, 0.0f), Vector2(342.0f, 438.0f), 4);
		mAnimation->Create(L"Slash_Left", Slash_Left, Vector2(0.0f, 0.0f), Vector2(792.0f, 438.0f), 4);
		mAnimation->Create(L"Slash_Right", Slash_Right, Vector2(0.0f, 0.0f), Vector2(792.0f, 438.0f), 4);
		mAnimation->Create(L"Up_Slash_Left", Up_Slash_Left, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 4);
		mAnimation->Create(L"Up_Slash_Right", Up_Slash_Right, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 4);


		mAnimation->CompleteEvent(L"AirDash_Attack_On") = std::bind(&GrimmScript::AirDash_Start, this);
		mAnimation->CompleteEvent(L"AirDash_Attack1_Left") = std::bind(&GrimmScript::AirDash_Loop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack1_Right") = std::bind(&GrimmScript::AirDash_Loop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack2_Left") = std::bind(&GrimmScript::AirDash_Land, this);
		mAnimation->CompleteEvent(L"AirDash_Attack2_Right") = std::bind(&GrimmScript::AirDash_Land, this);
		mAnimation->CompleteEvent(L"AirDash_Lend_Left") = std::bind(&GrimmScript::AirDash_Attack, this);
		mAnimation->CompleteEvent(L"AirDash_Lend_Right") = std::bind(&GrimmScript::AirDash_Attack, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_Left") = std::bind(&GrimmScript::AirDash_Stop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_Right") = std::bind(&GrimmScript::AirDash_Stop, this);
		mAnimation->CompleteEvent(L"AirDash_Stop_Left") = std::bind(&GrimmScript::Tele_Out, this);
		mAnimation->CompleteEvent(L"AirDash_Stop_Right") = std::bind(&GrimmScript::Tele_Out, this);

		mAnimation->CompleteEvent(L"Balloon_Start") = std::bind(&GrimmScript::Balloon_Loop, this);
		mAnimation->CompleteEvent(L"Balloon_Loop") = std::bind(&GrimmScript::Tele_Out, this);

		mAnimation->CompleteEvent(L"CapSpike_Start") = std::bind(&GrimmScript::Capspike_Loop, this);
		mAnimation->CompleteEvent(L"CapSpike_Loop") = std::bind(&GrimmScript::Capspike_End, this);
		mAnimation->CompleteEvent(L"CapSpike_End") = std::bind(&GrimmScript::Tele_Out, this);

		mAnimation->CompleteEvent(L"Cast_Left") = std::bind(&GrimmScript::Tele_Out, this);
		mAnimation->CompleteEvent(L"Cast_Right") = std::bind(&GrimmScript::Tele_Out, this);

		mAnimation->CompleteEvent(L"Slash_On_Left") = std::bind(&GrimmScript::Slash, this);
		mAnimation->CompleteEvent(L"Slash_On_Right") = std::bind(&GrimmScript::Slash, this);
		mAnimation->CompleteEvent(L"Slash_Left") = std::bind(&GrimmScript::Up_Slash, this);
		mAnimation->CompleteEvent(L"Slash_Right") = std::bind(&GrimmScript::Up_Slash, this);
		mAnimation->CompleteEvent(L"Up_Slash_Left") = std::bind(&GrimmScript::Tele_Out, this);
		mAnimation->CompleteEvent(L"Up_Slash_Right") = std::bind(&GrimmScript::Tele_Out, this);


		mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
		Collider2D* collider = GetOwner()->AddComponent<Collider2D>();

		mRigidbody = GetOwner()->AddComponent<Rigidbody>();
		mRigidbody->SetMass(0.1f);
		VectorR velocity = mRigidbody->GetVelocity();
		velocity.y -= 0.1f;
		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);

		mState = eGrimmState::Idle;
		mDirection = eDirection::Left;
	}

	void GrimmScript::Update()
	{

		switch (mState)
		{
		case km::GrimmScript::eGrimmState::Idle:
			Idle();
			break;
		case km::GrimmScript::eGrimmState::AirDashOn:
			AirDash_On();
			break;
		case km::GrimmScript::eGrimmState::AirDashStart:
			AirDash_Start();
			break;
		case km::GrimmScript::eGrimmState::AirDashLoop:
			AirDash_Loop();
			break;
		case km::GrimmScript::eGrimmState::AirDashLand:
			AirDash_Land();
			break;
		case km::GrimmScript::eGrimmState::AirDashAttack:
			AirDash_Attack();
			break;
		case km::GrimmScript::eGrimmState::AirDashStop:
			AirDash_Stop();
			break;
		case km::GrimmScript::eGrimmState::BalloonStart:
			Balloon_Start();
			break;
		case km::GrimmScript::eGrimmState::BalloonLoop:
			Balloon_Loop();
			break;
		case km::GrimmScript::eGrimmState::CapSpikeOn:
			Capspike_On();
			break;
		case km::GrimmScript::eGrimmState::CapSpikeLoop:
			Capspike_Loop();
			break;
		case km::GrimmScript::eGrimmState::CapSpikeEnd:
			Capspike_End();
			break;
		case km::GrimmScript::eGrimmState::Cast:
			Cast();
			break;
		case km::GrimmScript::eGrimmState::SlashOn:
			Slash_On();
			break;
		case km::GrimmScript::eGrimmState::Slash:
			Slash();
			break;
		case km::GrimmScript::eGrimmState::UpSlash:
			Up_Slash();
			break;
		case km::GrimmScript::eGrimmState::Tele_In:
			Tele_In();
			break;
		case km::GrimmScript::eGrimmState::Tele_Out:
			Tele_Out();
			break;
		case km::GrimmScript::eGrimmState::Death:
			Death();
			break;
		case km::GrimmScript::eGrimmState::End:
			break;
		default:
			break;
		}
	}

	void GrimmScript::OnCollisionEnter(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());

		if (gd != nullptr)
		{
			mRigidbody->SetGround(true);
		}
	}

	void GrimmScript::OnCollisionStay(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());

		if (gd != nullptr)
		{
			mRigidbody->SetGround(true);
		}
	}

	void GrimmScript::OnCollisionExit(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		if (gd != nullptr)
		{
			mRigidbody->SetGround(false);
		}
	}

	void GrimmScript::Idle()
	{
		if (Test)
		{
			mState = eGrimmState::Idle;
			mAnimation->PlayAnimation(L"Idle", true);
			Test = false;
		}
	}

	void GrimmScript::AirDash_On()
	{
	}

	void GrimmScript::AirDash_Start()
	{
	}

	void GrimmScript::AirDash_Loop()
	{
	}

	void GrimmScript::AirDash_Land()
	{
	}

	void GrimmScript::AirDash_Attack()
	{
	}

	void GrimmScript::AirDash_Stop()
	{
	}

	void GrimmScript::Balloon_Start()
	{
	}

	void GrimmScript::Balloon_Loop()
	{
	}

	void GrimmScript::Capspike_On()
	{
	}

	void GrimmScript::Capspike_Loop()
	{
	}

	void GrimmScript::Capspike_End()
	{
	}

	void GrimmScript::Cast()
	{
	}

	void GrimmScript::Slash_On()
	{
	}

	void GrimmScript::Slash()
	{
	}

	void GrimmScript::Up_Slash()
	{
	}

	void GrimmScript::Tele_In()
	{
	}

	void GrimmScript::Tele_Out()
	{
	}

	void GrimmScript::Death()
	{
	}


}