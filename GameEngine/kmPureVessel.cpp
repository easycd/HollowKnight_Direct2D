#include "kmPureVessel.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmRigidbody.h"
#include "kmCollider2D.h"
#include "kmCollisionManager.h"
#include "kmTime.h"

namespace km
{
	PureVessel::PureVessel()
		:IntroStart(0.0f)
		, Intro02_Start(0.0f)
		, Intro03_Start(0.0f)
		, Intro_End(0.0f)
	{
	}
	PureVessel::~PureVessel()
	{
	}

	void PureVessel::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
				
		//Intro Image
		std::shared_ptr<Texture> Intro_Idle = Resources::Load<Texture>(L"Intro_Idle", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_Idle\\Intro_Idle.png");
		std::shared_ptr<Texture> Intro00 = Resources::Load<Texture>(L"Intro00", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_00\\Intro_00.png");
		std::shared_ptr<Texture> Intro01 = Resources::Load<Texture>(L"Intro01", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_01\\Intro_01.png");
		std::shared_ptr<Texture> Intro02 = Resources::Load<Texture>(L"Intro02", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_02\\Intro_02.png");
		std::shared_ptr<Texture> Intro03 = Resources::Load<Texture>(L"Intro03", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_03\\Intro_03.png");
		std::shared_ptr<Texture> Intro04 = Resources::Load<Texture>(L"Intro04", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_04\\Intro_04.png");
		std::shared_ptr<Texture> Intro05 = Resources::Load<Texture>(L"Intro05", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_05\\Intro_05.png");
		std::shared_ptr<Texture> Intro06 = Resources::Load<Texture>(L"Intro06", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_06\\Intro_06.png");

		//Idle Image
		std::shared_ptr<Texture> Idle_Left = Resources::Load<Texture>(L"Idle_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Idle\\Left\\Idle_Left.png");
		std::shared_ptr<Texture> Idle_Right = Resources::Load<Texture>(L"Idle_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Idle\\Right\\Idle_Right.png");

		//Stun Image
		std::shared_ptr<Texture> Stun_00_Left = Resources::Load<Texture>(L"Stun_00_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_00\\Left\\Stun_00_Left.png");
		std::shared_ptr<Texture> Stun_00_Right = Resources::Load<Texture>(L"Stun_00_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_00\\Right\\Stun_00_Right.png");
		std::shared_ptr<Texture> Stun_01_Left = Resources::Load<Texture>(L"Stun_01_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_01\\Left\\Stun_01_Left.png");
		std::shared_ptr<Texture> Stun_01_Right = Resources::Load<Texture>(L"Stun_01_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_01\\Right\\Stun_01_Right.png");

		//Tele_On Image
		std::shared_ptr<Texture> Tele_On_Left = Resources::Load<Texture>(L"Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Tele_On_Right = Resources::Load<Texture>(L"Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");

		//Tele_Out Image
		std::shared_ptr<Texture> Tele_Out_Left = Resources::Load<Texture>(L"Tele_Out_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_Out\\Left\\Tele_Out_Left.png");
		std::shared_ptr<Texture> Tele_Out_Right = Resources::Load<Texture>(L"Tele_Out_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_Out\\Right\\Tele_Out_Right.png");

		//Turn Image
		std::shared_ptr<Texture> Turn_Left = Resources::Load<Texture>(L"Turn_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Turn\\Left\\Turn_Left.png");
		std::shared_ptr<Texture> Turn_Right = Resources::Load<Texture>(L"Turn_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Turn\\Right\\Turn_Right.png");

		//Counter Image
		std::shared_ptr<Texture> Counter_Cast_Left = Resources::Load<Texture>(L"Counter_Cast_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_Cast\\Left\\Counter_Cast_Left.png");
		std::shared_ptr<Texture> Counter_Cast_Right = Resources::Load<Texture>(L"Counter_Cast_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_Cast\\Right\\Counter_Cast_Right.png");
		std::shared_ptr<Texture> Counter_Loop_Left = Resources::Load<Texture>(L"Counter_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_Loop\\Left\\Counter_Loop_Left.png");
		std::shared_ptr<Texture> Counter_Loop_Right = Resources::Load<Texture>(L"Counter_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_Loop\\Right\\Counter_Loop_Right.png");
		std::shared_ptr<Texture> Counter_End_Left = Resources::Load<Texture>(L"Counter_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_End\\Left\\Counter_End_Left.png");
		std::shared_ptr<Texture> Counter_End_Right = Resources::Load<Texture>(L"Counter_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_End\\Right\\Counter_End_Right.png");

		//Dark_Tentacle Image
		std::shared_ptr<Texture> Tentacle_On_Left = Resources::Load<Texture>(L"Tentacle_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\On\\Left\\Dark_Teneacle_On_Left.png");
		std::shared_ptr<Texture> Tentacle_On_Right = Resources::Load<Texture>(L"Tentacle_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\On\\Right\\Dark_Teneacle_On_Right.png");
		std::shared_ptr<Texture> Tentacle_Start_Left = Resources::Load<Texture>(L"Tentacle_Start_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Start\\Left\\Tentacle_Start_Left.png");
		std::shared_ptr<Texture> Tentacle_Start_Right = Resources::Load<Texture>(L"Tentacle_Start_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Start\\Right\\Tentacle_Start_Right.png");
		std::shared_ptr<Texture> Tentacle_Loop_Left = Resources::Load<Texture>(L"Tentacle_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Loop\\Left\\Dark_Teneacle_Loop_Left.png");
		std::shared_ptr<Texture> Tentacle_Loop_Right = Resources::Load<Texture>(L"Tentacle_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Loop\\Right\\Dark_Teneacle_Loop_Right.png");
		std::shared_ptr<Texture> Tentacle_End_Left = Resources::Load<Texture>(L"Tentacle_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\End\\Left\\Dark_Teneacle_End_Left.png");
		std::shared_ptr<Texture> Tentacle_End_Right = Resources::Load<Texture>(L"Tentacle_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\End\\Right\\Dark_Teneacle_End_Right.png");

		//DartShoot Image
		std::shared_ptr<Texture> DartShoot_On_Left = Resources::Load<Texture>(L"DartShoot_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\On\\Left\\"); //아직 이미지 없음
		std::shared_ptr<Texture> DartShoot_On_Right = Resources::Load<Texture>(L"DartShoot_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\On\\Right\\"); //아직 이미지 없음
		std::shared_ptr<Texture> DartShoot_Start_Left = Resources::Load<Texture>(L"DartShoot_Start_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Start\\Left\\Start_Left.png");
		std::shared_ptr<Texture> DartShoot_Start_Right = Resources::Load<Texture>(L"DartShoot_Start_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Start\\Right\\Start_Right.png");
		std::shared_ptr<Texture> DartShoot_Loop_Left = Resources::Load<Texture>(L"DartShoot_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Loop\\Left\\DarkShoot_Loop_Left.png");
		std::shared_ptr<Texture> DartShoot_Loop_Right = Resources::Load<Texture>(L"DartShoot_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Loop\\Right\\DarkShoot_Loop_Right.png");
		std::shared_ptr<Texture> DartShoot_End_Left = Resources::Load<Texture>(L"DartShoot_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\End\\Left\\DarkShoot_End_Left.png");
		std::shared_ptr<Texture> DartShoot_End_Right = Resources::Load<Texture>(L"DartShoot_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\End\\Right\\DarkShoot_End_Right.png");

		//Dash Image
		std::shared_ptr<Texture> Dash_On_Left = Resources::Load<Texture>(L"Dash_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\On\\Left\\Dash_On_Left.png");
		std::shared_ptr<Texture> Dash_On_Right = Resources::Load<Texture>(L"Dash_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\On\\Right\\Dash_On_Right.png");
		std::shared_ptr<Texture> Dash_Shoot_Left = Resources::Load<Texture>(L"Dash_Shoot_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\Shoot\\Left\\Dash_Shoot_Left.png");
		std::shared_ptr<Texture> Dash_Shoot_Right = Resources::Load<Texture>(L"Dash_Shoot_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\Shoot\\Right\\Dash_Shoot_Right.png");
		std::shared_ptr<Texture> Dash_End_Left = Resources::Load<Texture>(L"Dash_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\End\\Left\\Dash_End_Left.png");
		std::shared_ptr<Texture> Dash_End_Right = Resources::Load<Texture>(L"Dash_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\End\\Right\\Dash_End_Right.png");

		//Slash Image
		std::shared_ptr<Texture> Slash_On_Left = Resources::Load<Texture>(L"Slash_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\On\\Left\\Slash_On_Left.png");
		std::shared_ptr<Texture> Slash_On_Right = Resources::Load<Texture>(L"Slash_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\On\\Right\\Slash_On_Right.png");
		std::shared_ptr<Texture> Slash_00_Left = Resources::Load<Texture>(L"Slash_00_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_00\\Left\\Slash_Slash00_Left.png");
		std::shared_ptr<Texture> Slash_00_Right = Resources::Load<Texture>(L"Slash_00_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_00\\Right\\Slash_Slash00_Right.png");
		std::shared_ptr<Texture> Slash_01_Left = Resources::Load<Texture>(L"Slash_01_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_01\\Left\\Slash_Slash01_Left.png");
		std::shared_ptr<Texture> Slash_01_Right = Resources::Load<Texture>(L"Slash_01_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_01\\Right\\Slash_Slash01_Right.png");
		std::shared_ptr<Texture> Slash_02_Left = Resources::Load<Texture>(L"Slash_02_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_02\\Left\\Slash_Slash02_Left.png");
		std::shared_ptr<Texture> Slash_02_Right = Resources::Load<Texture>(L"Slash_02_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_02\\Right\\Slash_Slash02_Right.png");
		std::shared_ptr<Texture> Slash_03_Left = Resources::Load<Texture>(L"Slash_03_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_03\\Left\\Slash_Slash03_Left.png");
		std::shared_ptr<Texture> Slash_03_Right = Resources::Load<Texture>(L"Slash_03_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_03\\Right\\Slash_Slash03_Right.png");
		std::shared_ptr<Texture> Slash_04_Left = Resources::Load<Texture>(L"Slash_04_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_04\\Left\\Slash_Slash04_Left.png");
		std::shared_ptr<Texture> Slash_04_Right = Resources::Load<Texture>(L"Slash_04_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_04\\Right\\Slash_Slash04_Right.png");
		std::shared_ptr<Texture> Slash_05_Left = Resources::Load<Texture>(L"Slash_05_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_05\\Left\\Slash_Slash05_Left.png");
		std::shared_ptr<Texture> Slash_05_Right = Resources::Load<Texture>(L"Slash_05_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_05\\Right\\Slash_Slash05_Right.png");
		std::shared_ptr<Texture> Slash_End_Left = Resources::Load<Texture>(L"Slash_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\End\\Left\\Slash_End_Left.png");
		std::shared_ptr<Texture> Slash_End_Right = Resources::Load<Texture>(L"Slash_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\End\\Right\\Slash_End_Right.png");

		//SpikeAttack Image
		std::shared_ptr<Texture> Spike_On_Left = Resources::Load<Texture>(L"Spike_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\On\\Left\\SpikeAttack_On_Left.png");
		std::shared_ptr<Texture> Spike_On_Right = Resources::Load<Texture>(L"Spike_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\On\\Right\\SpikeAttack_On_Right.png");
		std::shared_ptr<Texture> Spike_Loop_Left = Resources::Load<Texture>(L"Spike_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\Loop\\Left\\SpikeAttack_Loop_Left.png");
		std::shared_ptr<Texture> Spike_Loop_Right = Resources::Load<Texture>(L"Spike_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\Loop\\Right\\SpikeAttack_Loop_Right.png");
		std::shared_ptr<Texture> Spike_End_Left = Resources::Load<Texture>(L"Spike_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\End\\Left\\SpikeAttack_End_Left.png");
		std::shared_ptr<Texture> Spike_End_Right = Resources::Load<Texture>(L"Spike_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\End\\Right\\SpikeAttack_End_Right.png");

		//Intro Animation
		mAnimation->Create(L"Intro_Idle", Intro_Idle, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro00", Intro00, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro01", Intro01, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro02", Intro02, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 3, Vector2(0.06f, 0.02f), 0.07f);
		mAnimation->Create(L"Intro03", Intro03, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro04", Intro04, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 12, Vector2(0.02f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro05", Intro05, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.06f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro06", Intro06, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.06f, 0.02f), 0.1f);

		//Idle Animation
		mAnimation->Create(L"Idle_Left", Idle_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Idle_Right", Idle_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);


		//Stun Animation
		mAnimation->Create(L"Stun_00_Left", Stun_00_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Stun_00_Right", Stun_00_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Stun_01_Left", Stun_01_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Stun_01_Right", Stun_01_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);

		//Tele_On Animation
		mAnimation->Create(L"Tele_On_Left", Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tele_On_Right", Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		 
		//Tele_Out Animation
		mAnimation->Create(L"Tele_Out_Left", Tele_Out_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tele_Out_Right", Tele_Out_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);

		//Turn Animation
		mAnimation->Create(L"Turn_Left", Turn_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Turn_Right", Turn_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);

		//Counter Animation
		mAnimation->Create(L"Counter_Cast_Left", Counter_Cast_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_Cast_Right", Counter_Cast_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_Loop_Left", Counter_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_Loop_Right", Counter_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_End_Left", Counter_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_End_Right", Counter_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);

		//Dark_Tentacle Animation
		mAnimation->Create(L"Tentacle_On_Left", Tentacle_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_On_Right", Tentacle_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Start_Left", Tentacle_Start_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Start_Right", Tentacle_Start_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Loop_Left", Tentacle_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Loop_Right", Tentacle_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_End_Left", Tentacle_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		//DartShoot Animation
		mAnimation->Create(L"DartShoot_On_Left", DartShoot_On_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_On_Right", DartShoot_On_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Start_Left", DartShoot_Start_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Start_Right", DartShoot_Start_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Loop_Left", DartShoot_Loop_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Loop_Right", DartShoot_Loop_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_End_Left", DartShoot_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_End_Right", DartShoot_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);

		//Dash Animation
		mAnimation->Create(L"Dash_On_Left", Dash_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_On_Right", Dash_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_Shoot_Left", Dash_Shoot_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_Shoot_Right", Dash_Shoot_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_End_Left", Dash_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_End_Right", Dash_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		//Slash Animation
		mAnimation->Create(L"Slash_On_Left", Slash_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 8, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_On_Right", Slash_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 8, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_00_Left", Slash_00_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_00_Right", Slash_00_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_01_Left", Slash_01_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_01_Right", Slash_01_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_02_Left", Slash_02_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_02_Right", Slash_02_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_03_Left", Slash_03_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_03_Right", Slash_03_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_04_Left", Slash_04_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_04_Right", Slash_04_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_05_Left", Slash_05_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_05_Right", Slash_05_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_End_Left", Slash_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_End_Right", Slash_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		//SpikeAttack Animation
		mAnimation->Create(L"Spike_On_Left", Spike_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_On_Right", Spike_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Loop_Left", Spike_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Loop_Right", Spike_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_End_Left", Spike_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_End_Right", Spike_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);





		mAnimation->CompleteEvent(L"Intro00") = std::bind(&PureVessel::Intro_01, this);
		mAnimation->CompleteEvent(L"Intro03") = std::bind(&PureVessel::Intro_04, this);
		mAnimation->CompleteEvent(L"Intro04") = std::bind(&PureVessel::Intro_05, this);
		mAnimation->CompleteEvent(L"Intro05") = std::bind(&PureVessel::Intro_06, this);


		mTransform->SetScale(Vector3(0.55f, 0.62f, 0.0f));
		mTransform->SetPosition(Vector3(0.4f, -0.15f, 0.0f));
		//mCollider->SetSize(Vector2(0.6f, 0.6f));
		GameObject::Initialize();
	}
	void PureVessel::Update()
	{
		IntroStart += Time::DeltaTime();
		if (IntroStart > 2.0f && IntroStart_Check)
		{
			IntroStart_Check = false;
			Intro_00();
		}

		if (Intro_02_Start_Check)
		{		
			Intro02_Start += Time::DeltaTime();
			if (Intro02_Start > 2.0f)
			{
				Intro_02_Start_Check = false;
				Intro_02();
			}
		}
		if (Intro_03_Start_Check)
		{
			Intro03_Start += Time::DeltaTime();
		
			if (Intro03_Start > 3.0f)
			{
				Intro_03_Start_Check = false;
				Intro_03();
			}
		}

		if (Intro_End_Check)
		{
			Intro_End += Time::DeltaTime();
			if (Intro_End > 3.0f)
			{
				Intro_End_Check = false;
				Idle();
			}
		}

		GameObject::Update();
	}

	void PureVessel::OnCollisionEnter(Collider2D* other)
	{
	}

	void PureVessel::OnCollisionStay(Collider2D* other)
	{
	}

	void PureVessel::OnCollisionExit(Collider2D* other)
	{
	}

	void PureVessel::Intro_Idle()
	{
		mAnimation->PlayAnimation(L"Intro_Idle", true);
	}

	void PureVessel::Intro_00()
	{
		mAnimation->PlayAnimation(L"Intro00", true);
	}

	void PureVessel::Intro_01()
	{
		mAnimation->PlayAnimation(L"Intro01", true);
		Intro_02_Start_Check = true;
	}

	void PureVessel::Intro_02()
	{
		mAnimation->PlayAnimation(L"Intro02", true);
		Intro_03_Start_Check = true;
	}

	void PureVessel::Intro_03()
	{
		mAnimation->PlayAnimation(L"Intro03", true);
	}

	void PureVessel::Intro_04()
	{
		mTransform->SetScale(Vector3(0.8f, 1.0f, 0.0f));
		mTransform->SetPosition(Vector3(0.4f, -0.09f, 0.0f));
		mAnimation->PlayAnimation(L"Intro04", true);
	}

	void PureVessel::Intro_05()
	{
		mAnimation->PlayAnimation(L"Intro05", true);
	}

	void PureVessel::Intro_06()
	{
		mAnimation->PlayAnimation(L"Intro06", true);
		Intro_End_Check = true;
	}

	void PureVessel::Pattern()
	{
	}

	void PureVessel::Idle()
	{
		mAnimation->PlayAnimation(L"Idle_Left", true);
	}

	void PureVessel::Counter()
	{
	}

	void PureVessel::Dash()
	{
	}

	void PureVessel::Knife_Spike()
	{
	}

	void PureVessel::Slash()
	{
	}

	void PureVessel::Knife_Spread()
	{
	}

	void PureVessel::Groggy()
	{
	}

	void PureVessel::Circle_Attack()
	{
	}

	void PureVessel::Dark_tentacle()
	{
	}

}