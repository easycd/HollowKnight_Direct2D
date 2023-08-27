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
#include "kmPlayer.h"
#include "kmMeshRenderer.h"
#include "kmRigidbodyMath.h"

namespace km
{
	Grimm::Grimm()
		: mTime(0.0f)
		, AirDash_Attack_Delay(0.0f)
		, mDr(0)

		, Test(true)
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
		//mRigidbody = AddComponent<Rigidbody>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

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
		std::shared_ptr<Texture> AirDash_Attack_Stop_Left = Resources::Load<Texture>(L"AirDash_Attack_Stop_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\1_Land\\Left\\AirDashLand_Left.png");
		std::shared_ptr<Texture> AirDash_Attack_Stop_Right = Resources::Load<Texture>(L"AirDash_Attack_Stop_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\1_Land\\Right\\AirDashLand_Right.png");

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
		std::shared_ptr<Texture> AirDash_Stop_Left = Resources::Load<Texture>(L"Up_Slash_Ready_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\3_Stop\\Left\\AirDash_Stop_Left.png");
		std::shared_ptr<Texture> AirDash_Stop_Right = Resources::Load<Texture>(L"Up_Slash_Ready_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\3_Stop\\Right\\AirDash_Stop_Right.png");
		std::shared_ptr<Texture> Up_Slash_Left = Resources::Load<Texture>(L"Up_Slash_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack\\Left\\Up_Slash_Left.png");
		std::shared_ptr<Texture> Up_Slash_Right = Resources::Load<Texture>(L"Up_Slash_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack\\Right\\Up_Slash_Right.png");

		mAnimation->Create(L"Idle", Idle, Vector2(0.0f, 0.0f), Vector2(264.0f, 441.0f), 12, Vector2(0.0f, 0.02f), 0.2f);
		mAnimation->Create(L"Death", Death, Vector2(0.0f, 0.0f), Vector2(489.0f, 525.0f), 3, Vector2(0.0f, 0.02f), 0.15f);
		mAnimation->Create(L"Tele_Out", Tele_Out, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6, Vector2(0.0f, 0.02f), 0.2f);
		mAnimation->Create(L"Tele_In", Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.2f);

		mAnimation->Create(L"AirDash_Attack_On", AirDash_Attack_On, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"AirDash_Attack1_Left", AirDash_Attack1_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 7, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"AirDash_Attack1_Right", AirDash_Attack1_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 7, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"AirDash_Attack2_Left", AirDash_Attack2_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"AirDash_Attack2_Right", AirDash_Attack2_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"AirDash_Lend_Left", AirDash_Lend_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Lend_Right", AirDash_Lend_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Attack_Left", AirDash_Attack_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Attack_Right", AirDash_Attack_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Attack_Stop_Left", AirDash_Attack_Stop_Left, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);
		mAnimation->Create(L"AirDash_Attack_Stop_Right", AirDash_Attack_Stop_Right, Vector2(0.0f, 0.0f), Vector2(900.0f, 525.0f), 4, Vector2(0.0f, -0.15f), 0.1f);


