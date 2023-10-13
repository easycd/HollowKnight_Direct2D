#include "kmPureVessel.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmRigidbody.h"
#include "kmCollider2D.h"
#include "kmCollisionManager.h"
#include "kmTime.h"
#include "kmSceneManager.h"
#include "kmPlayer.h"

namespace km
{
	PureVessel::PureVessel()
		: Pattern_Timing(0.0f)
		, Intro_Idle_Timing(0.0f)
		, Intro01_Timing(0.0f)
		, Intro02_Timing(0.0f)
		, Intro06_Timing(0.0f)
		, Dash_On_Timing(0.0f)
		, mPattern(1)

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
		std::shared_ptr<Texture> Intro_End = Resources::Load<Texture>(L"Intro_End", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_End\\Intro_End.png");

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
		std::shared_ptr<Texture> Tentacle_Tele_On_Left = Resources::Load<Texture>(L"Tentacle_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Tentacle_Tele_On_Right = Resources::Load<Texture>(L"Tentacle_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> Tentacle_On_Left = Resources::Load<Texture>(L"Tentacle_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\On\\Left\\Dark_Teneacle_On_Left.png");
		std::shared_ptr<Texture> Tentacle_On_Right = Resources::Load<Texture>(L"Tentacle_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\On\\Right\\Dark_Teneacle_On_Right.png");
		std::shared_ptr<Texture> Tentacle_Start_Left = Resources::Load<Texture>(L"Tentacle_Start_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Start\\Left\\Tentacle_Start_Left.png");
		std::shared_ptr<Texture> Tentacle_Start_Right = Resources::Load<Texture>(L"Tentacle_Start_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Start\\Right\\Tentacle_Start_Right.png");
		std::shared_ptr<Texture> Tentacle_Loop_Left = Resources::Load<Texture>(L"Tentacle_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Loop\\Left\\Dark_Teneacle_Loop_Left.png");
		std::shared_ptr<Texture> Tentacle_Loop_Right = Resources::Load<Texture>(L"Tentacle_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Loop\\Right\\Dark_Teneacle_Loop_Right.png");
		std::shared_ptr<Texture> Tentacle_End_Left = Resources::Load<Texture>(L"Tentacle_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\End\\Left\\Dark_Teneacle_End_Left.png");
		std::shared_ptr<Texture> Tentacle_End_Right = Resources::Load<Texture>(L"Tentacle_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\End\\Right\\Dark_Teneacle_End_Right.png");

		//DartShoot Image
		std::shared_ptr<Texture> DartShoot_Tele_On_Left = Resources::Load<Texture>(L"DartShoot_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> DartShoot_Tele_On_Right = Resources::Load<Texture>(L"DartShoot_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> DartShoot_On_Left = Resources::Load<Texture>(L"DartShoot_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\On\\Left\\"); //아직 이미지 없음
		std::shared_ptr<Texture> DartShoot_On_Right = Resources::Load<Texture>(L"DartShoot_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\On\\Right\\"); //아직 이미지 없음
		std::shared_ptr<Texture> DartShoot_Start_Left = Resources::Load<Texture>(L"DartShoot_Start_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Start\\Left\\Start_Left.png");
		std::shared_ptr<Texture> DartShoot_Start_Right = Resources::Load<Texture>(L"DartShoot_Start_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Start\\Right\\Start_Right.png");
		std::shared_ptr<Texture> DartShoot_Loop_Left = Resources::Load<Texture>(L"DartShoot_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Loop\\Left\\DarkShoot_Loop_Left.png");
		std::shared_ptr<Texture> DartShoot_Loop_Right = Resources::Load<Texture>(L"DartShoot_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Loop\\Right\\DarkShoot_Loop_Right.png");
		std::shared_ptr<Texture> DartShoot_End_Left = Resources::Load<Texture>(L"DartShoot_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\End\\Left\\DarkShoot_End_Left.png");
		std::shared_ptr<Texture> DartShoot_End_Right = Resources::Load<Texture>(L"DartShoot_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\End\\Right\\DarkShoot_End_Right.png");

		//Dash Image
		std::shared_ptr<Texture> Dash_Tele_On_Left = Resources::Load<Texture>(L"Dash_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Dash_Tele_On_Right = Resources::Load<Texture>(L"Dash_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> Dash_On_Left = Resources::Load<Texture>(L"Dash_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\On\\Left\\Dash_On_Left.png");
		std::shared_ptr<Texture> Dash_On_Right = Resources::Load<Texture>(L"Dash_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\On\\Right\\Dash_On_Right.png");
		std::shared_ptr<Texture> Dash_Shoot_Left = Resources::Load<Texture>(L"Dash_Shoot_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\Shoot\\Left\\Dash_Shoot_Left.png");
		std::shared_ptr<Texture> Dash_Shoot_Right = Resources::Load<Texture>(L"Dash_Shoot_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\Shoot\\Right\\Dash_Shoot_Right.png");
		std::shared_ptr<Texture> Dash_End_Left = Resources::Load<Texture>(L"Dash_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\End\\Left\\Dash_End_Left.png");
		std::shared_ptr<Texture> Dash_End_Right = Resources::Load<Texture>(L"Dash_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\End\\Right\\Dash_End_Right.png");

		//Slash Image
		std::shared_ptr<Texture> Slash_Tele_On_Left = Resources::Load<Texture>(L"Slash_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Slash_Tele_On_Right = Resources::Load<Texture>(L"Slash_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
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
		std::shared_ptr<Texture> Spike_Tele_On_Left = Resources::Load<Texture>(L"Spike_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Spike_Tele_On_Right = Resources::Load<Texture>(L"Spike_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
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
		mAnimation->Create(L"Intro_End", Intro_End, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.06f, 0.02f), 0.1f);

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
		mAnimation->Create(L"Tentacle_Tele_On_Left", Tentacle_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Tele_On_Right", Tentacle_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_On_Left", Tentacle_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_On_Right", Tentacle_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Start_Left", Tentacle_Start_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Start_Right", Tentacle_Start_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Loop_Left", Tentacle_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Loop_Right", Tentacle_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_End_Left", Tentacle_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		//DartShoot Animation
		mAnimation->Create(L"DartShoot_Tele_On_Left", DartShoot_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Tele_On_Right", DartShoot_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_On_Left", DartShoot_On_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_On_Right", DartShoot_On_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Start_Left", DartShoot_Start_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Start_Right", DartShoot_Start_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Loop_Left", DartShoot_Loop_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Loop_Right", DartShoot_Loop_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_End_Left", DartShoot_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_End_Right", DartShoot_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);

		//Dash Animation
		mAnimation->Create(L"Dash_Tele_On_Left", Dash_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_Tele_On_Right", Dash_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_On_Left", Dash_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_On_Right", Dash_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_Shoot_Left", Dash_Shoot_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_Shoot_Right", Dash_Shoot_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_End_Left", Dash_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_End_Right", Dash_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		//Slash Animation
		mAnimation->Create(L"Slash_Tele_On_Left", Slash_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_Tele_On_Right", Slash_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
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
		mAnimation->Create(L"Spike_Tele_On_Left", Spike_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Tele_On_Right", Spike_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_On_Left", Spike_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_On_Right", Spike_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Loop_Left", Spike_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Loop_Right", Spike_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_End_Left", Spike_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_End_Right", Spike_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);


		mAnimation->CompleteEvent(L"Tele_Out_Left") = std::bind(&PureVessel::Tele_Out_State, this);
		mAnimation->CompleteEvent(L"Tele_Out_Right") = std::bind(&PureVessel::Tele_Out_State, this);

		mAnimation->CompleteEvent(L"Intro00") = std::bind(&PureVessel::Intro_01, this);
		mAnimation->CompleteEvent(L"Intro03") = std::bind(&PureVessel::Intro_04, this);
		mAnimation->CompleteEvent(L"Intro04") = std::bind(&PureVessel::Intro_05, this);
		mAnimation->CompleteEvent(L"Intro05") = std::bind(&PureVessel::Intro_06, this);
		mAnimation->CompleteEvent(L"Intro_End") = std::bind(&PureVessel::Idle, this);
		mAnimation->CompleteEvent(L"Idle_Left") = std::bind(&PureVessel::Pattern, this);
		mAnimation->CompleteEvent(L"Idle_Right") = std::bind(&PureVessel::Pattern, this);

		mAnimation->CompleteEvent(L"Dash_Tele_On_Left") = std::bind(&PureVessel::Dash_On, this);
		mAnimation->CompleteEvent(L"Dash_Tele_On_Right") = std::bind(&PureVessel::Dash_On, this);
		mAnimation->CompleteEvent(L"Dash_Shoot_Left") = std::bind(&PureVessel::Dash_End, this);
		mAnimation->CompleteEvent(L"Dash_Shoot_Right") = std::bind(&PureVessel::Dash_End, this);
		mAnimation->CompleteEvent(L"Dash_End_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"Dash_End_Right") = std::bind(&PureVessel::Tele_Out, this);



		//Intro Scale//mTransform->SetScale(Vector3(0.55f, 0.62f, 0.0f));
		//mTransform->SetPosition(Vector3(0.4f, -0.15f, 0.0f));

		mTransform->SetScale(Vector3(0.9f, 0.9f, 0.0f));
		mTransform->SetPosition(Vector3(0.4f, -0.13f, 0.0f));

		mCollider->SetSize(Vector2(0.3f, 0.5f));
		mCollider->SetCenter(Vector2(0.0f, -0.05f));

		GameObject::Initialize();
	}
	void PureVessel::Update()
	{
		mVesselPos = mTransform->GetPosition();

		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mPlayer_Direction = VectorR(mPlayerPos.x, mPlayerPos.y);
		mGrimm_Direction = VectorR(mTransform->GetPosition().x, mTransform->GetPosition().y);
		dr = rigidmath::Direction(mGrimm_Direction, mPlayer_Direction);
		if (dr.x > 0.0f)
		{
			Live_Direction = eDirection::Right;
		}
		else
		{
			Live_Direction = eDirection::Left;
		}

		switch (mState)
		{
		case km::PureVessel::eVesselState::IntroIdle:
			Intro_Idle();
			break;
		case km::PureVessel::eVesselState::Intro00:
			Intro_00();
			break;
		case km::PureVessel::eVesselState::Intro01:
			Intro_01();
			break;
		case km::PureVessel::eVesselState::Intro02:
			Intro_02();
			break;
		case km::PureVessel::eVesselState::Intro03:
			Intro_03();
			break;
		case km::PureVessel::eVesselState::Intro04:
			Intro_04();
			break;
		case km::PureVessel::eVesselState::Intro05:
			Intro_05();
			break;
		case km::PureVessel::eVesselState::Intro06:
			Intro_06();
			break;
		case km::PureVessel::eVesselState::IntroEnd:
			Intro_End();
			break;
		case km::PureVessel::eVesselState::Pattern:
			Pattern();
			break;
		case km::PureVessel::eVesselState::Idle:
			Idle();
			break;
		case km::PureVessel::eVesselState::CounterCast:
			Counter_Cast();
			break;
		case km::PureVessel::eVesselState::CounterLoop:
			Counter_Loop();
			break;
		case km::PureVessel::eVesselState::CounterEnd:
			Counter_End();
			break;
		case km::PureVessel::eVesselState::DashTeleIn:
			Dash_Tele_In();
			break;
		case km::PureVessel::eVesselState::DashOn:
			Dash_On();
			break;
		case km::PureVessel::eVesselState::DashShoot:
			Dash_Shoot();
			break;
		case km::PureVessel::eVesselState::DashEnd:
			Dash_End();
			break;
		case km::PureVessel::eVesselState::KnifeSpikeTeleIn:
			Knife_Spike_Tele_In();
			break;
		case km::PureVessel::eVesselState::KnifeSpike:
			Knife_Spike();
			break;
		case km::PureVessel::eVesselState::SlashTeleIn:
			Slash_Tele_In();
			break;
		case km::PureVessel::eVesselState::Slash:
			Slash();
			break;
		case km::PureVessel::eVesselState::KnifeSpreadTeleIn:
			Knife_Spread_Tele_In();
			break;
		case km::PureVessel::eVesselState::KnifeSpread:
			Knife_Spread();
			break;
		case km::PureVessel::eVesselState::Groggy:
			Groggy();
			break;
		case km::PureVessel::eVesselState::CircleAttackTeleIn:
			Circle_Attack_Tele_In();
			break;
		case km::PureVessel::eVesselState::CircleAttack:
			Circle_Attack();
			break;
		case km::PureVessel::eVesselState::DarkTentacleTeleIn:
			Dark_Tentacle_Tele_In();
			break;
		case km::PureVessel::eVesselState::DarkTentacle:
			Dark_Tentacle();
			break;
		case km::PureVessel::eVesselState::TeleOut:
			Tele_Out();
			break;
		case km::PureVessel::eVesselState::TeleOutState:
			Tele_Out_State();
			break;
		case km::PureVessel::eVesselState::Death:
			Death();
				break;
		default:
			break;
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
		mState = eVesselState::IntroIdle;
		Intro_Idle_Timing += Time::DeltaTime();

		if(Intro_Idle_Check)
			mAnimation->PlayAnimation(L"Intro_Idle", true);

		if (Intro_Idle_Timing > 1.0f)
			Intro_00();
	}

	void PureVessel::Intro_00()
	{
		mState = eVesselState::Intro00;

		if (Intro_00_Check)
		{
			mAnimation->PlayAnimation(L"Intro00", true);
			Intro_00_Check = false;
		}
	}

	void PureVessel::Intro_01()
	{
		mState = eVesselState::Intro01;
		Intro01_Timing += Time::DeltaTime();

		if (Intro_01_Check)
		{
			mAnimation->PlayAnimation(L"Intro01", true);
			Intro_01_Check = false;
		}

		if (Intro01_Timing > 1.0f)
			Intro_02();
	}

	void PureVessel::Intro_02()
	{
		mState = eVesselState::Intro02;
		Intro02_Timing += Time::DeltaTime();

		if (Intro_02_Check)
		{
			mAnimation->PlayAnimation(L"Intro02", true);
			Intro_02_Check = false;
		}

		if (Intro02_Timing > 1.0f)
			Intro_03();
	}

	void PureVessel::Intro_03()
	{
		mState = eVesselState::Intro03;

		if (Intro_03_Check)
		{
			mAnimation->PlayAnimation(L"Intro03", true);
			Intro_03_Check = false;
		}
	}

	void PureVessel::Intro_04()
	{
		mState = eVesselState::Intro04;

		if (Intro_04_Check)
		{
			mTransform->SetScale(Vector3(0.9f, 1.0f, 0.0f));
			mTransform->SetPosition(Vector3(0.4f, -0.09f, 0.0f));
			mAnimation->PlayAnimation(L"Intro04", true);
			Intro_04_Check = false;
		}
	}

	void PureVessel::Intro_05()
	{
		mState = eVesselState::Intro05;

		if (Intro_05_Check)
		{
			mAnimation->PlayAnimation(L"Intro05", true);
			Intro_05_Check = false;
		}
	}

	void PureVessel::Intro_06()
	{
		mState = eVesselState::Intro06;
		Intro06_Timing += Time::DeltaTime();

		if (Intro_06_Check)
		{
			mAnimation->PlayAnimation(L"Intro06", true);
			Intro_06_Check = false;
		}

		if (Intro06_Timing > 1.0f)
			Intro_End();
	}

	void PureVessel::Intro_End()
	{
		mState = eVesselState::IntroEnd;

		if (Intro_End_Check)
		{
			mAnimation->PlayAnimation(L"Intro_End", true);
			Intro_End_Check = false;
		}
	}

	void PureVessel::Pattern()
	{
		switch (mPattern)
		{
		case 0:
			Counter_Cast();
		case 1:
			Dash_Tele_In();
		case 2:
			Knife_Spike_Tele_In();
		case 3:
			Slash();
		case 4:
			Slash_Tele_In();
		default:
			break;
		}

		//Pase 2
		//switch (mPattern)
		//{
		//case 0:
		//	Counter_Cast();
		//case 1:
		//	Dash_Tele_In();
		//case 2:
		//	Knife_Spike_Tele_In();
		//case 3:
		//	Slash();
		//case 4:
		//	Slash_Tele_In();
		//case 5:
		//	Circle_Attack();
		//case 6:
		//	Dark_Tentacle();
		//default:
		//	break;
		//}
	}

	void PureVessel::Idle()
	{
		mState = eVesselState::Idle;

		if (Idle_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Idle_Left", true);
			Idle_Check = false;
		}

		if (Idle_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Idle_Right", true);
			Idle_Check = false;
		}
	}

	void PureVessel::Counter_Cast()
	{
		mState = eVesselState::CounterCast;
		mDirection = Live_Direction;


		if (Counter_Cast_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Counter_Cast_Left", true);
			Counter_Cast_Check = false;
		}
		if (Counter_Cast_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Counter_Cast_Right", true);
			Counter_Cast_Check = false;
		}
	}

	void PureVessel::Counter_Loop()
	{
		mState = eVesselState::CounterLoop;

		if (Counter_Loop_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Counter_Loop_Left", true);
			Counter_Loop_Check = false;
		}
		if (Counter_Loop_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Counter_Loop_Right", true);
			Counter_Loop_Check = false;
		}
	}

	void PureVessel::Counter_End()
	{
		mState = eVesselState::CounterEnd;

		if (Counter_End_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Counter_End_Left", true);
			Counter_End_Check = false;
		}
		if (Counter_End_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Counter_End_Right", true);
			Counter_End_Check = false;
		}
	}



	void PureVessel::Dash_Tele_In()
	{
		mState = eVesselState::DashTeleIn;

		if(Dash_Tele_In_Check)
			mDirection = Live_Direction;

		if (Dash_Tele_In_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Dash_Tele_On_Left", true);
			Dash_Tele_In_Check = false;
			mTransform->SetPosition(Vector3(0.5f, 0.0f, 0.0f));
		}

		if (Dash_Tele_In_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Dash_Tele_On_Right", true);
			Dash_Tele_In_Check = false;
			mTransform->SetPosition(Vector3(0.5f, 0.0f, 0.0f));
		}
	}

	void PureVessel::Dash_On()
	{
		mState = eVesselState::DashOn;

		Dash_On_Timing += Time::DeltaTime();

		if (Dash_On_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Dash_On_Left", false);
			Dash_On_Check = false;
		}
		if (Dash_On_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Dash_On_Right", false);
			Dash_On_Check = false;
		}

		if (Dash_On_Timing > 1.0f)
			mState = eVesselState::DashShoot;
	}

	void PureVessel::Dash_Shoot()
	{
		mState = eVesselState::DashShoot;

		if (Dash_Shoot_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Dash_Shoot_Left", true);
			Dash_Shoot_Check = false;
		}
		if (Dash_Shoot_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Dash_Shoot_Right", true);
			Dash_Shoot_Check = false;
		}

		if (mDirection == eDirection::Left)
		{
			if (Wall_Check == false)
			{
				mVesselPos.x -= 2.5f * Time::DeltaTime();
				mTransform->SetPosition(mVesselPos);
			}
		}
		else if (mDirection == eDirection::Right)
		{
			if (Wall_Check == false)
			{
				mVesselPos.x += 2.5f * Time::DeltaTime();
				mTransform->SetPosition(mVesselPos);
			}
		}
	}

	void PureVessel::Dash_End()
	{
		mState = eVesselState::DashEnd;

		if (Dash_End_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Dash_End_Left", true);
			Dash_End_Check = false;
		}
		if (Dash_End_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Dash_End_Right", true);
			Dash_End_Check = false;
		}
	}

	void PureVessel::Knife_Spike_Tele_In()
	{
	}

	void PureVessel::Knife_Spike()
	{
	}

	void PureVessel::Slash_Tele_In()
	{
	}

	void PureVessel::Slash()
	{
	}

	void PureVessel::Knife_Spread_Tele_In()
	{
	}

	void PureVessel::Knife_Spread()
	{
	}

	void PureVessel::Groggy()
	{
	}

	void PureVessel::Circle_Attack_Tele_In()
	{
	}

	void PureVessel::Circle_Attack()
	{
	}

	void PureVessel::Dark_Tentacle_Tele_In()
	{
	}

	void PureVessel::Dark_Tentacle()
	{
	}

	void PureVessel::Tele_Out()
	{
		mState = eVesselState::TeleOut;

		if (Tele_Out_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Tele_Out_Left", true);
			Tele_Out_Check = false;
		}
		if (Tele_Out_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Tele_Out_Right", true);
			Tele_Out_Check = false;
		}
	}

	void PureVessel::Tele_Out_State()
	{
		mState = eVesselState::TeleOutState;
		Pattern_Timing += Time::DeltaTime();

		mTransform->SetPosition(Vector3(0.0f, 100.0f, 0.0f));

		if (Pattern_Timing > 0.5f)
		{
			mState = eVesselState::Pattern;
			Pattern_Timing = 0.0f;
		}

		Dash_On_Timing = 0.0f;
		Intro_Idle_Timing = 0.0f;
		Intro01_Timing = 0.0f;
		Intro02_Timing = 0.0f;
		Intro06_Timing = 0.0f;

		Intro_Idle_Check = true;
		Intro_00_Check = true;
		Intro_01_Check = true;
		Intro_02_Check = true;
		Intro_03_Check = true;
		Intro_04_Check = true;
		Intro_05_Check = true;
		Intro_06_Check = true;
		Intro_End_Check = true;

		Idle_Check = true;
		Tele_Out_Check = true;

		Counter_Cast_Check = true;
		Counter_Loop_Check = true;
		Counter_End_Check = true;

		Dash_Tele_In_Check = true;
		Dash_On_Check = true;
		Dash_Shoot_Check = true;
		Dash_End_Check = true;

	}

	void PureVessel::Death()
	{

	}

}