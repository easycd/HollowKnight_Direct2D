#include "kmGrimm.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmGroundScript.h"
#include "kmObject.h"
#include "kmRigidbody.h"
#include "kmGroundScript.h"
#include "kmWall.h"
#include "kmPlayer.h"
#include "kmMeshRenderer.h"
#include "kmRigidbodyMath.h"

//Object
#include "kmSpike_Object.h"
#include "kmFlameBat.h"
#include "kmFIreBall.h"

//Effect
#include "kmAirDash_Effect.h"
#include "kmGroundDash_Effect.h"

namespace km
{
	Grimm::Grimm()
		: mPattern_Timing(0.0f)
		, PatternState(4)
		, AirDash_On_Location(0)
		, Balloon_Loop_Delay(0.0f)
		, FireBall_Delay_time(0.0f)
		, CapSpike_Loop_Delay(0.0f)
		, FlameBat_Delay(0.0f)
		, Cast_Delay(0.0f)
		, Slash_On_Delay(0.0f)
	{
	}
	Grimm::~Grimm()
	{
	}
	void Grimm::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Idle = Resources::Load<Texture>(L"Idle", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Idle\\Idle.png");
		std::shared_ptr<Texture> Death = Resources::Load<Texture>(L"Death", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Death\\Death.png");

		//TelePort
		std::shared_ptr<Texture> Tele_Out = Resources::Load<Texture>(L"Tele_Out", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOut\\Tele_Out.png");
		std::shared_ptr<Texture> Tele_In = Resources::Load<Texture>(L"Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOn\\Tele_In.png");

		//AirDash
		std::shared_ptr<Texture> AirDash_Tele_In = Resources::Load<Texture>(L"AirDash_Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\On\\AirDashOn.png");

		std::shared_ptr<Texture> AirDash_Attack1_Left = Resources::Load<Texture>(L"AirDash_Attack1_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Grimm_AirDash_Attack1\\Left\\AirDash_Attack1_Left.png");
		std::shared_ptr<Texture> AirDash_Attack1_Right = Resources::Load<Texture>(L"AirDash_Attack1_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Grimm_AirDash_Attack1\\Right\\AirDash_Attack1_Right.png");
		std::shared_ptr<Texture> AirDash_Attack2_Left = Resources::Load<Texture>(L"AirDash_Attack2_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Grimm_AirDash_Attack2\\Left\\AirDash_Attack2_Left.png");
		std::shared_ptr<Texture> AirDash_Attack2_Right = Resources::Load<Texture>(L"AirDash_Attack2_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Grimm_AirDash_Attack2\\Right\\AirDash_Attack2_Right.png");

		std::shared_ptr<Texture> AirDash_Lend_Left = Resources::Load<Texture>(L"AirDash_Lend_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\1_Land\\Left\\AirDashLand_Left.png");
		std::shared_ptr<Texture> AirDash_Lend_Right = Resources::Load<Texture>(L"AirDash_Lend_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\1_Land\\Right\\AirDashLand_Right.png");
		std::shared_ptr<Texture> AirDash_Attack_Left = Resources::Load<Texture>(L"AirDash_Attack_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\2_Attack\\Left\\AirDash_Attack_Left.png");
		std::shared_ptr<Texture> AirDash_Attack_Right = Resources::Load<Texture>(L"AirDash_Attack_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\2_Attack\\Right\\AirDash_Attack_Right.png");
		std::shared_ptr<Texture> AirDash_Attack_Stop_Left = Resources::Load<Texture>(L"AirDash_Attack_Stop_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\1_Land\\Left\\AirDashLand_Left.png");
		std::shared_ptr<Texture> AirDash_Attack_Stop_Right = Resources::Load<Texture>(L"AirDash_Attack_Stop_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\1_Land\\Right\\AirDashLand_Right.png");

		//Balloon
		std::shared_ptr<Texture> Balloon_Tele_In = Resources::Load<Texture>(L"Balloon_Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\On\\AirDashOn.png");
		std::shared_ptr<Texture> Balloon_Start = Resources::Load<Texture>(L"Balloon_Start", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Balloon\\start\\Balloon_Start.png");
		std::shared_ptr<Texture> Balloon_Loop = Resources::Load<Texture>(L"Balloon_Loop", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Balloon\\loop\\Balloon_Loop.png");

		//CapSpike
		std::shared_ptr<Texture> CapSpike_Tele_In = Resources::Load<Texture>(L"CapSpike_Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOn\\Tele_In.png");
		std::shared_ptr<Texture> CapSpike_Start = Resources::Load<Texture>(L"CapSpike_Start", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Capspike\\On\\Capspike_On.png");
		std::shared_ptr<Texture> CapSpike_Loop = Resources::Load<Texture>(L"CapSpike_Loop", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Capspike\\Loop\\Capspike_Loop.png");
		std::shared_ptr<Texture> CapSpike_End = Resources::Load<Texture>(L"CapSpike_End", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Capspike\\End\\Capspike_End.png");

		//Cast
		std::shared_ptr<Texture> Cast_Tele_In = Resources::Load<Texture>(L"Cast_Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOn\\Tele_In.png");
		std::shared_ptr<Texture> Cast_Left = Resources::Load<Texture>(L"Cast_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Cast\\Left\\Grimm_Cast_Left.png");
		std::shared_ptr<Texture> Cast_Right = Resources::Load<Texture>(L"Cast_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Cast\\Right\\Grimm_Cast_Right.png");

		//Slash
		std::shared_ptr<Texture> Slash_Tele_In = Resources::Load<Texture>(L"Slash_Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOn\\Tele_In.png");
		std::shared_ptr<Texture> Slash_On_Left = Resources::Load<Texture>(L"Slash_On_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\On\\Left\\Slash_On_Left.png");
		std::shared_ptr<Texture> Slash_On_Right = Resources::Load<Texture>(L"Slash_On_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\On\\Right\\Slash_On_Right.png");
		std::shared_ptr<Texture> Slash_Left = Resources::Load<Texture>(L"Slash_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Slash\\Left\\Slash_Left.png");
		std::shared_ptr<Texture> Slash_Right = Resources::Load<Texture>(L"Slash_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Slash\\Right\\Slash_Right.png");
		std::shared_ptr<Texture> Up_Slash_Ready_Left = Resources::Load<Texture>(L"Up_Slash_Ready_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack_Delay\\Left\\Up_Attack_Delay_Left.png");
		std::shared_ptr<Texture> Up_Slash_Ready_Right = Resources::Load<Texture>(L"Up_Slash_Ready_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack_Delay\\Right\\Up_Attack_Delay_Right.png");
		std::shared_ptr<Texture> Up_Slash_Left = Resources::Load<Texture>(L"Up_Slash_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack\\Left\\Up_Slash_Left.png");
		std::shared_ptr<Texture> Up_Slash_Right = Resources::Load<Texture>(L"Up_Slash_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack\\Right\\Up_Slash_Right.png");

		mAnimation->Create(L"Idle", Idle, Vector2(0.0f, 0.0f), Vector2(264.0f, 441.0f), 12, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Death", Death, Vector2(0.0f, 0.0f), Vector2(489.0f, 525.0f), 3, Vector2(0.0f, 0.02f), 0.15f);
		mAnimation->Create(L"Tele_Out", Tele_Out, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6, Vector2(0.0f, 0.02f), 0.05f);
		mAnimation->Create(L"Tele_In", Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.05f);

		mAnimation->Create(L"AirDash_Tele_In", AirDash_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6, Vector2(0.0f, 0.02f), 0.05f);
		mAnimation->Create(L"AirDash_Attack1_Left", AirDash_Attack1_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 7, Vector2(0.0f, 0.02f), 0.05f);
		mAnimation->Create(L"AirDash_Attack1_Right", AirDash_Attack1_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 7, Vector2(0.0f, 0.02f), 0.05f);
		mAnimation->Create(L"AirDash_Attack2_Left", AirDash_Attack2_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"AirDash_Attack2_Right", AirDash_Attack2_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"AirDash_Lend_Left", AirDash_Lend_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Lend_Right", AirDash_Lend_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Attack_Left", AirDash_Attack_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Attack_Right", AirDash_Attack_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Attack_Stop_Left", AirDash_Attack_Stop_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Attack_Stop_Right", AirDash_Attack_Stop_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);

		mAnimation->Create(L"Balloon_Tele_In", Balloon_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6, Vector2(0.0f, 0.02f), 0.05f);
		mAnimation->Create(L"Balloon_Start", Balloon_Start, Vector2(0.0f, 0.0f), Vector2(521.0f, 576.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Balloon_Loop", Balloon_Loop, Vector2(0.0f, 0.0f), Vector2(521.0f, 576.0f), 3, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->Create(L"CapSpike_Tele_In", CapSpike_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.05f);
		mAnimation->Create(L"CapSpike_Start", CapSpike_Start, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 10, Vector2(0.0f, 0.02f), 0.08f);
		mAnimation->Create(L"CapSpike_Loop", CapSpike_Loop, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 3, Vector2(0.0f, 0.02f), 0.08f);
		mAnimation->Create(L"CapSpike_End", CapSpike_End, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 7, Vector2(0.0f, 0.02f), 0.08f);

		mAnimation->Create(L"Cast_Tele_In", Cast_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Cast_Left", Cast_Left, Vector2(0.0f, 0.0f), Vector2(546.0f, 444.0f), 8, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Cast_Right", Cast_Right, Vector2(0.0f, 0.0f), Vector2(546.0f, 444.0f), 8, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->Create(L"Slash_Tele_In", Slash_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_On_Left", Slash_On_Left, Vector2(0.0f, 0.0f), Vector2(342.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_On_Right", Slash_On_Right, Vector2(0.0f, 0.0f), Vector2(342.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_Left", Slash_Left, Vector2(0.0f, 0.0f), Vector2(792.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_Right", Slash_Right, Vector2(0.0f, 0.0f), Vector2(792.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Up_Slash_Ready_Left", Up_Slash_Ready_Left, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 3, Vector2(0.0f, -0.02f), 0.12f);
		mAnimation->Create(L"Up_Slash_Ready_Right", Up_Slash_Ready_Right, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 3, Vector2(0.0f, -0.02f), 0.12f);
		mAnimation->Create(L"Up_Slash_Left", Up_Slash_Left, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Up_Slash_Right", Up_Slash_Right, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->CompleteEvent(L"Tele_Out") = std::bind(&Grimm::Tele_Out_End, this);

		mAnimation->CompleteEvent(L"AirDash_Tele_In") = std::bind(&Grimm::AirDash_Start, this);
		mAnimation->CompleteEvent(L"AirDash_Attack1_Left") = std::bind(&Grimm::AirDash_Loop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack1_Right") = std::bind(&Grimm::AirDash_Loop, this);
		mAnimation->CompleteEvent(L"AirDash_Lend_Left") = std::bind(&Grimm::AirDash_Attack, this);
		mAnimation->CompleteEvent(L"AirDash_Lend_Right") = std::bind(&Grimm::AirDash_Attack, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_Left") = std::bind(&Grimm::AirDash_Stop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_Right") = std::bind(&Grimm::AirDash_Stop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_Stop_Left") = std::bind(&Grimm::Tele_Out, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_Stop_Right") = std::bind(&Grimm::Tele_Out, this);

		mAnimation->CompleteEvent(L"Balloon_Tele_In") = std::bind(&Grimm::Balloon_Start, this);
		mAnimation->CompleteEvent(L"Balloon_Start") = std::bind(&Grimm::Balloon_Loop, this);

		mAnimation->CompleteEvent(L"CapSpike_Tele_In") = std::bind(&Grimm::Capspike_On, this);
		mAnimation->CompleteEvent(L"CapSpike_Start") = std::bind(&Grimm::Capspike_Loop, this);
		mAnimation->CompleteEvent(L"CapSpike_End") = std::bind(&Grimm::Tele_Out, this);

		mAnimation->CompleteEvent(L"Cast_Tele_In") = std::bind(&Grimm::Cast, this);

		mAnimation->CompleteEvent(L"Slash_Tele_In") = std::bind(&Grimm::Slash_On, this);
		mAnimation->CompleteEvent(L"Slash_Left") = std::bind(&Grimm::UP_Slash_Ready, this);
		mAnimation->CompleteEvent(L"Slash_Right") = std::bind(&Grimm::UP_Slash_Ready, this);
		mAnimation->CompleteEvent(L"Up_Slash_Ready_Left") = std::bind(&Grimm::Up_Slash, this);
		mAnimation->CompleteEvent(L"Up_Slash_Ready_Right") = std::bind(&Grimm::Up_Slash, this);
		mAnimation->CompleteEvent(L"Up_Slash_Left") = std::bind(&Grimm::Tele_Out, this);
		mAnimation->CompleteEvent(L"Up_Slash_Right") = std::bind(&Grimm::Tele_Out, this);



		mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
		mTransform->SetPosition(Vector3(0.3f, -0.35f, 1.0f));
		mCollider->SetSize(Vector2(0.7f, 1.0f));

		mState = eGrimmState::Idle;
		mDirection = eDirection::Left;

		GameObject::Initialize();
	}
	void Grimm::OnCollisionEnter(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		Wall* wall = dynamic_cast<Wall*>(other->GetOwner());

		if (gd != nullptr)
		{
			Ground_Check = true;
		}

		if (wall != nullptr)
		{
			Wall_Check = true;
		}
	}
	void Grimm::OnCollisionStay(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());

		if (gd != nullptr)
		{
		}
	}
	void Grimm::OnCollisionExit(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		Wall* wall = dynamic_cast<Wall*>(other->GetOwner());

		if (gd != nullptr)
		{
			Ground_Check = false;
		}

		if (wall != nullptr)
		{
			Wall_Check = false;
		}
	}

	void Grimm::Update()
	{
		mGrimmPos = mTransform->GetPosition(); // 그림 위치
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition(); // 캐릭터 위치

		mPlayer_Direction = VectorR(mPlayerPos.x, mPlayerPos.y);
		mGrimm_Direction = VectorR(mTransform->GetPosition().x, mTransform->GetPosition().y);
		dr = rigidmath::Direction(mGrimm_Direction, mPlayer_Direction); //캐릭터 방향
		if (dr.x > 0.0f)
		{
			mLive_Direction = eDirection::Right;
		}
		else
		{
			mLive_Direction = eDirection::Left;
		}

		switch (mState)
		{
		case km::Grimm::eGrimmState::Pattern:
			Pattern();
			break;
		case km::Grimm::eGrimmState::Idle:
			Idle();
			break;
		case km::Grimm::eGrimmState::AirDashTeleIn:
			AirDash_Tele_In();
			break;
		case km::Grimm::eGrimmState::AirDashStart:
			AirDash_Start();
			break;
		case km::Grimm::eGrimmState::AirDashLoop:
			AirDash_Loop();
			break;
		case km::Grimm::eGrimmState::AirDashLand:
			AirDash_Land();
			break;
		case km::Grimm::eGrimmState::AirDashAttack:
			AirDash_Attack();
			break;
		case km::Grimm::eGrimmState::AirDashStop:
			AirDash_Stop();
			break;
		case km::Grimm::eGrimmState::BalloonTeleIn:
			Balloon_Tele_In();
			break;
		case km::Grimm::eGrimmState::BalloonStart:
			Balloon_Start();
			break;
		case km::Grimm::eGrimmState::BalloonLoop:
			Balloon_Loop();
			break;
		case km::Grimm::eGrimmState::CapSpikeTeleIn:
			Capspike_Tele_In();
			break;
		case km::Grimm::eGrimmState::CapSpikeOn:
			Capspike_On();
			break;
		case km::Grimm::eGrimmState::CapSpikeLoop:
			Capspike_Loop();
			break;
		case km::Grimm::eGrimmState::CapSpikeEnd:
			Capspike_End();
			break;
		case km::Grimm::eGrimmState::CastTeleIn:
			Cast_Tele_In();
			break;
		case km::Grimm::eGrimmState::Cast:
			Cast();
			break;
		case km::Grimm::eGrimmState::SlashTeleIn:
			Slash_Tele_In();
			break;
		case km::Grimm::eGrimmState::SlashOn:
			Slash_On();
			break;
		case km::Grimm::eGrimmState::Slash:
			Slash();
			break;
		case km::Grimm::eGrimmState::UpSlashReady:
			UP_Slash_Ready();
			break;
		case km::Grimm::eGrimmState::UpSlash:
			Up_Slash();
			break;
		case km::Grimm::eGrimmState::Tele_In:
			Tele_In();
			break;
		case km::Grimm::eGrimmState::Tele_Out:
			Tele_Out();
			break;
		case km::Grimm::eGrimmState::Tele_Out_End:
			Tele_Out_End();
			break;
		case km::Grimm::eGrimmState::Death:
			Death();
			break;
		default:
			break;
		}


		GameObject::Update();
	}
	void Grimm::Pattern()
	{
		mState = eGrimmState::Pattern;

		//srand(time(NULL));
		//PatternState = rand() % 9;

		switch (PatternState)
		{
		case 0:
			AirDash_Tele_In();
			break;
		case 1:
			Balloon_Tele_In();
			break;
		case 2:
			Capspike_Tele_In();
			break;
		case 3:
			Cast_Tele_In();
			break;
		case 4:
			Slash_Tele_In();
			break;
		case 5:
			AirDash_Tele_In();
			break;
		case 6:
			Slash_Tele_In();
			break;
		case 7:
			AirDash_Tele_In();
			break;
		case 8:
			Cast_Tele_In();
			break;
		case 9:
			AirDash_Tele_In();
			break;
		default:
			break;
		}
	}
	void Grimm::Tele_In()
	{
		mState = eGrimmState::Tele_In;
	}
	void Grimm::Tele_Out()
	{
		mState = eGrimmState::Tele_Out;

		if (Tele_Out_Check)
		{
			mAnimation->PlayAnimation(L"Tele_Out", true);
			mTransform->SetScale(Vector3(0.3f, 0.35f, 0.0f));
			Tele_Out_Check = false;
		}
	}
	void Grimm::Tele_Out_End()
	{
		mState = eGrimmState::Tele_Out_End;

		mPattern_Timing += Time::DeltaTime();
		if (mPattern_Timing > 0.5f)
		{
			mPattern_Timing = 0.0f;
			mState = eGrimmState::Pattern;
		}

		mTransform->SetPosition(Vector3(0.0f, 100.0f, 0.0f));

		Idle_Check = true;
		Tele_Out_Check = true;

		AirDash_Tele_In_Check = true;
		AirDash_Start_Check = true;
		AirDash_Loop_Check = true;
		AirDash_Land_Check = true;
		AirDash_Attack_Check = true;
		AirDash_Stop_Check = true;

		Balloon_Tele_In_Check = true;
		Balloon_Start_Check = true;
		Balloon_Loop_Check = true;

		Capspike_Tele_In_Check = true;
		Capspike_On_Check = true;
		Capspike_Loop_Check = true;
		Capspike_End_Check = true;

		Cast_Tele_In_Check = true;
		Cast_Check = true;

		Slash_Tele_In_Check = true;
		Slash_On_Check = true;
		Slash_Check = true;
		UP_Slash_Ready_Check = true;
		Up_Slash_Check = true;
	}
	void Grimm::Intro()
	{
	}
	void Grimm::Idle()
	{
		mState = eGrimmState::Idle;
		if (Idle_Check)
		{
			mAnimation->PlayAnimation(L"Idle", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Idle_Check = false;
		}

		Test += Time::DeltaTime();
		if (Test > 1.0f)
		{
			mState = eGrimmState::Tele_Out;
			Test = 0.0f;
		}
	}
	void Grimm::AirDash_Tele_In()
	{
		mState = eGrimmState::AirDashTeleIn;

		if (AirDash_Tele_In_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));

			if (AirDash_On_Location == 0)
			{
				mTransform->SetPosition(Vector3(-0.25f, 0.0f, 0.0f));
				AirDash_On_Location++;
			}
			else if (AirDash_On_Location == 1)
			{
				mTransform->SetPosition(Vector3(-0.4f, 0.0f, 0.0f));
				AirDash_On_Location++;
			}
			else if (AirDash_On_Location == 2)
			{
				mTransform->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
				AirDash_On_Location = 0;
			}

			AirDash_Tele_In_Check = false;
		}
	}
	void Grimm::AirDash_Start()
	{
		mState = eGrimmState::AirDashStart;

		if (AirDash_Start_Check)
			mDirection = mLive_Direction;

		if (mDirection == eDirection::Left && AirDash_Start_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack1_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.3f, 0.8f));

			AirDash_Start_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Start_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack1_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.3f, 0.8f));

			AirDash_Start_Check = false;
		}
	}
	void Grimm::AirDash_Loop()
	{
		mState = eGrimmState::AirDashLoop;

		if (AirDash_Loop_Check)
		{
			Dash_Locate = rigidmath::Direction(mGrimm_Direction, mPlayer_Direction);
			mTransform->SetRotation(Vector3(Dash_Locate.x, Dash_Locate.y, 0.0f));
		}

		if (mDirection == eDirection::Left && AirDash_Loop_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack2_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.1f, 0.8f));
			//mAirDash_Effect = object::Instantiate<AirDash_Effect>(eLayerType::Effect);
			//mAirDash_Effect->PlayEffect();
			//mAirDash_Effect->GetComponent<Transform>()->SetPosition(Vector3(mGrimm_Live_Pos.x, mGrimm_Live_Pos.y, 0.0f));
			//mAirDash_Effect->GetComponent<Transform>()->SetRotation(Vector3(Dash_Locate.x, Dash_Locate.y, 0.0f));

			AirDash_Loop_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Loop_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack2_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.1f, 0.8f));
			//mAirDash_Effect = object::Instantiate<AirDash_Effect>(eLayerType::Effect);
			//mAirDash_Effect->PlayEffect();
			//mAirDash_Effect->GetComponent<Transform>()->SetPosition(Vector3(mGrimm_Live_Pos.x, mGrimm_Live_Pos.y, 0.0f));
			//mAirDash_Effect->GetComponent<Transform>()->SetRotation(Vector3(Dash_Locate.x, Dash_Locate.y, 0.0f));

			AirDash_Loop_Check = false;
		}

		if (Ground_Check == false)
		{
			mGrimmPos.x += Dash_Locate.x * Time::DeltaTime() * 2.5f;
			mGrimmPos.y += Dash_Locate.y * Time::DeltaTime() * 2.5f;
			//if (mAirDash_Effect_Check)
			//{
			//	mAirDash_Effect = object::Instantiate<AirDash_Effect>(eLayerType::Effect);
			//	mAirDash_Effect->PlayEffect();
			//	mAirDash_Effect->GetComponent<Transform>()->SetPosition(Vector3(mGrimm_Live_Pos.x, mGrimm_Live_Pos.y, 0.0f));
			//	mAirDash_Effect->GetComponent<Transform>()->SetRotation(Vector3(Dash_Locate.x, Dash_Locate.y, 0.0f));
			//
			//	mAirDash_Effect_Check = false;
			//}
		}
		else if (Ground_Check)
		{
			mState = eGrimmState::AirDashLand;
		}

		mTransform->SetPosition(mGrimmPos);

	}
	void Grimm::AirDash_Land()
	{
		mState = eGrimmState::AirDashLand;

		if (mDirection == eDirection::Left && AirDash_Land_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Lend_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));
			mTransform->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			mTransform->SetPosition(Vector3(mGrimmPos.x, -0.45f, 0.0f));
			mGrimmPos = mTransform->GetPosition();

			AirDash_Land_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Land_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Lend_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));
			mTransform->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			mTransform->SetPosition(Vector3(mGrimmPos.x, -0.45f, 0.0f));
			mGrimmPos = mTransform->GetPosition();

			AirDash_Land_Check = false;
		}
	}
	void Grimm::AirDash_Attack()
	{
		mState = eGrimmState::AirDashAttack;

		if (AirDash_Attack_Check)
			mDirection = mLive_Direction;

		if (mDirection == eDirection::Left && AirDash_Attack_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			//mGroundDash_Effect = object::Instantiate<GroundDash_Effect>(eLayerType::Effect);
			//mGroundDash_Effect->PlayEffect_Left();
			//mGroundDash_Effect->GetComponent<Transform>()->SetPosition(Vector3(mGrimm_Live_Pos.x, mGrimm_Live_Pos.y, 0.0f));

			AirDash_Attack_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Attack_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			//mGroundDash_Effect = object::Instantiate<GroundDash_Effect>(eLayerType::Effect);
			//mGroundDash_Effect->PlayEffect_Right();
			//mGroundDash_Effect->GetComponent<Transform>()->SetPosition(Vector3(mGrimm_Live_Pos.x, mGrimm_Live_Pos.y, 0.0f));

			AirDash_Attack_Check = false;
		}

		//땅에서 돌진할때 체크
		if (mDirection == eDirection::Left)
		{
			if (Wall_Check == false)
			{
				mGrimmPos.x -= 2.5f * Time::DeltaTime();
				mTransform->SetPosition(mGrimmPos);
			}
		}
		else if (mDirection == eDirection::Right)
		{
			if (Wall_Check == false)
			{
				mGrimmPos.x += 2.5f * Time::DeltaTime();
				mTransform->SetPosition(mGrimmPos);
			}
		}

		mTransform->SetPosition(mGrimmPos);
	}
	void Grimm::AirDash_Stop()
	{
		mState = eGrimmState::AirDashStop;

		if (mDirection == eDirection::Left && AirDash_Stop_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_Stop_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));

			AirDash_Stop_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Stop_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_Stop_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));

			AirDash_Stop_Check = false;
		}
	}
	void Grimm::Balloon_Tele_In()
	{
		mState = eGrimmState::BalloonTeleIn;

		if (Balloon_Tele_In_Check)
		{
			mAnimation->PlayAnimation(L"Balloon_Tele_In", true);
			mTransform->SetScale(Vector3(0.3f, 0.35f, 0.0f));
			mTransform->SetPosition(Vector3(-0.25f, -0.1f, 0.0f));
			Balloon_Tele_In_Check = false;
		}
	}
	void Grimm::Balloon_Start()
	{
		mState = eGrimmState::BalloonStart;

		if (Balloon_Start_Check)
		{
			mAnimation->PlayAnimation(L"Balloon_Start", true);
			mTransform->SetScale(Vector3(0.45f, 0.45f, 0.0f));
			Balloon_Start_Check = false;
		}
	}
	void Grimm::Balloon_Loop()
	{
		mState = eGrimmState::BalloonLoop;
		Balloon_Loop_Delay += Time::DeltaTime();
		FireBall_Delay_time += Time::DeltaTime();

		if (Balloon_Loop_Check)
		{
			mAnimation->PlayAnimation(L"Balloon_Loop", true);
			mTransform->SetScale(Vector3(0.45f, 0.45f, 0.0f));
			mTransform->SetPosition(Vector3(-0.25f, -0.1f, 0.0f));
			Balloon_Loop_Check = false;
		}

		if (FireBall_Delay_time > 0.5f)
		{
			FireBall_Delay_time = 0.0f;
			FireBall_Obj();
		}

		if (Balloon_Loop_Delay > 5.0f)
		{
			Balloon_Loop_Delay = 0.0f;
			Tele_Out();
		}
	}
	void Grimm::Capspike_Tele_In()
	{
		mState = eGrimmState::CapSpikeTeleIn;

		if (Capspike_Tele_In_Check)
		{
			mAnimation->PlayAnimation(L"CapSpike_Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			mTransform->SetPosition(Vector3(0.35f, -0.35f, 0.0f));
			Capspike_Tele_In_Check = false;
		}
	}
	void Grimm::Capspike_On()
	{
		mState = eGrimmState::CapSpikeOn;

		if (Capspike_On_Check)
		{
			mAnimation->PlayAnimation(L"CapSpike_Start", true);
			mTransform->SetScale(Vector3(0.35f, 0.4f, 0.0f));
			Capspike_On_Check = false;
		}
	}
	void Grimm::Capspike_Loop()
	{
		mState = eGrimmState::CapSpikeLoop;
		CapSpike_Loop_Delay += Time::DeltaTime();

		if (Capspike_Loop_Check)
		{
			mAnimation->PlayAnimation(L"CapSpike_Loop", true);
			mTransform->SetScale(Vector3(0.35f, 0.4f, 0.0f));
			Capspike_Loop_Check = false;

			Spike_Obj();
		}

		if (CapSpike_Loop_Delay > 2.5f)
		{
			CapSpike_Loop_Delay = 0.0f;
			Capspike_End();
		}
	}
	void Grimm::Capspike_End()
	{
		mState = eGrimmState::CapSpikeEnd;

		if (Capspike_End_Check)
		{
			mAnimation->PlayAnimation(L"CapSpike_End", true);
			mTransform->SetScale(Vector3(0.35f, 0.4f, 0.0f));
			Capspike_End_Check = false;
		}
	}
	void Grimm::Cast_Tele_In()
	{
		mState = eGrimmState::CastTeleIn;

		if (mPlayerPos.x > -0.2f)
			mDirection = eDirection::Right;

		if (mPlayerPos.x < -0.2f)
			mDirection = eDirection::Left;

		if (Cast_Tele_In_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Cast_Tele_In", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			mTransform->SetPosition(Vector3(0.5f, -0.35f, 0.0f));
			Cast_Tele_In_Check = false;
		}

		if (Cast_Tele_In_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Cast_Tele_In", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			mTransform->SetPosition(Vector3(-0.72f, -0.35f, 0.0f));
			Cast_Tele_In_Check = false;
		}
	}
	void Grimm::Cast()
	{
		mState = eGrimmState::Cast;
		Cast_Delay += Time::DeltaTime();
		FlameBat_Delay += Time::DeltaTime();

		if (mDirection == eDirection::Left && Cast_Check)
		{
			mAnimation->PlayAnimation(L"Cast_Left", false);
			Cast_Check = false;
			Bat0_Play = true;
		}

		if (mDirection == eDirection::Right && Cast_Check)
		{
			mAnimation->PlayAnimation(L"Cast_Right", false);
			Cast_Check = false;
			Bat0_Play = true;
		}

		if (Bat0_Play && FlameBat_Delay > 1.0f)
		{
			Bat0 = object::Instantiate<FlameBat>(Vector3(mGrimmPos.x, mGrimmPos.y, 0.0f), eLayerType::BossObj);
			if (mDirection == eDirection::Left)
			{
				Bat0->On_Left();
			}
			if (mDirection == eDirection::Right)
			{
				Bat0->On_Right();
			}

			Bat0_Play = false;
			Bat1_Play = true;
		}

		if (Bat1_Play && FlameBat_Delay > 2.0f)
		{
			Bat1 = object::Instantiate<FlameBat>(Vector3(mGrimmPos.x, mGrimmPos.y, 0.0f), eLayerType::BossObj);
			if (mDirection == eDirection::Left)
			{
				Bat1->On_Left();
			}
			if (mDirection == eDirection::Right)
			{
				Bat1->On_Right();
			}

			Bat1_Play = false;
			Bat2_Play = true;
		}

		if (Bat2_Play && FlameBat_Delay > 3.0f)
		{
			Bat2 = object::Instantiate<FlameBat>(Vector3(mGrimmPos.x, mGrimmPos.y, 0.0f), eLayerType::BossObj);
			if (mDirection == eDirection::Left)
			{
				Bat2->On_Left();
			}
			if (mDirection == eDirection::Right)
			{
				Bat2->On_Right();
			}

			Bat2_Play = false;
		}

		if (Cast_Delay > 5.0f)
		{
			Cast_Delay = 0.0;
			FlameBat_Delay = 0.0f;
			Tele_Out();
		}
	}
	void Grimm::Slash_Tele_In()
	{
		mState = eGrimmState::SlashTeleIn;

		if (Slash_Tele_In_Check)
			mDirection = mLive_Direction;

		if (Slash_Tele_In_Check)
		{
			mAnimation->PlayAnimation(L"Slash_Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Slash_Tele_In_Check = false;

			if (mDirection == eDirection::Left)
			{
				if (mPlayerPos.x < 0.241f)
				{
					mTransform->SetPosition(Vector3(mPlayerPos.x + 0.5, -0.35f, 0.0f));
				}
				else
				{
					mTransform->SetPosition(Vector3(0.756f, -0.35f, 0.0f));
				}
			}

			if (mDirection == eDirection::Right)
			{
				if (mPlayerPos.x > -0.493f)
				{
					mTransform->SetPosition(Vector3(mPlayerPos.x - 0.5, -0.35f, 0.0f));
				}
				else
				{
					mTransform->SetPosition(Vector3(-1.0f, -0.35f, 0.0f));
				}
			}
		}
	}
	void Grimm::Slash_On()
	{
		mState = eGrimmState::SlashOn;
		Slash_On_Delay += Time::DeltaTime();

		if (mDirection == eDirection::Left && Slash_On_Check)
		{
			mAnimation->PlayAnimation(L"Slash_On_Left", false);
			mTransform->SetScale(Vector3(0.3f, 0.4f, 0.0f));
			Slash_On_Check = false;
		}

		if (mDirection == eDirection::Right && Slash_On_Check)
		{
			mAnimation->PlayAnimation(L"Slash_On_Right", false);
			mTransform->SetScale(Vector3(0.3f, 0.4f, 0.0f));
			Slash_On_Check = false;
		}

		if (Slash_On_Delay > 1.0f)
		{
			Slash_On_Delay = 0.0f;
			Slash();
		}
	}
	void Grimm::Slash()
	{
		mState = eGrimmState::Slash;

		if (mDirection == eDirection::Left && Slash_Check)
		{
			mAnimation->PlayAnimation(L"Slash_Left", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Slash_Check = false;
		}

		if (mDirection == eDirection::Right && Slash_Check)
		{
			mAnimation->PlayAnimation(L"Slash_Right", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Slash_Check = false;
		}


		if (mDirection == eDirection::Left)
		{
			if (Wall_Check == false)
			{
				mGrimmPos.x -= 2.0f * Time::DeltaTime();
			}
		}
		else if (mDirection == eDirection::Right)
		{
			if (Wall_Check == false)
			{
				mGrimmPos.x += 2.0f * Time::DeltaTime();
			}
		}

		mTransform->SetPosition(mGrimmPos);
	}
	void Grimm::UP_Slash_Ready()
	{
		mState = eGrimmState::UpSlashReady;

		if (mDirection == eDirection::Left && UP_Slash_Ready_Check)
		{
			mAnimation->PlayAnimation(L"Up_Slash_Ready_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mTransform->SetPosition(Vector3(mGrimmPos.x, -0.4f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			UP_Slash_Ready_Check = false;
		}

		if (mDirection == eDirection::Right && UP_Slash_Ready_Check)
		{
			mAnimation->PlayAnimation(L"Up_Slash_Ready_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mTransform->SetPosition(Vector3(mGrimmPos.x, -0.4f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			UP_Slash_Ready_Check = false;
		}
	}
	void Grimm::Up_Slash()
	{
		mState = eGrimmState::UpSlash;

		if (mDirection == eDirection::Left && Up_Slash_Check)
		{
			mAnimation->PlayAnimation(L"Up_Slash_Left", true);
			mTransform->SetScale(Vector3(0.5f, 0.6f, 0.0f));
			Up_Slash_Check = false;
		}

		if (mDirection == eDirection::Right && Up_Slash_Check)
		{
			mAnimation->PlayAnimation(L"Up_Slash_Right", true);
			mTransform->SetScale(Vector3(0.5f, 0.6f, 0.0f));
			Up_Slash_Check = false;
		}

		if (mGrimmPos.y < 0.1f)
		{
			if (mDirection == eDirection::Left)
			{
				if (Wall_Check == false)
				{
					mGrimmPos.x -= 1.5f * Time::DeltaTime();
					mGrimmPos.y += 1.5f * Time::DeltaTime();
				}
				else if (Wall_Check)
				{
					mGrimmPos.y += 1.5f * Time::DeltaTime();
				}
			}
			else if (mDirection == eDirection::Right)
			{
				if (Wall_Check == false)
				{
					mGrimmPos.x += 1.5f * Time::DeltaTime();
					mGrimmPos.y += 1.5f * Time::DeltaTime();
				}
				else if (Wall_Check)
				{
					mGrimmPos.y += 1.5f * Time::DeltaTime();
				}
			}
		}

		mTransform->SetPosition(mGrimmPos);
	}
	void Grimm::Death()
	{
		mState = eGrimmState::Death;
	}
	void Grimm::Spike_Obj()
	{
		Spike0 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike1 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike2 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike3 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike4 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike5 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike6 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike7 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike8 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike9 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike10 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike11 = object::Instantiate<Spike_Object>(eLayerType::BossObj);
		Spike12 = object::Instantiate<Spike_Object>(eLayerType::BossObj);


		Spike0->GetComponent<Transform>()->SetPosition(Vector3(-1.1f, -0.25f, 9.0f));
		Spike1->GetComponent<Transform>()->SetPosition(Vector3(-0.95f, -0.25f, 9.0f));
		Spike2->GetComponent<Transform>()->SetPosition(Vector3(-0.8f, -0.25f, 9.0f));
		Spike3->GetComponent<Transform>()->SetPosition(Vector3(-0.65f, -0.25f, 9.0f));
		Spike4->GetComponent<Transform>()->SetPosition(Vector3(-0.5f, -0.25f, 9.0f));
		Spike5->GetComponent<Transform>()->SetPosition(Vector3(-0.35f, -0.25f, 9.0f));
		Spike6->GetComponent<Transform>()->SetPosition(Vector3(-0.2f, -0.25f, 9.0f));
		Spike7->GetComponent<Transform>()->SetPosition(Vector3(-0.05f, -0.25f, 9.0f));
		Spike8->GetComponent<Transform>()->SetPosition(Vector3(0.1f, -0.25f, 9.0f));
		Spike9->GetComponent<Transform>()->SetPosition(Vector3(0.25f, -0.25f, 9.0f));
		Spike10->GetComponent<Transform>()->SetPosition(Vector3(0.4f, -0.25f, 9.0f));
		Spike11->GetComponent<Transform>()->SetPosition(Vector3(0.55f, -0.25f, 9.0f));
		Spike12->GetComponent<Transform>()->SetPosition(Vector3(0.7f, -0.25f, 9.0f));

		Spike0->Spike_On_Delay();
		Spike1->Spike_On_Delay();
		Spike2->Spike_On_Delay();
		Spike3->Spike_On_Delay();
		Spike4->Spike_On_Delay();
		Spike5->Spike_On_Delay();
		Spike6->Spike_On_Delay();
		Spike7->Spike_On_Delay();
		Spike8->Spike_On_Delay();
		Spike9->Spike_On_Delay();
		Spike10->Spike_On_Delay();
		Spike11->Spike_On_Delay();
		Spike12->Spike_On_Delay();
	}
	void Grimm::FireBall_Obj()
	{
		object::FireBall_Instantiate0<FIreBall>(Vector3(-0.3f, -0.08f, 0.0f), eLayerType::BossObj);
		object::FireBall_Instantiate1<FIreBall>(Vector3(-0.2f, -0.08f, 0.0f), eLayerType::BossObj);
		object::FireBall_Instantiate2<FIreBall>(Vector3(-0.3f, -0.15f, 0.0f), eLayerType::BossObj);
		object::FireBall_Instantiate3<FIreBall>(Vector3(-0.2f, -0.15, 0.0f), eLayerType::BossObj);
		object::FireBall_Instantiate4<FIreBall>(Vector3(-0.32f, -0.2f, 0.0f), eLayerType::BossObj);
		object::FireBall_Instantiate5<FIreBall>(Vector3(-0.3f, -0.25f, 0.0f), eLayerType::BossObj);
		object::FireBall_Instantiate6<FIreBall>(Vector3(-0.25f, -0.27f, 0.0f), eLayerType::BossObj);
		object::FireBall_Instantiate7<FIreBall>(Vector3(-0.2f, -0.25f, 0.0f), eLayerType::BossObj);
		object::FireBall_Instantiate8<FIreBall>(Vector3(-0.18f, -0.2f, 0.0f), eLayerType::BossObj);
	}
}