		mAnimation->Create(L"Balloon_Start", Balloon_Start, Vector2(0.0f, 0.0f), Vector2(521.0f, 576.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Balloon_Loop", Balloon_Loop, Vector2(0.0f, 0.0f), Vector2(521.0f, 576.0f), 3, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->Create(L"CapSpike_Start", CapSpike_Start, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 10, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"CapSpike_Loop", CapSpike_Loop, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"CapSpike_End", CapSpike_End, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 7, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->Create(L"Cast_Left", Cast_Left, Vector2(0.0f, 0.0f), Vector2(546.0f, 444.0f), 8, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Cast_Right", Cast_Right, Vector2(0.0f, 0.0f), Vector2(546.0f, 444.0f), 8, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->Create(L"Slash_On_Left", Slash_On_Left, Vector2(0.0f, 0.0f), Vector2(342.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_On_Right", Slash_On_Right, Vector2(0.0f, 0.0f), Vector2(342.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_Left", Slash_Left, Vector2(0.0f, 0.0f), Vector2(792.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_Right", Slash_Right, Vector2(0.0f, 0.0f), Vector2(792.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Up_Slash_Ready_Left", AirDash_Stop_Left, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 3, Vector2(0.0f, -0.02f), 0.1f);
		mAnimation->Create(L"Up_Slash_Ready_Right", AirDash_Stop_Right, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 3, Vector2(0.0f, -0.02f), 0.1f);
		mAnimation->Create(L"Up_Slash_Left", Up_Slash_Left, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Up_Slash_Right", Up_Slash_Right, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 4, Vector2(0.0f, 0.02f), 0.1f);


		mAnimation->CompleteEvent(L"AirDash_Attack_On") = std::bind(&Grimm::AirDash_Start, this);
		mAnimation->CompleteEvent(L"AirDash_Attack1_Left") = std::bind(&Grimm::AirDash_Loop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack1_Right") = std::bind(&Grimm::AirDash_Loop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack2_Left") = std::bind(&Grimm::AirDash_Loop_Move, this);
		mAnimation->CompleteEvent(L"AirDash_Attack2_Right") = std::bind(&Grimm::AirDash_Loop_Move, this);
		//mAnimation->CompleteEvent(L"AirDash_Attack2_Left") = std::bind(&Grimm::AirDash_Land, this);
		//mAnimation->CompleteEvent(L"AirDash_Attack2_Right") = std::bind(&Grimm::AirDash_Land, this);
		mAnimation->CompleteEvent(L"AirDash_Lend_Left") = std::bind(&Grimm::AirDash_Attack, this);
		mAnimation->CompleteEvent(L"AirDash_Lend_Right") = std::bind(&Grimm::AirDash_Attack, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_Left") = std::bind(&Grimm::AirDash_Stop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_Right") = std::bind(&Grimm::AirDash_Stop, this);
		//mAnimation->CompleteEvent(L"AirDash_Attack_Left") = std::bind(&Grimm::AirDash_Stop, this);
		//mAnimation->CompleteEvent(L"AirDash_Attack_Right") = std::bind(&Grimm::AirDash_Stop, this);
		//mAnimation->CompleteEvent(L"AirDash_Stop_Left") = std::bind(&Grimm::Tele_Out, this);
		//mAnimation->CompleteEvent(L"AirDash_Stop_Right") = std::bind(&Grimm::Tele_Out, this);
		//
		//mAnimation->CompleteEvent(L"Balloon_Start") = std::bind(&Grimm::Balloon_Loop, this);
		//mAnimation->CompleteEvent(L"Balloon_Loop") = std::bind(&Grimm::Tele_Out, this);
		//
		//mAnimation->CompleteEvent(L"CapSpike_Start") = std::bind(&Grimm::Capspike_Loop, this);
		//mAnimation->CompleteEvent(L"CapSpike_Loop") = std::bind(&Grimm::Capspike_End, this);
		//mAnimation->CompleteEvent(L"CapSpike_End") = std::bind(&Grimm::Tele_Out, this);
		//
		//mAnimation->CompleteEvent(L"Cast_Left") = std::bind(&Grimm::Tele_Out, this);
		//mAnimation->CompleteEvent(L"Cast_Right") = std::bind(&Grimm::Tele_Out, this);
		//
		//mAnimation->CompleteEvent(L"Slash_On_Left") = std::bind(&Grimm::Slash, this);
		//mAnimation->CompleteEvent(L"Slash_On_Right") = std::bind(&Grimm::Slash, this);
		//mAnimation->CompleteEvent(L"Slash_Left") = std::bind(&Grimm::Up_Slash, this);
		//mAnimation->CompleteEvent(L"Slash_Right") = std::bind(&Grimm::Up_Slash, this);
		//mAnimation->CompleteEvent(L"Up_Slash_Left") = std::bind(&Grimm::Tele_Out, this);
		//mAnimation->CompleteEvent(L"Up_Slash_Right") = std::bind(&Grimm::Tele_Out, this);


		mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
		mTransform->SetPosition(Vector3(0.3f, -0.35f, 0.0f));
		//mTransform->SetPosition(Vector3(0.0f, 0.1, 0.0f));
		mCollider->SetSize(Vector2(0.7f, 1.0f));

		//mRigidbody->SetMass(0.0001f);
		//VectorR velocity = mRigidbody->GetVelocity();
		//velocity.y -= 0.1f;
		//mRigidbody->SetVelocity(velocity);
		//mRigidbody->SetGround(false);

		mState = eGrimmState::Idle;
		mPattern_State = ePatternState::Pattern;
		mDirection = eDirection::Left;

		GameObject::Initialize();
	}

	void Grimm::Update()
	{
		if (AirDash_Loop_Move_Check)
		{
			if (Ground_Check == false)
			{
				mGrimmPos = mTransform->GetPosition();
				mGrimmPos.x += Dash_Locate.x * Time::DeltaTime();
				mGrimmPos.y += Dash_Locate.y * Time::DeltaTime();
				mTransform->SetPosition(mGrimmPos);
			}
			else if (Ground_Check)
			{
				AirDash_Land();
			}
		}

		if (AirDash_Attack_Move_Check && mDirection == eDirection::Left)
		{
			AirDash_Attack_Delay += Time::DeltaTime();

			mDr = 0;
			if (AirDash_Attack_Delay > 0.1f)
			{
				mGrimmPos.x -= 2.0f * Time::DeltaTime();
				mTransform->SetPosition(mGrimmPos);
			}
		}
		else if (AirDash_Attack_Move_Check && mDirection == eDirection::Right)
		{
			AirDash_Attack_Delay += Time::DeltaTime();

			mDr = 1;
			if (AirDash_Attack_Delay > 0.1f)
			{
				mGrimmPos.x += 2.0f * Time::DeltaTime();
				mTransform->SetPosition(mGrimmPos);
			}
		}

		if (AirDash_Attack_Delay > 1.0f)
		{
			AirDash_Attack_Delay = 0.0f;
		}

		switch (mPattern_State)
		{
		case km::Grimm::ePatternState::Pattern:
			Pattern();
			break;
		case km::Grimm::ePatternState::DisPattern:
			break;
		default:
			break;
		}

		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mPlayer_Direction = VectorR(mPlayerPos.x, mPlayerPos.y);
		mGrimm_Direction = VectorR(mTransform->GetPosition().x, mTransform->GetPosition().y);
		dr = rigidmath::Direction(mGrimm_Direction, mPlayer_Direction);

		if (dr.x > 0.0f)
		{
			mDirection = eDirection::Right;
		}
		else
		{
			mDirection = eDirection::Left;
		}

		GameObject::Update();
	}

	void Grimm::OnCollisionEnter(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		
		if (gd != nullptr)
		{
			//mRigidbody->SetGround(true);
			Ground_Check = true;
		}
	}
	void Grimm::OnCollisionStay(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		
		if (gd != nullptr)
		{
			//mRigidbody->SetGround(true);
		}
	}
	void Grimm::OnCollisionExit(Collider2D* other)
	{
		GroundScript* gd = dynamic_cast<GroundScript*>(other->GetOwner());
		if (gd != nullptr)
		{
			//mRigidbody->SetGround(false);
		}
	}

	void Grimm::Pattern()
	{
		//Check();

		switch (mState)
		{
		case km::Grimm::eGrimmState::Idle:
			Idle();
			break;
		case km::Grimm::eGrimmState::AirDashOn:
			AirDash_On();
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
		case km::Grimm::eGrimmState::BalloonStart:
			Balloon_Start();
			break;
		case km::Grimm::eGrimmState::BalloonLoop:
			Balloon_Loop();
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
		case km::Grimm::eGrimmState::Cast:
			Cast();
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
		case km::Grimm::eGrimmState::AirDashMove:
			AirDash_Loop_Move();
			break;
		case km::Grimm::eGrimmState::Death:
			Death();
			break;
		case km::Grimm::eGrimmState::End:
			break;
		default:
			break;
		}

		GameObject::Update();
	}
	void Grimm::Idle()
	{
		if (Idle_Check)
		{
			mPattern_State = ePatternState::Pattern;
			mState = eGrimmState::Idle;
			mAnimation->PlayAnimation(L"Idle", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Idle_Check = false;
		}
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
		{
			AirDash_On();
		}
	}

	void Grimm::AirDash_On()
	{
		if (AirDash_On_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack_On", true);
			mTransform->SetPosition(Vector3(-0.25f, 0.0f, 0.0f));
			AirDash_On_Check = false;
		}
	}

	void Grimm::AirDash_Start()
	{
		if (mDirection == eDirection::Left && AirDash_Start_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack1_Left", true);
			AirDash_Start_Check = false;
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.3f, 0.8f));
		}

		if (mDirection == eDirection::Right && AirDash_Start_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack1_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.3f, 0.8f));
			AirDash_Start_Check = false;
		}
	}

	void Grimm::AirDash_Loop()
	{
		if (mDirection == eDirection::Left && AirDash_Loop_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack2_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.1f, 0.8f));
			AirDash_Loop_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Loop_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack2_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.1f, 0.8f));
			AirDash_Loop_Check = false;
		}

	}

	void Grimm::AirDash_Land()
	{
		if (mDirection == eDirection::Left && AirDash_Land_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Lend_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));
			mTransform->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			mGrimmPos = mTransform->GetPosition();

			AirDash_Land_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Land_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Lend_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));
			mTransform->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			mGrimmPos = mTransform->GetPosition();

			AirDash_Land_Check = false;
		}
	}

	void Grimm::AirDash_Attack()
	{
		if (mDirection == eDirection::Left && AirDash_Attack_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			AirDash_Attack_Check = false;
			AirDash_Attack_Move_Check = true;

		}

		if (mDirection == eDirection::Right && AirDash_Attack_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			AirDash_Attack_Check = false;
			AirDash_Attack_Move_Check = true;
		}
	}

	void Grimm::AirDash_Stop()
	{
		if (mDirection == eDirection::Left && AirDash_Stop_Check && mDr == 0)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack_Stop_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));
			AirDash_Stop_Check = false;

			AirDash_Attack_Move_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Stop_Check && mDr == 1)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"AirDash_Attack_Stop_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));
			AirDash_Stop_Check = false;

			AirDash_Attack_Move_Check = false;
		}
	}

	void Grimm::Balloon_Start()
	{
		if (Balloon_Start_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Balloon_Start", true);
			mTransform->SetScale(Vector3(0.4f, 0.4f, 0.0f));
			Balloon_Start_Check = false;
		}
	}

	void Grimm::Balloon_Loop()
	{
		if (Balloon_Loop_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Balloon_Loop", true);
			mTransform->SetScale(Vector3(0.4f, 0.4f, 0.0f));
			Balloon_Loop_Check = false;
		}
	}

	void Grimm::Capspike_On()
	{
		if (Capspike_On_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"CapSpike_Start", true);
			mTransform->SetScale(Vector3(0.35f, 0.4f, 0.0f));
			Capspike_On_Check = false;
		}
	}

	void Grimm::Capspike_Loop()
	{
		if (Capspike_Loop_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"CapSpike_Loop", true);
			mTransform->SetScale(Vector3(0.35f, 0.4f, 0.0f));
			Capspike_Loop_Check = false;
		}
	}

	void Grimm::Capspike_End()
	{
		if (Capspike_End_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"CapSpike_End", true);
			mTransform->SetScale(Vector3(0.35f, 0.4f, 0.0f));
			Capspike_End_Check = false;
		}
	}

	void Grimm::Cast()
	{
		if (mDirection == eDirection::Left && Cast_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Cast_Left", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Cast_Check = false;
		}

		if (mDirection == eDirection::Right && Cast_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Cast_Right", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Cast_Check = false;
		}
	}

	void Grimm::Slash_On()
	{
		if (mDirection == eDirection::Left && Slash_On_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Slash_On_Left", true);
			mTransform->SetScale(Vector3(0.3f, 0.4f, 0.0f));
			Slash_On_Check = false;
		}

		if (mDirection == eDirection::Right && Slash_On_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Slash_On_Right", true);
			mTransform->SetScale(Vector3(0.3f, 0.4f, 0.0f));
			Slash_On_Check = false;
		}
	}

	void Grimm::Slash()
	{
		if (mDirection == eDirection::Left && Slash_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Slash_Left", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Slash_Check = false;
		}

		if (mDirection == eDirection::Right && Slash_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Slash_Right", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Slash_Check = false;
		}
	}

	void Grimm::UP_Slash_Ready()
	{
		if (mDirection == eDirection::Left && AirDash_Stop_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Up_Slash_Ready_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			AirDash_Stop_Check = false;
		}

		if (mDirection == eDirection::Right && AirDash_Stop_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Up_Slash_Ready_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			AirDash_Stop_Check = false;
		}
	}

	void Grimm::Up_Slash()
	{
		if (mDirection == eDirection::Left && Up_Slash_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Up_Slash_Left", true);
			Up_Slash_Check = false;
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
		}

		if (mDirection == eDirection::Right && Up_Slash_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Up_Slash_Right", true);
			Up_Slash_Check = false;
		}
	}

	void Grimm::Tele_In()
	{
		if (Tele_In_Check)
		{
			mPattern_State = ePatternState::Pattern;
			mAnimation->PlayAnimation(L"Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Tele_In_Check = false;
		}
	}

	void Grimm::Tele_Out()
	{
		if (Tele_Out_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Tele_Out", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Tele_Out_Check = false;
		}
	}

	void Grimm::AirDash_Loop_Move()
	{
		if(AirDash_Loop_Move_Check == false)
			Dash_Locate = rigidmath::Direction(mGrimm_Direction, mPlayer_Direction);

		mTransform->SetRotation(Vector3(Dash_Locate.x, Dash_Locate.y, 0.0f));
		AirDash_Loop_Move_Check = true;
	}

	void Grimm::AirDash_Attack_Move()
	{
		AirDash_Attack_Move_Check = true;
	}



	void Grimm::Death()
	{
		if (Death_Check)
		{
			mAnimation->PlayAnimation(L"Death", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Death_Check = false;
		}
	}

	void Grimm::Check()
	{
		Idle_Check           = true;
		AirDash_On_Check     = true;
		AirDash_Start_Check  = true;
		AirDash_Loop_Check   = true;
		AirDash_Land_Check   = true;
		AirDash_Attack_Check = true;
		AirDash_Stop_Check   = true;
		Balloon_Start_Check  = true;
		Balloon_Loop_Check   = true;
		Capspike_On_Check    = true;
		Capspike_Loop_Check  = true;
		Capspike_End_Check   = true;
		Cast_Check           = true;
		Slash_On_Check       = true;
		Slash_Check          = true;
		Up_Slash_Check       = true;
		Tele_In_Check        = true;
		Tele_Out_Check       = true;
		Death_Check          = true;
	}
}