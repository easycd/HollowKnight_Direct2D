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

//Object
#include "kmSpike_Object.h"
#include "kmFlameBat.h"

namespace km
{
	Grimm::Grimm()
		: mTime(0.0f)
		, AirDash_Attack_Delay(0.0f)
		, Balloon_Loop_Delay(0.0f)
		, CapSpike_Loop_Delay(0.0f)
		, Cast_Loop_Delay(0.0f)
		, Slash_On_Delay(0.0f)
		, Pattern_Delay(0.0f)
		, Cast_Delay(0.0f)
		, AirDash_On_Location(0)
		, FlameBat_Delay(0.0f)



		, attack_pattern(0)

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
		std::shared_ptr<Texture> AirDash_Tele_In = Resources::Load<Texture>(L"AirDash_Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOn\\Tele_In.png");
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
		std::shared_ptr<Texture> Balloon_Tele_In = Resources::Load<Texture>(L"Balloon_Tele_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Teleport\\Grimm_TeleOn\\Tele_In.png");
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
		std::shared_ptr<Texture> AirDash_Stop_Left = Resources::Load<Texture>(L"Up_Slash_Ready_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\3_Stop\\Left\\AirDash_Stop_Left.png");
		std::shared_ptr<Texture> AirDash_Stop_Right = Resources::Load<Texture>(L"Up_Slash_Ready_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\AirDash\\Dash\\3_Stop\\Right\\AirDash_Stop_Right.png");
		std::shared_ptr<Texture> Up_Slash_Left = Resources::Load<Texture>(L"Up_Slash_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack\\Left\\Up_Slash_Left.png");
		std::shared_ptr<Texture> Up_Slash_Right = Resources::Load<Texture>(L"Up_Slash_Right", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Pattern\\Attack\\Slash\\Up_Attack\\Right\\Up_Slash_Right.png");

		mAnimation->Create(L"Idle", Idle, Vector2(0.0f, 0.0f), Vector2(264.0f, 441.0f), 12, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Death", Death, Vector2(0.0f, 0.0f), Vector2(489.0f, 525.0f), 3, Vector2(0.0f, 0.02f), 0.15f);
		mAnimation->Create(L"Tele_Out", Tele_Out, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6, Vector2(0.0f, 0.02f), 0.05f);
		mAnimation->Create(L"Tele_In", Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.05f);

		mAnimation->Create(L"AirDash_Tele_In", AirDash_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.05f);
		mAnimation->Create(L"AirDash_Attack_On", AirDash_Attack_On, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 6, Vector2(0.0f, 0.02f), 0.05f);
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

		mAnimation->Create(L"Balloon_Tele_In", Balloon_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Balloon_Start", Balloon_Start, Vector2(0.0f, 0.0f), Vector2(521.0f, 576.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Balloon_Loop", Balloon_Loop, Vector2(0.0f, 0.0f), Vector2(521.0f, 576.0f), 3, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->Create(L"CapSpike_Tele_In", CapSpike_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"CapSpike_Start", CapSpike_Start, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 10, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"CapSpike_Loop", CapSpike_Loop, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"CapSpike_End", CapSpike_End, Vector2(0.0f, 0.0f), Vector2(394.0f, 445.0f), 7, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->Create(L"Cast_Tele_In", Cast_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Cast_Left", Cast_Left, Vector2(0.0f, 0.0f), Vector2(546.0f, 444.0f), 8, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Cast_Right", Cast_Right, Vector2(0.0f, 0.0f), Vector2(546.0f, 444.0f), 8, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->Create(L"Slash_Tele_In", Slash_Tele_In, Vector2(0.0f, 0.0f), Vector2(315.0f, 444.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_On_Left", Slash_On_Left, Vector2(0.0f, 0.0f), Vector2(342.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_On_Right", Slash_On_Right, Vector2(0.0f, 0.0f), Vector2(342.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_Left", Slash_Left, Vector2(0.0f, 0.0f), Vector2(792.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_Right", Slash_Right, Vector2(0.0f, 0.0f), Vector2(792.0f, 438.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Up_Slash_Ready_Left", AirDash_Stop_Left, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 3, Vector2(0.0f, -0.02f), 0.12f);
		mAnimation->Create(L"Up_Slash_Ready_Right", AirDash_Stop_Right, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 3, Vector2(0.0f, -0.02f), 0.12f);
		mAnimation->Create(L"Up_Slash_Left", Up_Slash_Left, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Up_Slash_Right", Up_Slash_Right, Vector2(0.0f, 0.0f), Vector2(662.0f, 786.0f), 4, Vector2(0.0f, 0.02f), 0.1f);


		//mAnimation->CompleteEvent(L"AirDash_Tele_In") = std::bind(&Grimm::AirDash_On, this);
		mAnimation->CompleteEvent(L"AirDash_Attack_On") = std::bind(&Grimm::AirDash_Start, this);
		mAnimation->CompleteEvent(L"AirDash_Attack1_Left") = std::bind(&Grimm::AirDash_Loop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack1_Right") = std::bind(&Grimm::AirDash_Loop, this);
		mAnimation->CompleteEvent(L"AirDash_Attack2_Left") = std::bind(&Grimm::AirDash_Loop_Move, this);
		mAnimation->CompleteEvent(L"AirDash_Attack2_Right") = std::bind(&Grimm::AirDash_Loop_Move, this);
		mAnimation->CompleteEvent(L"AirDash_Lend_Left") = std::bind(&Grimm::AirDash_Attack, this);
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

		mAnimation->CompleteEvent(L"Tele_Out") = std::bind(&Grimm::Tele_Out_State, this);

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
		mPattern_State = ePatternState::DisPattern;
		mDirection = eDirection::Left;

		GameObject::Initialize();
	}

	void Grimm::Update()
	{
		//실시간 그림 위치 받아옴
		mGrimm_Live_Pos = mTransform->GetPosition();


		//에어대쉬 방향회전 및 돌진
		if (AirDash_Loop_Move_Check)
		{
			if (Ground_Check == false)
			{
				mGrimm_Live_Pos = mTransform->GetPosition();
				mGrimm_Live_Pos.x += Dash_Locate.x * Time::DeltaTime() * 1.8f;
				mGrimm_Live_Pos.y += Dash_Locate.y * Time::DeltaTime() * 1.8f;
				//mTransform->SetPosition(mGrimm_Live_Pos);
			}
			else if (Ground_Check)
			{
				AirDash_Loop_Move_Check = false;
				AirDash_Land();
			}
		}

		//땅에서 돌진할때 체크
		if (AirDash_Attack_Move_Check && mGetDirection == eDirection::Left)
		{
			AirDash_Attack_Delay += Time::DeltaTime();

			if(mGrimm_Live_Pos.x > -1.13f)
			mGrimm_Live_Pos.x -= 2.5f * Time::DeltaTime();
		}
		else if (AirDash_Attack_Move_Check && mGetDirection == eDirection::Right)
		{
			AirDash_Attack_Delay += Time::DeltaTime();

			if (mGrimm_Live_Pos.x < 0.94f)
			mGrimm_Live_Pos.x += 2.5f * Time::DeltaTime();
		}
		mTransform->SetPosition(mGrimm_Live_Pos);

		if (AirDash_Attack_Delay > 0.5f)
		{
			AirDash_Attack_Delay = 0.0f;
			AirDash_Attack_Move_Check = false;
		}

		//Balloon 패턴 지속시간 체크
		if (Balloon_Loop_Delay_Check)
		{
			Balloon_Loop_Delay += Time::DeltaTime();

			if (Balloon_Loop_Delay > 5.0f)
			{
				Balloon_Loop_Delay = 0.0f;
				Tele_Out();
			}
		}


		//CapSpike 패턴 오브젝트 생성 및 소멸
		if (CapSpike_Loop_Delay_Check)
		{
			CapSpike_Loop_Delay += Time::DeltaTime();

			if (Spike_Object_Check)
			{
				Spike_Obj();
			}

			if (CapSpike_Loop_Delay > 6.0f)
			{
				CapSpike_Loop_Delay = 0.0f;

				Capspike_End();
			}
		}

		//Slash 패턴 하기 전 딜레이
		if (Slash_On_Delay_Check)
		{
			Slash_On_Delay += Time::DeltaTime();

			if (Slash_On_Delay > 1.0f)
			{
				Slash_On_Delay = 0.0f;
				Slash();
			}
		}

		//Cast 패턴 유지시간 체크
		if (Cast_Delay_Check)
		{
			Cast_Delay += Time::DeltaTime();

			if (Cast_Delay > 5.0f)
			{
				Cast_Delay = 0.0;
				Tele_Out();
			}
		}

		//Cast 패턴 중 FlameBat 생성타이밍 체크
		if (FlameBat_Obj_Play)
		{
			FlameBat_Delay += Time::DeltaTime();

			if (Bat0_Play && FlameBat_Delay > 1.0f)
			{
				Bat0 = object::Instantiate<FlameBat>(eLayerType::BossObj);
				Bat0->On();
				if (mGetDirection == eDirection::Left)
				{
					Bat0->SetDirection(0);
				}
				if (mGetDirection == eDirection::Right)
				{
					Bat0->SetDirection(1);
				}

				Bat0_Play = false;
				Bat1_Play = true;
			}

			if (Bat1_Play && FlameBat_Delay > 2.0f)
			{
				Bat1 = object::Instantiate<FlameBat>(eLayerType::BossObj);
				Bat1->On();
				if (mGetDirection == eDirection::Left)
				{
					Bat1->SetDirection(0);
				}
				if (mGetDirection == eDirection::Right)
				{
					Bat1->SetDirection(1);
				}

				Bat1_Play = false;
				Bat2_Play = true;
			}

			if (Bat2_Play && FlameBat_Delay > 3.0f)
			{
				Bat2 = object::Instantiate<FlameBat>(eLayerType::BossObj);
				Bat2->On();
				if (mGetDirection == eDirection::Left)
				{
					Bat2->SetDirection(0);
				}
				if (mGetDirection == eDirection::Right)
				{
					Bat2->SetDirection(1);
				}

				Bat2_Play = false;
				FlameBat_Delay = 0.0f;
			}
		}

		//Slash 패턴 돌진 방향 및 위치이동
		if (Slash_Move_Check && mDirection == eDirection::Left)
		{
			mGetGimmPos.x -= 2.0f * Time::DeltaTime();
			mTransform->SetPosition(mGetGimmPos);
		}
		else if (Slash_Move_Check && mDirection == eDirection::Right)
		{
			mGetGimmPos.x += 2.0f * Time::DeltaTime();
			mTransform->SetPosition(mGetGimmPos);
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

		if (mPlayerPos.x > -1.26f && Pattern_Start == false)
		{
			mTime += Time::DeltaTime();
			if (mTime > 3.0f)
			{
				Pattern_Start = true;
				Tele_Out();
			}
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
			Ground_Check = false;
		}
	}

	void Grimm::Pattern()
	{
			switch (attack_pattern)
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
			}
	}
	void Grimm::Idle()
	{
		if (Idle_Check)
		{
			mAnimation->PlayAnimation(L"Idle", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Idle_Check = false;
		}
		mTime += Time::DeltaTime();
		if (mTime > 3.0f)
			Pattern();
	}

	void Grimm::AirDash_Tele_In()
	{
		if (AirDash_Tele_In_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_On", true);
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

	//void Grimm::AirDash_On()
	//{
	//	if (AirDash_On_Check)
	//	{
	//		mPattern_State = ePatternState::DisPattern;
	//		mAnimation->PlayAnimation(L"AirDash_Attack_On", true);
	//		AirDash_On_Check = false;
	//	}
	//}

	void Grimm::AirDash_Start()
	{
		if (AirDash_Start_Check)
			mGetDirection = mDirection;

		if (mGetDirection == eDirection::Left && AirDash_Start_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack1_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.3f, 0.8f));

			AirDash_Start_Check = false;
		}

		if (mGetDirection == eDirection::Right && AirDash_Start_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack1_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.3f, 0.8f));

			AirDash_Start_Check = false;
		}
	}

	void Grimm::AirDash_Loop()
	{
		if (mGetDirection == eDirection::Left && AirDash_Loop_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack2_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.1f, 0.8f));

			AirDash_Loop_Check = false;
		}

		if (mGetDirection == eDirection::Right && AirDash_Loop_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack2_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.1f, 0.8f));

			AirDash_Loop_Check = false;
		}
	}

	void Grimm::AirDash_Land()
	{
		if (mGetDirection == eDirection::Left && AirDash_Land_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Lend_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));
			mTransform->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			mTransform->SetPosition(Vector3(mGrimm_Live_Pos.x, -0.45f, 0.0f));
			mGrimmPos = mTransform->GetPosition();

			AirDash_Land_Check = false;
		}

		if (mGetDirection == eDirection::Right && AirDash_Land_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Lend_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));
			mTransform->SetRotation(Vector3(0.0f, 0.0f, 0.0f));
			mTransform->SetPosition(Vector3(mGrimm_Live_Pos.x, -0.45f, 0.0f));
			mGrimmPos = mTransform->GetPosition();

			AirDash_Land_Check = false;
		}
	}

	void Grimm::AirDash_Attack()
	{
		if (mGetDirection == eDirection::Left && AirDash_Attack_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			//mGetGimmPos = mGrimm_Live_Pos;

			AirDash_Attack_Check = false;
			AirDash_Attack_Move_Check = true;
		}

		if (mGetDirection == eDirection::Right && AirDash_Attack_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			//mGetGimmPos = mGrimm_Live_Pos;

			AirDash_Attack_Check = false;
			AirDash_Attack_Move_Check = true;
		}
	}

	void Grimm::AirDash_Stop()
	{
		if (mGetDirection == eDirection::Left && AirDash_Stop_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_Stop_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));

			AirDash_Stop_Check = false;
		}

		if (mGetDirection == eDirection::Right && AirDash_Stop_Check)
		{
			mAnimation->PlayAnimation(L"AirDash_Attack_Stop_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mCollider->SetSize(Vector2(0.4f, 0.5f));

			AirDash_Stop_Check = false;
		}
	}

	void Grimm::Balloon_Tele_In()
	{
		if (Balloon_Tele_In_Check)
		{
			mPattern_State = ePatternState::Pattern;
			mAnimation->PlayAnimation(L"Balloon_Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			mTransform->SetPosition(Vector3(-0.25f, -0.1f, 0.0f));
			Balloon_Tele_In_Check = false;
		}
	}

	void Grimm::Balloon_Start()
	{
		if (Balloon_Start_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Balloon_Start", true);
			mTransform->SetScale(Vector3(0.45f, 0.45f, 0.0f));
			mTransform->SetPosition(Vector3(-0.25f, -0.1f, 0.0f));
			Balloon_Start_Check = false;
		}
	}

	void Grimm::Balloon_Loop()
	{
		if (Balloon_Loop_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Balloon_Loop", true);
			mTransform->SetScale(Vector3(0.45f, 0.45f, 0.0f));
			mTransform->SetPosition(Vector3(-0.25f, -0.1f, 0.0f));
			Balloon_Loop_Delay_Check = true;
			Balloon_Loop_Check = false;
		}
	}

	void Grimm::Capspike_Tele_In()
	{
		if (Capspike_Tele_In_Check)
		{
			mPattern_State = ePatternState::Pattern;
			mAnimation->PlayAnimation(L"CapSpike_Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			mTransform->SetPosition(Vector3(0.35f, -0.35f, 0.0f));
			Capspike_Tele_In_Check = false;
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
			CapSpike_Loop_Delay_Check = true;
			Capspike_Loop_Check = false;

			Spike_Object_Check = true;
		}
	}

	void Grimm::Capspike_End()
	{
		if (Capspike_End_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"CapSpike_End", true);
			mTransform->SetScale(Vector3(0.35f, 0.4f, 0.0f));
			CapSpike_Loop_Delay_Check = false;
			Capspike_End_Check = false;
		}
	}

	void Grimm::Cast_Tele_In()
	{
		if (Cast_Tele_In_Check)
		{
			mPattern_State = ePatternState::Pattern;
			mAnimation->PlayAnimation(L"Cast_Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Cast_Tele_In_Check = false;
		}
	}

	void Grimm::Cast()
	{
		if (Cast_Check)
			mGetDirection = mDirection;

		if (mGetDirection == eDirection::Left && Cast_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Cast_Left", false);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			mTransform->SetPosition(Vector3(0.46f, -0.35f, 0.0f));
			FlameBat_Obj_Play = true;
			Cast_Delay_Check = true;
			Cast_Check = false;
			Bat0_Play = true;
		}

		if (mGetDirection == eDirection::Right && Cast_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Cast_Right", false);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			mTransform->SetPosition(Vector3(-0.72f, -0.35f, 0.0f));
			FlameBat_Obj_Play = true;
			Cast_Delay_Check = true;
			Cast_Check = false;
			Bat0_Play = true;
		}
	}

	void Grimm::Slash_Tele_In()
	{
		if (Slash_On_Check)
			mGetDirection = mDirection;

		if (Slash_Tele_In_Check)
		{
			mPattern_State = ePatternState::Pattern;
			mAnimation->PlayAnimation(L"Slash_Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Slash_Tele_In_Check = false;

			if (mGetDirection == eDirection::Left)
				mTransform->SetPosition(Vector3(mPlayerPos.x + 0.5, -0.35f, 0.0f));

			if (mGetDirection == eDirection::Right)
				mTransform->SetPosition(Vector3(mPlayerPos.x - 0.5, -0.35f, 0.0f));
		}
	}

	void Grimm::Slash_On()
	{
		if (mGetDirection == eDirection::Left && Slash_On_Check)
		{
			mGetPlayerPos = mPlayerPos;
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Slash_On_Left", false);
			mTransform->SetScale(Vector3(0.3f, 0.4f, 0.0f));
			Slash_On_Delay_Check = true;
			Slash_On_Check = false;
			mGetGimmPos = mGrimm_Live_Pos;
		}

		if (mGetDirection == eDirection::Right && Slash_On_Check)
		{
			mGetPlayerPos = mPlayerPos;
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Slash_On_Right", false);
			mTransform->SetScale(Vector3(0.3f, 0.4f, 0.0f));
			Slash_On_Delay_Check = true;
			Slash_On_Check = false;
			mGetGimmPos = mGrimm_Live_Pos;
		}
	}

	void Grimm::Slash()
	{
		if (mGetDirection == eDirection::Left && Slash_Check)
		{
			Slash_On_Delay_Check = false;
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Slash_Left", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Slash_Check = false;
			Slash_Move_Check = true;
		}

		if (mGetDirection == eDirection::Right && Slash_Check)
		{
			Slash_On_Delay_Check = false;
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Slash_Right", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Slash_Check = false;
			Slash_Move_Check = true;
		}
	}

	void Grimm::UP_Slash_Ready()
	{
		Slash_Move_Check = false;

		if (mGetDirection == eDirection::Left && AirDash_Stop_Check)
		{
			mAnimation->PlayAnimation(L"Up_Slash_Ready_Left", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mTransform->SetPosition(Vector3(mGrimm_Live_Pos.x, -0.4f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			AirDash_Stop_Check = false;
		}

		if (mGetDirection == eDirection::Right && AirDash_Stop_Check)
		{

			mAnimation->PlayAnimation(L"Up_Slash_Ready_Right", true);
			mTransform->SetScale(Vector3(0.6f, 0.5f, 0.0f));
			mTransform->SetPosition(Vector3(mGrimm_Live_Pos.x, -0.4f, 0.0f));
			mCollider->SetSize(Vector2(0.7f, 0.5f));
			AirDash_Stop_Check = false;
		}
	}

	void Grimm::Up_Slash()
	{
		if (mGetDirection == eDirection::Left && Up_Slash_Check)
		{
			mAnimation->PlayAnimation(L"Up_Slash_Left", true);
			mTransform->SetScale(Vector3(0.5f, 0.6f, 0.0f));
			Up_Slash_Check = false;
		}

		if (mGetDirection == eDirection::Right && Up_Slash_Check)
		{
			mAnimation->PlayAnimation(L"Up_Slash_Right", true);
			mTransform->SetScale(Vector3(0.5f, 0.6f, 0.0f));
			Up_Slash_Check = false;
		}
	}

	void Grimm::Tele_In()
	{
		if (Tele_In_Check)
		{
			mAnimation->PlayAnimation(L"Tele_In", true);
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Tele_In_Check = false;
		}
	}

	void Grimm::Tele_In_State()
	{
		Check();
		Pattern();
	}

	void Grimm::Tele_Out()
	{
		Balloon_Loop_Delay_Check = false;
		if (Tele_Out_Check)
		{
			mPattern_State = ePatternState::DisPattern;
			mAnimation->PlayAnimation(L"Tele_Out", true);
			if (mGrimm_Live_Pos.y < -0.2)
			{
				mTransform->SetPosition(Vector3(mGrimm_Live_Pos.x, -0.37f, 0.0f));
			}
			mTransform->SetScale(Vector3(0.25f, 0.4f, 0.0f));
			Tele_Out_Check = false;
		}
	}

	void Grimm::Tele_Out_State()
	{
		mTransform->SetPosition(Vector3(100.0f, 0.0f, 0.0f));
		Tele_In_State();
	}

	void Grimm::AirDash_Loop_Move()
	{
		if (AirDash_Loop_Move_Check == false)
		{
			Dash_Locate = rigidmath::Direction(mGrimm_Direction, mPlayer_Direction);
			mTransform->SetRotation(Vector3(Dash_Locate.x, Dash_Locate.y, 0.0f));

			AirDash_Loop_Move_Check = true;
		}
	}

	void Grimm::Death()
	{
		mPattern_State = ePatternState::DisPattern;
		if (Death_Check)
		{
			mAnimation->PlayAnimation(L"Death", true);
			mTransform->SetScale(Vector3(0.5f, 0.4f, 0.0f));
			Death_Check = false;
		}
	}

	void Grimm::Check()
	{
		Idle_Check = true;
		AirDash_On_Check = true;
		AirDash_Start_Check = true;
		AirDash_Loop_Check = true;
		AirDash_Land_Check = true;
		AirDash_Attack_Check = true;
		AirDash_Stop_Check = true;
		Balloon_Start_Check = true;
		Balloon_Loop_Check = true;
		Capspike_On_Check = true;
		Capspike_Loop_Check = true;
		Capspike_End_Check = true;
		Cast_Check = true;
		Slash_On_Check = true;
		Slash_Check = true;
		Up_Slash_Check = true;
		Tele_In_Check = true;
		Tele_Out_Check = true;
		Death_Check = true;
		AirDash_Tele_In_Check = true;
		Balloon_Tele_In_Check = true;
		Capspike_Tele_In_Check = true;
		Cast_Tele_In_Check = true;
		Slash_Tele_In_Check = true;
	}

	void Grimm::Spike_Obj()
	{
		Spike_Object_Check = false;

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
}