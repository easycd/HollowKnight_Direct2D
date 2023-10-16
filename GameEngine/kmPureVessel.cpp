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
		, Groggy_Loop_Timing(0.0f)
		, Intro_Idle_Timing(0.0f)
		, Intro01_Timing(0.0f)
		, Intro02_Timing(0.0f)
		, Intro06_Timing(0.0f)
		, Dash_On_Timing(0.0f)
		, Knife_Spike_Loop_Timing(0.0f)
		, Knife_Spread_Loop_Timing(0.0f)
		, DarkTentacle_Loop_Timing(0.0f)
		, RoarLocationCounter(0)
		, Roar_On_Loop_Timing(0.0f)
		, Roar_Loop_Timing(0.0f)
		, mPattern(2)

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
		std::shared_ptr<Texture> Veesel_Intro_Idle = Resources::Load<Texture>(L"Veesel_Intro_Idle", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_Idle\\Intro_Idle.png");
		std::shared_ptr<Texture> Veesel_Intro00 = Resources::Load<Texture>(L"Veesel_Intro00", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_00\\Intro_00.png");
		std::shared_ptr<Texture> Veesel_Intro01 = Resources::Load<Texture>(L"Veesel_Intro01", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_01\\Intro_01.png");
		std::shared_ptr<Texture> Veesel_Intro02 = Resources::Load<Texture>(L"Veesel_Intro02", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_02\\Intro_02.png");
		std::shared_ptr<Texture> Veesel_Intro03 = Resources::Load<Texture>(L"Veesel_Intro03", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_03\\Intro_03.png");
		std::shared_ptr<Texture> Veesel_Intro04 = Resources::Load<Texture>(L"Veesel_Intro04", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_04\\Intro_04.png");
		std::shared_ptr<Texture> Veesel_Intro05 = Resources::Load<Texture>(L"Veesel_Intro05", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_05\\Intro_05.png");
		std::shared_ptr<Texture> Veesel_Intro06 = Resources::Load<Texture>(L"Veesel_Intro06", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_06\\Intro_06.png");
		std::shared_ptr<Texture> Veesel_Intro_End = Resources::Load<Texture>(L"Veesel_Intro_End", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro_End\\Intro_End.png");

		//Idle Image
		std::shared_ptr<Texture> Vessel_Idle_Left = Resources::Load<Texture>(L"Vessel_Idle_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Idle\\Left\\Idle_Left.png");
		std::shared_ptr<Texture> Vessel_Idle_Right = Resources::Load<Texture>(L"Vessel_Idle_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Idle\\Right\\Idle_Right.png");

		//Stun Image
		std::shared_ptr<Texture> Veesel_Stun_00_Left = Resources::Load<Texture>(L"Veesel_Stun_00_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_00\\Left\\Stun_00_Left.png");
		std::shared_ptr<Texture> Veesel_Stun_00_Right = Resources::Load<Texture>(L"Veesel_Stun_00_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_00\\Right\\Stun_00_Right.png");
		std::shared_ptr<Texture> Veesel_Stun_01_Left = Resources::Load<Texture>(L"Veesel_Stun_01_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_01\\Left\\Stun_01_Left.png");
		std::shared_ptr<Texture> Veesel_Stun_01_Right = Resources::Load<Texture>(L"Veesel_Stun_01_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_01\\Right\\Stun_01_Right.png");
		std::shared_ptr<Texture> Veesel_Stun_02_Left = Resources::Load<Texture>(L"Veesel_Stun_02_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_02\\Left\\Stun_02_Left.png");
		std::shared_ptr<Texture> Veesel_Stun_02_Right = Resources::Load<Texture>(L"Veesel_Stun_02_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Stun\\Stun_02\\Right\\Stun_02_Right.png");

		//Tele_On Image
		std::shared_ptr<Texture> Veesel_Tele_On_Left = Resources::Load<Texture>(L"Veesel_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Veesel_Tele_On_Right = Resources::Load<Texture>(L"Veesel_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");

		//Tele_Out Image
		std::shared_ptr<Texture> Veesel_Tele_Out_Left = Resources::Load<Texture>(L"Veesel_Tele_Out_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_Out\\Left\\Tele_Out_Left.png");
		std::shared_ptr<Texture> Veesel_Tele_Out_Right = Resources::Load<Texture>(L"Veesel_Tele_Out_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_Out\\Right\\Tele_Out_Right.png");

		//Turn Image
		std::shared_ptr<Texture> Veesel_Turn_Left = Resources::Load<Texture>(L"Veesel_Turn_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Turn\\Left\\Turn_Left.png");
		std::shared_ptr<Texture> Veesel_Turn_Right = Resources::Load<Texture>(L"Veesel_Turn_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Turn\\Right\\Turn_Right.png");

		//Counter Image
		std::shared_ptr<Texture> Veesel_Counter_Cast_Left = Resources::Load<Texture>(L"Veesel_Counter_Cast_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_Cast\\Left\\Counter_Cast_Left.png");
		std::shared_ptr<Texture> Veesel_Counter_Cast_Right = Resources::Load<Texture>(L"Veesel_Counter_Cast_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_Cast\\Right\\Counter_Cast_Right.png");
		std::shared_ptr<Texture> Veesel_Counter_Loop_Left = Resources::Load<Texture>(L"Veesel_Counter_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_Loop\\Left\\Counter_Loop_Left.png");
		std::shared_ptr<Texture> Veesel_Counter_Loop_Right = Resources::Load<Texture>(L"Veesel_Counter_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_Loop\\Right\\Counter_Loop_Right.png");
		std::shared_ptr<Texture> Veesel_Counter_End_Left = Resources::Load<Texture>(L"Veesel_Counter_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_End\\Left\\Counter_End_Left.png");
		std::shared_ptr<Texture> Veesel_Counter_End_Right = Resources::Load<Texture>(L"Veesel_Counter_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Counter\\Counter_End\\Right\\Counter_End_Right.png");

		//Dark_Tentacle Image
		std::shared_ptr<Texture> Veesel_Tentacle_Tele_On_Left = Resources::Load<Texture>(L"Veesel_Tentacle_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Veesel_Tentacle_Tele_On_Right = Resources::Load<Texture>(L"Veesel_Tentacle_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> Veesel_Tentacle_On_Left = Resources::Load<Texture>(L"Veesel_Tentacle_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\On\\Left\\Dark_Teneacle_On_Left.png");
		std::shared_ptr<Texture> Veesel_Tentacle_On_Right = Resources::Load<Texture>(L"Veesel_Tentacle_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\On\\Right\\Dark_Teneacle_On_Right.png");
		std::shared_ptr<Texture> Veesel_Tentacle_Start_Left = Resources::Load<Texture>(L"Veesel_Tentacle_Start_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Start\\Left\\Tentacle_Start_Left.png");
		std::shared_ptr<Texture> Veesel_Tentacle_Start_Right = Resources::Load<Texture>(L"Veesel_Tentacle_Start_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Start\\Right\\Tentacle_Start_Right.png");
		std::shared_ptr<Texture> Veesel_Tentacle_Loop_Left = Resources::Load<Texture>(L"Veesel_Tentacle_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Loop\\Left\\Dark_Teneacle_Loop_Left.png");
		std::shared_ptr<Texture> Veesel_Tentacle_Loop_Right = Resources::Load<Texture>(L"Veesel_Tentacle_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\Loop\\Right\\Dark_Teneacle_Loop_Right.png");
		std::shared_ptr<Texture> Veesel_Tentacle_End_Left = Resources::Load<Texture>(L"Veesel_Tentacle_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\End\\Left\\Dark_Teneacle_End_Left.png");
		std::shared_ptr<Texture> Veesel_Tentacle_End_Right = Resources::Load<Texture>(L"Veesel_Tentacle_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dark_Tentacle\\End\\Right\\Dark_Teneacle_End_Right.png");

		//DartShoot Image
		std::shared_ptr<Texture> Veesel_DartShoot_Tele_On_Left = Resources::Load<Texture>(L"Veesel_DartShoot_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Veesel_DartShoot_Tele_On_Right = Resources::Load<Texture>(L"Veesel_DartShoot_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> Veesel_DartShoot_On_Left = Resources::Load<Texture>(L"Veesel_DartShoot_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\On\\Left\\DartShoot_On_Left.png"); //아직 이미지 없음
		std::shared_ptr<Texture> Veesel_DartShoot_On_Right = Resources::Load<Texture>(L"Veesel_DartShoot_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\On\\Right\\DartShoot_On_Right.png"); //아직 이미지 없음
		std::shared_ptr<Texture> Veesel_DartShoot_Start_Left = Resources::Load<Texture>(L"Veesel_DartShoot_Start_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Start\\Left\\Start_Left.png");
		std::shared_ptr<Texture> Veesel_DartShoot_Start_Right = Resources::Load<Texture>(L"Veesel_DartShoot_Start_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Start\\Right\\Start_Right.png");
		std::shared_ptr<Texture> Veesel_DartShoot_Loop_Left = Resources::Load<Texture>(L"Veesel_DartShoot_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Loop\\Left\\DarkShoot_Loop_Left.png");
		std::shared_ptr<Texture> Veesel_DartShoot_Loop_Right = Resources::Load<Texture>(L"Veesel_DartShoot_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\Loop\\Right\\DarkShoot_Loop_Right.png");
		std::shared_ptr<Texture> Veesel_DartShoot_End_Left = Resources::Load<Texture>(L"Veesel_DartShoot_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\End\\Left\\DarkShoot_End_Left.png");
		std::shared_ptr<Texture> Veesel_DartShoot_End_Right = Resources::Load<Texture>(L"Veesel_DartShoot_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\DartShoot\\End\\Right\\DarkShoot_End_Right.png");

		//Dash Image
		std::shared_ptr<Texture> Veesel_Dash_Tele_On_Left = Resources::Load<Texture>(L"Veesel_Dash_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Veesel_Dash_Tele_On_Right = Resources::Load<Texture>(L"Veesel_Dash_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> Veesel_Dash_On_Left = Resources::Load<Texture>(L"Veesel_Dash_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\On\\Left\\Dash_On_Left.png");
		std::shared_ptr<Texture> Veesel_Dash_On_Right = Resources::Load<Texture>(L"Veesel_Dash_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\On\\Right\\Dash_On_Right.png");
		std::shared_ptr<Texture> Veesel_Dash_Shoot_Left = Resources::Load<Texture>(L"Veesel_Dash_Shoot_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\Shoot\\Left\\Dash_Shoot_Left.png");
		std::shared_ptr<Texture> Veesel_Dash_Shoot_Right = Resources::Load<Texture>(L"Veesel_Dash_Shoot_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\Shoot\\Right\\Dash_Shoot_Right.png");
		std::shared_ptr<Texture> Veesel_Dash_End_Left = Resources::Load<Texture>(L"Veesel_Dash_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\End\\Left\\Dash_End_Left.png");
		std::shared_ptr<Texture> Veesel_Dash_End_Right = Resources::Load<Texture>(L"Veesel_Dash_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Dash\\End\\Right\\Dash_End_Right.png");

		//Slash Image
		std::shared_ptr<Texture> Vessel_Slash_Tele_On_Left = Resources::Load<Texture>(L"Vessel_Slash_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_Tele_On_Right = Resources::Load<Texture>(L"Vessel_Slash_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> Vessel_Slash_On_Left = Resources::Load<Texture> (L"Vessel_Slash_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\On\\Left\\Slash_On_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_On_Right = Resources::Load<Texture>(L"Vessel_Slash_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\On\\Right\\Slash_On_Right.png");
		std::shared_ptr<Texture> Vessel_Slash_00_Left = Resources::Load<Texture> (L"Vessel_Slash_00_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_00\\Left\\Slash_Slash00_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_00_Right = Resources::Load<Texture>(L"Vessel_Slash_00_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_00\\Right\\Slash_Slash00_Right.png");
		std::shared_ptr<Texture> Vessel_Slash_01_Left = Resources::Load<Texture> (L"Vessel_Slash_01_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_01\\Left\\Slash_Slash01_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_01_Right = Resources::Load<Texture>(L"Vessel_Slash_01_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_01\\Right\\Slash_Slash01_Right.png");
		std::shared_ptr<Texture> Vessel_Slash_02_Left = Resources::Load<Texture> (L"Vessel_Slash_02_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_02\\Left\\Slash_Slash02_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_02_Right = Resources::Load<Texture>(L"Vessel_Slash_02_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_02\\Right\\Slash_Slash02_Right.png");
		std::shared_ptr<Texture> Vessel_Slash_03_Left = Resources::Load<Texture> (L"Vessel_Slash_03_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_03\\Left\\Slash_Slash03_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_03_Right = Resources::Load<Texture>(L"Vessel_Slash_03_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_03\\Right\\Slash_Slash03_Right.png");
		std::shared_ptr<Texture> Vessel_Slash_04_Left = Resources::Load<Texture> (L"Vessel_Slash_04_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_04\\Left\\Slash_Slash04_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_04_Right = Resources::Load<Texture>(L"Vessel_Slash_04_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_04\\Right\\Slash_Slash04_Right.png");
		std::shared_ptr<Texture> Vessel_Slash_05_Left = Resources::Load<Texture> (L"Vessel_Slash_05_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_05\\Left\\Slash_Slash05_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_05_Right = Resources::Load<Texture>(L"Vessel_Slash_05_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\Slash_05\\Right\\Slash_Slash05_Right.png");
		std::shared_ptr<Texture> Vessel_Slash_End_Left = Resources::Load<Texture>(L"Vessel_Slash_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\End\\Left\\Slash_End_Left.png");
		std::shared_ptr<Texture> Vessel_Slash_End_Right = Resources::Load<Texture>(L"Vessel_Slash_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Slash\\End\\Right\\Slash_End_Right.png");

		//SpikeAttack Image
		std::shared_ptr<Texture> Vessel_Spike_Tele_On_Left = Resources::Load<Texture>(L"Vessel_Spike_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Vessel_Spike_Tele_On_Right = Resources::Load<Texture>(L"Vessel_Spike_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> Vessel_Spike_On_Left = Resources::Load<Texture>(L"Vessel_Spike_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\On\\Left\\SpikeAttack_On_Left.png");
		std::shared_ptr<Texture> Vessel_Spike_On_Right = Resources::Load<Texture>(L"Vessel_Spike_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\On\\Right\\SpikeAttack_On_Right.png");
		std::shared_ptr<Texture> Vessel_Spike_Start_Left = Resources::Load<Texture>(L"Vessel_Spike_Start_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\Start\\Left\\Spike_Start_Left.png");
		std::shared_ptr<Texture> Vessel_Spike_Start_Right = Resources::Load<Texture>(L"Vessel_Spike_Start_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\Start\\Right\\Spike_Start_Right.png");
		std::shared_ptr<Texture> Vessel_Spike_Loop_Left = Resources::Load<Texture>(L"Vessel_Spike_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\Loop\\Left\\SpikeAttack_Loop_Left.png");
		std::shared_ptr<Texture> Vessel_Spike_Loop_Right = Resources::Load<Texture>(L"Vessel_Spike_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\Loop\\Right\\SpikeAttack_Loop_Right.png");
		std::shared_ptr<Texture> Vessel_Spike_End_Left = Resources::Load<Texture>(L"Vessel_Spike_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\End\\Left\\SpikeAttack_End_Left.png");
		std::shared_ptr<Texture> Vessel_Spike_End_Right = Resources::Load<Texture>(L"Vessel_Spike_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\SpikeAttack\\End\\Right\\SpikeAttack_End_Right.png");

		//Roar Image
		std::shared_ptr<Texture> Vessel_Roar_Tele_On_Left = Resources::Load<Texture>(L"Vessel_Roar_Tele_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Left\\Tele_On_Left.png");
		std::shared_ptr<Texture> Vessel_Roar_Tele_On_Right = Resources::Load<Texture>(L"Vessel_Roar_Tele_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Tele_On\\Right\\Tele_On_Right.png");
		std::shared_ptr<Texture> Vessel_Roar_On_Left = Resources::Load<Texture>(L"Vessel_Roar_On_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\On\\Left\\Roar_On_Left.png");
		std::shared_ptr<Texture> Vessel_Roar_On_Right = Resources::Load<Texture>(L"Vessel_Roar_On_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\On\\Right\\Roar_On_Right.png");
		std::shared_ptr<Texture> Vessel_Roar_On_Loop_Left = Resources::Load<Texture>(L"Vessel_Roar_On_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\On_Loop\\Left\\Roar_On_Loop_Left.png");
		std::shared_ptr<Texture> Vessel_Roar_On_Loop_Right = Resources::Load<Texture>(L"Vessel_Roar_On_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\On_Loop\\Right\\Roar_On_Loop_Right.png");

		std::shared_ptr<Texture> Vessel_Roar_Start_Left = Resources::Load<Texture>(L"Vessel_Roar_Start_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\Start\\Left\\Roar_Start_Left.png");
		std::shared_ptr<Texture> Vessel_Roar_Start_Right = Resources::Load<Texture>(L"Vessel_Roar_Start_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\Start\\Right\\Roar_Start_Right.png");
		std::shared_ptr<Texture> Vessel_Roar_Loop_Left = Resources::Load<Texture>(L"Vessel_Roar_Loop_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\Loop\\Left\\Roar_Loop_Left.png");
		std::shared_ptr<Texture> Vessel_Roar_Loop_Right = Resources::Load<Texture>(L"Vessel_Roar_Loop_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\Loop\\Right\\Roar_Loop_Right.png");
		std::shared_ptr<Texture> Vessel_Roar_End_Left = Resources::Load<Texture>(L"Vessel_Roar_End_Left", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\End\\Left\\Roar_End_Left.png");
		std::shared_ptr<Texture> Vessel_Roar_End_Right = Resources::Load<Texture>(L"Vessel_Roar_End_Right", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Roar\\End\\Right\\Roar_End_Right.png");


		//Intro Animation
		mAnimation->Create(L"Intro_Idle", Veesel_Intro_Idle, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro00", Veesel_Intro00, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro01", Veesel_Intro01, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro02", Veesel_Intro02, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 3, Vector2(0.06f, 0.02f), 0.07f);
		mAnimation->Create(L"Intro03", Veesel_Intro03, Vector2(0.0f, 0.0f), Vector2(648.0f, 692.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro04", Veesel_Intro04, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 12, Vector2(0.02f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro05", Veesel_Intro05, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.06f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro06", Veesel_Intro06, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.06f, 0.02f), 0.1f);
		mAnimation->Create(L"Intro_End", Veesel_Intro_End, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.06f, 0.02f), 0.1f);

		//Idle Animation
		mAnimation->Create(L"Vessel_Idle_Left", Vessel_Idle_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Vessel_Idle_Right", Vessel_Idle_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);


		//Stun Animation
		mAnimation->Create(L"Stun_00_Left", Veesel_Stun_00_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Stun_00_Right", Veesel_Stun_00_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Stun_01_Left", Veesel_Stun_01_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Stun_01_Right", Veesel_Stun_01_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Stun_02_Left", Veesel_Stun_02_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Stun_02_Right", Veesel_Stun_02_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);


		//Tele_On Animation
		mAnimation->Create(L"Tele_On_Left", Veesel_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tele_On_Right", Veesel_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		 
		//Tele_Out Animation
		mAnimation->Create(L"Tele_Out_Left", Veesel_Tele_Out_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tele_Out_Right", Veesel_Tele_Out_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);

		//Turn Animation
		mAnimation->Create(L"Turn_Left", Veesel_Turn_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Turn_Right", Veesel_Turn_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);

		//Counter Animation
		mAnimation->Create(L"Counter_Cast_Left", Veesel_Counter_Cast_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_Cast_Right", Veesel_Counter_Cast_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_Loop_Left", Veesel_Counter_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_Loop_Right", Veesel_Counter_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_End_Left", Veesel_Counter_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Counter_End_Right", Veesel_Counter_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);

		//Dark_Tentacle Animation
		mAnimation->Create(L"Tentacle_Tele_On_Left", Veesel_Tentacle_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Tele_On_Right", Veesel_Tentacle_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_On_Left", Veesel_Tentacle_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_On_Right", Veesel_Tentacle_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Start_Left", Veesel_Tentacle_Start_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Start_Right", Veesel_Tentacle_Start_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Loop_Left", Veesel_Tentacle_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_Loop_Right", Veesel_Tentacle_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_End_Left", Veesel_Tentacle_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Tentacle_End_Right", Veesel_Tentacle_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		
		//DartShoot Animation
		mAnimation->Create(L"DartShoot_Tele_On_Left", Veesel_DartShoot_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Tele_On_Right", Veesel_DartShoot_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_On_Left", Veesel_DartShoot_On_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_On_Right", Veesel_DartShoot_On_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Start_Left", Veesel_DartShoot_Start_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Start_Right", Veesel_DartShoot_Start_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Loop_Left", Veesel_DartShoot_Loop_Left, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_Loop_Right", Veesel_DartShoot_Loop_Right, Vector2(0.0f, 0.0f), Vector2(939.0f, 698.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_End_Left", Veesel_DartShoot_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"DartShoot_End_Right", Veesel_DartShoot_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);

		//Dash Animation
		mAnimation->Create(L"Dash_Tele_On_Left", Veesel_Dash_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_Tele_On_Right", Veesel_Dash_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_On_Left", Veesel_Dash_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_On_Right", Veesel_Dash_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_Shoot_Left", Veesel_Dash_Shoot_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_Shoot_Right", Veesel_Dash_Shoot_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_End_Left", Veesel_Dash_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Dash_End_Right", Veesel_Dash_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		//Slash Animation
		mAnimation->Create(L"Slash_Tele_On_Left", Vessel_Slash_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_Tele_On_Right", Vessel_Slash_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_On_Left", Vessel_Slash_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 8, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_On_Right", Vessel_Slash_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 8, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_00_Left", Vessel_Slash_00_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_00_Right", Vessel_Slash_00_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_01_Left", Vessel_Slash_01_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_01_Right", Vessel_Slash_01_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_02_Left", Vessel_Slash_02_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_02_Right", Vessel_Slash_02_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_03_Left", Vessel_Slash_03_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_03_Right", Vessel_Slash_03_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 2, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_04_Left", Vessel_Slash_04_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_04_Right", Vessel_Slash_04_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_05_Left", Vessel_Slash_05_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_05_Right", Vessel_Slash_05_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_End_Left", Vessel_Slash_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Slash_End_Right", Vessel_Slash_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		//SpikeAttack Animation
		mAnimation->Create(L"Spike_Tele_On_Left", Vessel_Spike_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Tele_On_Right", Vessel_Spike_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_On_Left", Vessel_Spike_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_On_Right", Vessel_Spike_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Start_Left", Vessel_Spike_Start_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Start_Right", Vessel_Spike_Start_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 1, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Loop_Left", Vessel_Spike_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_Loop_Right", Vessel_Spike_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_End_Left", Vessel_Spike_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Spike_End_Right", Vessel_Spike_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		//Roar Animation
		mAnimation->Create(L"Roar_Tele_On_Left", Vessel_Roar_Tele_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_Tele_On_Right", Vessel_Roar_Tele_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 5, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_On_Left", Vessel_Roar_On_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_On_Right", Vessel_Roar_On_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 6, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_On_Loop_Left", Vessel_Roar_On_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_On_Loop_Right", Vessel_Roar_On_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_Start_Left", Vessel_Roar_Start_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 7, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_Start_Right", Vessel_Roar_Start_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 7, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_Loop_Left", Vessel_Roar_Loop_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_Loop_Right", Vessel_Roar_Loop_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 3, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_End_Left", Vessel_Roar_End_Left, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);
		mAnimation->Create(L"Roar_End_Right", Vessel_Roar_End_Right, Vector2(0.0f, 0.0f), Vector2(1296.0f, 908.0f), 4, Vector2(0.0f, 0.02f), 0.1f);

		mAnimation->CompleteEvent(L"Stun_00_Left") = std::bind(&PureVessel::Groggy_Loop, this);
		mAnimation->CompleteEvent(L"Stun_00_Right") = std::bind(&PureVessel::Groggy_Loop, this);
		mAnimation->CompleteEvent(L"Stun_02_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"Stun_02_Right") = std::bind(&PureVessel::Tele_Out, this);

		mAnimation->CompleteEvent(L"Tele_Out_Left") = std::bind(&PureVessel::Tele_Out_State, this);
		mAnimation->CompleteEvent(L"Tele_Out_Right") = std::bind(&PureVessel::Tele_Out_State, this);

		mAnimation->CompleteEvent(L"Intro00") = std::bind(&PureVessel::Intro_01, this);
		mAnimation->CompleteEvent(L"Intro03") = std::bind(&PureVessel::Intro_04, this);
		mAnimation->CompleteEvent(L"Intro04") = std::bind(&PureVessel::Intro_05, this);
		mAnimation->CompleteEvent(L"Intro05") = std::bind(&PureVessel::Intro_06, this);
		mAnimation->CompleteEvent(L"Intro_End") = std::bind(&PureVessel::Idle, this);

		mAnimation->CompleteEvent(L"Vessel_Idle_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"Vessel_Idle_Right") = std::bind(&PureVessel::Tele_Out, this);

		mAnimation->CompleteEvent(L"Dash_Tele_On_Left") = std::bind(&PureVessel::Dash_On, this);
		mAnimation->CompleteEvent(L"Dash_Tele_On_Right") = std::bind(&PureVessel::Dash_On, this);
		mAnimation->CompleteEvent(L"Dash_Shoot_Left") = std::bind(&PureVessel::Dash_End, this);
		mAnimation->CompleteEvent(L"Dash_Shoot_Right") = std::bind(&PureVessel::Dash_End, this);
		mAnimation->CompleteEvent(L"Dash_End_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"Dash_End_Right") = std::bind(&PureVessel::Tele_Out, this);

		mAnimation->CompleteEvent(L"Spike_Tele_On_Left") = std::bind(&PureVessel::Knife_Spike_On, this);
		mAnimation->CompleteEvent(L"Spike_Tele_On_Right") = std::bind(&PureVessel::Knife_Spike_On, this);
		mAnimation->CompleteEvent(L"Spike_On_Left") = std::bind(&PureVessel::Knife_Spike_Start, this);
		mAnimation->CompleteEvent(L"Spike_On_Right") = std::bind(&PureVessel::Knife_Spike_Start, this);
		mAnimation->CompleteEvent(L"Spike_End_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"Spike_End_Right") = std::bind(&PureVessel::Tele_Out, this);

		mAnimation->CompleteEvent(L"Slash_Tele_On_Left") = std::bind(&PureVessel::Slash_On, this);
		mAnimation->CompleteEvent(L"Slash_Tele_On_Right") = std::bind(&PureVessel::Slash_On, this);
		mAnimation->CompleteEvent(L"Slash_On_Left") = std::bind(&PureVessel::Slash_00, this);
		mAnimation->CompleteEvent(L"Slash_On_Right") = std::bind(&PureVessel::Slash_00, this);
		mAnimation->CompleteEvent(L"Slash_00_Left") = std::bind(&PureVessel::Slash_01, this);
		mAnimation->CompleteEvent(L"Slash_00_Right") = std::bind(&PureVessel::Slash_01, this);
		mAnimation->CompleteEvent(L"Slash_01_Left") = std::bind(&PureVessel::Slash_02, this);
		mAnimation->CompleteEvent(L"Slash_01_Right") = std::bind(&PureVessel::Slash_02, this);
		mAnimation->CompleteEvent(L"Slash_02_Left") = std::bind(&PureVessel::Slash_03, this);
		mAnimation->CompleteEvent(L"Slash_02_Right") = std::bind(&PureVessel::Slash_03, this);
		mAnimation->CompleteEvent(L"Slash_03_Left") = std::bind(&PureVessel::Slash_04, this);
		mAnimation->CompleteEvent(L"Slash_03_Right") = std::bind(&PureVessel::Slash_04, this);
		mAnimation->CompleteEvent(L"Slash_04_Left") = std::bind(&PureVessel::Slash_05, this);
		mAnimation->CompleteEvent(L"Slash_04_Right") = std::bind(&PureVessel::Slash_05, this);
		mAnimation->CompleteEvent(L"Slash_05_Left") = std::bind(&PureVessel::Slash_End, this);
		mAnimation->CompleteEvent(L"Slash_05_Right") = std::bind(&PureVessel::Slash_End, this);
		mAnimation->CompleteEvent(L"Slash_End_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"Slash_End_Right") = std::bind(&PureVessel::Tele_Out, this);

		mAnimation->CompleteEvent(L"DartShoot_Tele_On_Left") = std::bind(&PureVessel::Knife_Spread_On, this);
		mAnimation->CompleteEvent(L"DartShoot_Tele_On_Right") = std::bind(&PureVessel::Knife_Spread_On, this);
		mAnimation->CompleteEvent(L"DartShoot_On_Left") = std::bind(&PureVessel::Knife_Spread_Start, this);
		mAnimation->CompleteEvent(L"DartShoot_On_Right") = std::bind(&PureVessel::Knife_Spread_Start, this);
		mAnimation->CompleteEvent(L"DartShoot_Start_Left") = std::bind(&PureVessel::Knife_Spread_Loop, this);
		mAnimation->CompleteEvent(L"DartShoot_Start_Right") = std::bind(&PureVessel::Knife_Spread_Loop, this);
		mAnimation->CompleteEvent(L"DartShoot_End_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"DartShoot_End_Right") = std::bind(&PureVessel::Tele_Out, this);

		mAnimation->CompleteEvent(L"Tentacle_Tele_On_Left") = std::bind(&PureVessel::Dark_Tentacle_On, this);
		mAnimation->CompleteEvent(L"Tentacle_Tele_On_Right") = std::bind(&PureVessel::Dark_Tentacle_On, this);
		mAnimation->CompleteEvent(L"Tentacle_On_Left") = std::bind(&PureVessel::Dark_Tentacle_Start, this);
		mAnimation->CompleteEvent(L"Tentacle_On_Right") = std::bind(&PureVessel::Dark_Tentacle_Start, this);
		mAnimation->CompleteEvent(L"Tentacle_Start_Left") = std::bind(&PureVessel::Dark_Tentacle_Loop, this);
		mAnimation->CompleteEvent(L"Tentacle_Start_Right") = std::bind(&PureVessel::Dark_Tentacle_Loop, this);
		mAnimation->CompleteEvent(L"Tentacle_End_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"Tentacle_End_Right") = std::bind(&PureVessel::Tele_Out, this);

		mAnimation->CompleteEvent(L"Roar_Tele_On_Left") = std::bind(&PureVessel::Roar_On, this);
		mAnimation->CompleteEvent(L"Roar_Tele_On_Right") = std::bind(&PureVessel::Roar_On, this);
		mAnimation->CompleteEvent(L"Roar_On_Left") = std::bind(&PureVessel::Roar_On_Loop, this);
		mAnimation->CompleteEvent(L"Roar_On_Right") = std::bind(&PureVessel::Roar_On_Loop, this);
		mAnimation->CompleteEvent(L"Roar_Start_Left") = std::bind(&PureVessel::Roar_Loop, this);
		mAnimation->CompleteEvent(L"Roar_Start_Right") = std::bind(&PureVessel::Roar_Loop, this);
		mAnimation->CompleteEvent(L"Roar_End_Left") = std::bind(&PureVessel::Tele_Out, this);
		mAnimation->CompleteEvent(L"Roar_End_Right") = std::bind(&PureVessel::Tele_Out, this);


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
		case km::PureVessel::eVesselState::KnifeSpikeOn:
			Knife_Spike_On();
			break;
		case km::PureVessel::eVesselState::KnifeSpikeStart:
			Knife_Spike_Start();
			break;
		case km::PureVessel::eVesselState::KnifeSpikeLoop:
			Knife_Spike_Loop();
			break;
		case km::PureVessel::eVesselState::KnifeSpikeEnd:
			Knife_Spike_End();
			break;
		case km::PureVessel::eVesselState::SlashTeleIn:
			Slash_Tele_In();
			break;
		case km::PureVessel::eVesselState::SlashOn:
			Slash_On();
			break;
		case km::PureVessel::eVesselState::Slash00:
			Slash_00();
			break;
		case km::PureVessel::eVesselState::Slash01:
			Slash_01();
			break;
		case km::PureVessel::eVesselState::Slash02:
			Slash_02();
			break;
		case km::PureVessel::eVesselState::Slash03:
			Slash_03();
			break;
		case km::PureVessel::eVesselState::Slash04:
			Slash_04();
			break;
		case km::PureVessel::eVesselState::Slash05:
			Slash_05();
			break;
		case km::PureVessel::eVesselState::SlashEnd:
			Slash_End();
			break;
		case km::PureVessel::eVesselState::KnifeSpreadTeleIn:
			Knife_Spread_Tele_In();
			break;
		case km::PureVessel::eVesselState::KnifeSpreadOn:
			Knife_Spread_On();
			break;
		case km::PureVessel::eVesselState::KnifeSpreadStart:
			Knife_Spread_Start();
			break;
		case km::PureVessel::eVesselState::KnifeSpreadLoop:
			Knife_Spread_Loop();
			break;
		case km::PureVessel::eVesselState::KnifeSpreadEnd:
			Knife_Spread_End();
			break;
		case km::PureVessel::eVesselState::GroggyStart:
			Groggy_Start();
			break;
		case km::PureVessel::eVesselState::GroggyLoop:
			Groggy_Loop();
			break;
		case km::PureVessel::eVesselState::GroggyEnd:
			Groggy_End();
			break;
		case km::PureVessel::eVesselState::RoarTeleIn:
			Roar_Tele_In();
			break;
		case km::PureVessel::eVesselState::RoarOn:
			Roar_On();
			break;
		case km::PureVessel::eVesselState::RoarOnLoop:
			Roar_On_Loop();
			break;
		case km::PureVessel::eVesselState::RoarStart:
			Roar_Start();
			break;
		case km::PureVessel::eVesselState::RoarLoop:
			Roar_Loop();
			break;
		case km::PureVessel::eVesselState::RoarEnd:
			Roar_End();
			break;
		case km::PureVessel::eVesselState::DarkTentacleTeleIn:
			Dark_Tentacle_Tele_In();
			break;
		case km::PureVessel::eVesselState::DarkTentacleOn:
			Dark_Tentacle_On();
			break;
		case km::PureVessel::eVesselState::DarkTentacleStart:
			Dark_Tentacle_Start();
			break;
		case km::PureVessel::eVesselState::DarkTentacleLoop:
			Dark_Tentacle_Loop();
			break;
		case km::PureVessel::eVesselState::DarkTentacleEnd:
			Dark_Tentacle_End();
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

		//Test
		switch (mPattern)
		{
		case 0:
			Counter_Cast();
			break;
		case 1:
			Dash_Tele_In();
			break;
		case 2:
			Knife_Spike_Tele_In();
			break;
		case 3:
			Slash_Tele_In();
			break;
		case 4:
			Knife_Spread_Tele_In();
			break;
		case 5:
			Roar_Tele_In();
			break;
		case 6:
			Dark_Tentacle_Tele_In();
			break;
		default:
			break;
		}

		////Pase 1
		//switch (mPattern)
		//{
		//case 0:
		//	Counter_Cast();
		//	break;
		//case 1:
		//	Dash_Tele_In();
		//	break;
		//case 2:
		//	Knife_Spike_Tele_In();
		//	break;
		//case 3:
		//	Slash_Tele_In();
		//	break;
		//case 4:
		//	Knife_Spread_Tele_In();
		//	break;
		//default:
		//	break;
		//}
		//
		////Pase 2
		//switch (mPattern)
		//{
		//case 0:
		//	Counter_Cast();
		//	break;
		//case 1:
		//	Dash_Tele_In();
		//	break;
		//case 2:
		//	Knife_Spike_Tele_In();
		//	break;
		//case 4:
		//	Slash_Tele_In();
		//	break;
		//case 5:
		//	Knife_Spread_Tele_In();
		//	break;
		//case 6:
		//	Roar_Tele_In();
		//	break;
		//case 7:
		//	Dark_Tentacle_Tele_In();
		//	break;
		//case 8:
		//	Roar_Tele_In();
		//	break;
		//default:
		//	break;
		//}
	}

	void PureVessel::Idle()
	{
		mState = eVesselState::Idle;

		if (Idle_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Vessel_Idle_Left", true);
			Idle_Check = false;
		}

		if (Idle_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Vessel_Idle_Right", true);
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

			if (mPlayerPos.x < 0.241f)
			{
				mTransform->SetPosition(Vector3(mPlayerPos.x + 0.7f, -0.125f, 0.0f));
			}
		}

		if (Dash_Tele_In_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Dash_Tele_On_Right", true);
			Dash_Tele_In_Check = false;

			if (mPlayerPos.x > -0.493f)
			{
				mTransform->SetPosition(Vector3(mPlayerPos.x - 0.7f, -0.125f, 0.0f));
			}
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

		if (Dash_On_Timing > 0.7f)
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
				mVesselPos.x -= 3.5f * Time::DeltaTime();
				mTransform->SetPosition(mVesselPos);
			}
		}
		else if (mDirection == eDirection::Right)
		{
			if (Wall_Check == false)
			{
				mVesselPos.x += 3.5f * Time::DeltaTime();
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
		mState = eVesselState::KnifeSpikeTeleIn;

		if (Knife_Spike_Tele_In_Check)
		{
			mDirection = Live_Direction;
			Temp_Pos = mPlayerPos;
		}

		if (Knife_Spike_Tele_In_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Spike_Tele_On_Left", true);
			Knife_Spike_Tele_In_Check = false;
		}
		if (Knife_Spike_Tele_In_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Spike_Tele_On_Right", true);
			Knife_Spike_Tele_In_Check = false;
		}

		mTransform->SetPosition(Temp_Pos.x, 0.4f, 0.0f);
	}

	void PureVessel::Knife_Spike_On()
	{
		mState = eVesselState::KnifeSpikeOn;

		if (Spike_On_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Spike_On_Left", true);
			Spike_On_Check = false;
		}
		if (Spike_On_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Spike_On_Right", true);
			Spike_On_Check = false;
		}
	}

	void PureVessel::Knife_Spike_Start()
	{
		mState = eVesselState::KnifeSpikeStart;

		if (Spike_Start_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Spike_Start_Left", true);
			Spike_Start_Check = false;
		}
		if (Spike_Start_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Spike_Start_Right", true);
			Spike_Start_Check = false;
		}

		if (mVesselPos.y > -0.12f && mDirection == eDirection::Left)
		{
			mVesselPos.x -= 0.5f * Time::DeltaTime();
		    mVesselPos.y -= 2.0f * Time::DeltaTime();
		}
		if (mVesselPos.y > -0.12f && mDirection == eDirection::Right)
		{
			mVesselPos.x += 0.5f * Time::DeltaTime();
			mVesselPos.y -= 2.0f * Time::DeltaTime();
		}

		if(mVesselPos.y < -0.12f)
			mState = eVesselState::KnifeSpikeLoop;

		mTransform->SetPosition(mVesselPos);
	}

	void PureVessel::Knife_Spike_Loop()
	{
		mState = eVesselState::KnifeSpikeLoop;
		Knife_Spike_Loop_Timing += Time::DeltaTime();

		if (Spike_Loop_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Spike_Loop_Left", true);
			Spike_Loop_Check = false;
		}
		if (Spike_Loop_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Spike_Loop_Right", true);
			Spike_Loop_Check = false;
		}

		if(Knife_Spike_Loop_Timing > 2.0f)
			mState = eVesselState::KnifeSpikeEnd;
	}

	void PureVessel::Knife_Spike_End()
	{
		mState = eVesselState::KnifeSpikeEnd;

		if (Spike_End_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Spike_End_Left", true);
			Spike_End_Check = false;
		}
		if (Spike_End_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Spike_End_Right", true);
			Spike_End_Check = false;
		}
	}

	void PureVessel::Slash_Tele_In()
	{
		mState = eVesselState::SlashTeleIn;

		if(Slash_Tele_In_Check)
			mDirection = Live_Direction;

		if (Slash_Tele_In_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_Tele_On_Left", true);
			Slash_Tele_In_Check = false;

			if (mPlayerPos.x < 0.241f)
			{
				mTransform->SetPosition(Vector3(mPlayerPos.x + 0.7f, -0.125f, 0.0f));
			}
		}

		if (Slash_Tele_In_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_Tele_On_Right", true);
			Slash_Tele_In_Check = false;

			if (mPlayerPos.x > -0.493f)
			{
				mTransform->SetPosition(Vector3(mPlayerPos.x - 0.7f, -0.125f, 0.0f));
			}
		}
	}

	void PureVessel::Slash_On()
	{
		mState = eVesselState::SlashOn;

		if (Slash_On_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_On_Left", true);
			Slash_On_Check = false;
		}
		if (Slash_On_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_On_Right", true);
			Slash_On_Check = false;
		}

	}

	void PureVessel::Slash_00()
	{
		mState = eVesselState::Slash00;

		if (Slash_00_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_00_Left", true);
			Slash_00_Check = false;
		}
		if (Slash_00_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_00_Right", true);
			Slash_00_Check = false;
		}

		if(mDirection == eDirection::Left)
			mVesselPos.x -= 2.5f * Time::DeltaTime();

		if (mDirection == eDirection::Right)
			mVesselPos.x += 2.5f * Time::DeltaTime();

		mTransform->SetPosition(mVesselPos);
	}

	void PureVessel::Slash_01()
	{
		mState = eVesselState::Slash01;

		if (Slash_01_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_01_Left", true);
			Slash_01_Check = false;
		}
		if (Slash_01_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_01_Right", true);
			Slash_01_Check = false;
		}
	}

	void PureVessel::Slash_02()
	{
		mState = eVesselState::Slash02;

		if (Slash_02_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_02_Left", true);
			Slash_02_Check = false;
		}
		if (Slash_02_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_02_Right", true);
			Slash_02_Check = false;
		}

		if (mDirection == eDirection::Left)
			mVesselPos.x -= 2.5f * Time::DeltaTime();

		if (mDirection == eDirection::Right)
			mVesselPos.x += 2.5f * Time::DeltaTime();

		mTransform->SetPosition(mVesselPos);
	}

	void PureVessel::Slash_03()
	{
		mState = eVesselState::Slash03;

		if (Slash_03_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_03_Left", true);
			Slash_03_Check = false;
		}
		if (Slash_03_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_03_Right", true);
			Slash_03_Check = false;
		}
	}

	void PureVessel::Slash_04()
	{
		mState = eVesselState::Slash04;

		if (Slash_04_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_04_Left", true);
			Slash_04_Check = false;
		}
		if (Slash_04_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_04_Right", true);
			Slash_04_Check = false;
		}

		if (mDirection == eDirection::Left)
			mVesselPos.x -= 2.5f * Time::DeltaTime();

		if (mDirection == eDirection::Right)
			mVesselPos.x += 2.5f * Time::DeltaTime();

		mTransform->SetPosition(mVesselPos);
	}

	void PureVessel::Slash_05()
	{
		mState = eVesselState::Slash05;

		if (Slash_05_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_05_Left", true);
			Slash_05_Check = false;
		}
		if (Slash_05_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_05_Right", true);
			Slash_05_Check = false;
		}
	}

	void PureVessel::Slash_End()
	{
		mState = eVesselState::SlashEnd;

		if (Slash_End_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Slash_End_Left", true);
			Slash_End_Check = false;
		}
		if (Slash_End_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Slash_End_Right", true);
			Slash_End_Check = false;
		}
	}

	void PureVessel::Knife_Spread_Tele_In()
	{
		mState = eVesselState::KnifeSpreadTeleIn;

		if (DartShoot_Tele_In_Check)
			mDirection = Live_Direction;

		if (DartShoot_Tele_In_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"DartShoot_Tele_On_Left", true);
			DartShoot_Tele_In_Check = false;

			if (mPlayerPos.x < 0.241f)
			{
				mTransform->SetPosition(Vector3(mPlayerPos.x + 0.85f, -0.125f, 0.0f));
			}
		}

		if (DartShoot_Tele_In_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"DartShoot_Tele_On_Right", true);
			DartShoot_Tele_In_Check = false;

			if (mPlayerPos.x > -0.493f)
			{
				mTransform->SetPosition(Vector3(mPlayerPos.x - 0.85f, -0.125f, 0.0f));
			}
		}
	}

	void PureVessel::Knife_Spread_On()
	{
		mState = eVesselState::KnifeSpreadOn;
		mTransform->SetScale(Vector3(0.7f, 0.7f, 0.0f));

		if (Spread_On_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"DartShoot_On_Left", true);
			Spread_On_Check = false;
		}
		if (Spread_On_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"DartShoot_On_Right", true);
			Spread_On_Check = false;
		}
	}

	void PureVessel::Knife_Spread_Start()
	{
		mState = eVesselState::KnifeSpreadStart;

		if (Spread_Start_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"DartShoot_Start_Left", true);
			Spread_Start_Check = false;
		}
		if (Spread_Start_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"DartShoot_Start_Right", true);
			Spread_Start_Check = false;
		}
	}

	void PureVessel::Knife_Spread_Loop()
	{
		mState = eVesselState::KnifeSpreadLoop;
		Knife_Spread_Loop_Timing += Time::DeltaTime();

		if (Spread_Loop_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"DartShoot_Loop_Left", true);
			Spread_Loop_Check = false;
		}
		if (Spread_Loop_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"DartShoot_Loop_Right", true);
			Spread_Loop_Check = false;
		}

		if(Knife_Spread_Loop_Timing > 2.0f)
			mState = eVesselState::KnifeSpreadEnd;
	}

	void PureVessel::Knife_Spread_End()
	{
		mState = eVesselState::KnifeSpreadEnd;
		mTransform->SetScale(Vector3(0.9f, 0.9f, 0.0f));

		if (Spread_End_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"DartShoot_End_Left", true);
			Spread_End_Check = false;
		}
		if (Spread_End_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"DartShoot_End_Right", true);
			Spread_End_Check = false;
		}
	}

	void PureVessel::Groggy_Start()
	{
		mState = eVesselState::GroggyStart;
		mTransform->SetPosition(Vector3(0.0f, -0.13f, 0.0f));
		
		if (Groggy_Start_Check)
			mDirection = Live_Direction;

		if (Groggy_Start_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Stun_00_Left", true);
			Groggy_Start_Check = false;
		}
		if (Groggy_Start_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Stun_00_Right", true);
			Groggy_Start_Check = false;
		}
	}

	void PureVessel::Groggy_Loop()
	{
		mState = eVesselState::GroggyLoop;
		Groggy_Loop_Timing += Time::DeltaTime();

		if (Groggy_Loop_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Stun_01_Left", false);
			Groggy_Loop_Check = false;
		}
		if (Groggy_Loop_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Stun_01_Right", false);
			Groggy_Loop_Check = false;
		}

		if (Groggy_Loop_Timing > 3.0f)
			mState = eVesselState::GroggyEnd;
	}

	void PureVessel::Groggy_End()
	{
		mState = eVesselState::GroggyEnd;

		if (Groggy_End_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Stun_02_Left", true);
			Groggy_End_Check = false;
		}
		if (Groggy_End_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Stun_02_Right", true);
			Groggy_End_Check = false;
		}
	}

	void PureVessel::Roar_Tele_In()
	{
		mState = eVesselState::RoarTeleIn;

		if (Roar_Tele_In_Check)
			mDirection = Live_Direction;

		if (Roar_Tele_In_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Roar_Tele_On_Left", true);
			Roar_Tele_In_Check = false;

			if (RoarLocationCounter == 0)
			{
				mTransform->SetPosition(Vector3(0.0f, -0.125f, 0.0f));
				RoarLocationCounter++;
			}
			else if (RoarLocationCounter == 1)
			{
				mTransform->SetPosition(Vector3(0.5f, -0.125f, 0.0f));
				RoarLocationCounter++;
			}
			else if (RoarLocationCounter == 2)
			{
				mTransform->SetPosition(Vector3(-0.5f, -0.125f, 0.0f));
				RoarLocationCounter++;
			}
			else if (RoarLocationCounter == 3)
			{
				mTransform->SetPosition(Vector3(-0.8f, -0.125f, 0.0f));
				RoarLocationCounter++;
			}
			else if (RoarLocationCounter == 4)
			{
				mTransform->SetPosition(Vector3(0.8f, -0.125f, 0.0f));
				RoarLocationCounter = 0;
			}
		}

		if (Roar_Tele_In_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Roar_Tele_On_Right", true);
			Roar_Tele_In_Check = false;

			if (RoarLocationCounter == 0)
			{
				mTransform->SetPosition(Vector3(0.0f, -0.125f, 0.0f));
				RoarLocationCounter++;
			}
			else if (RoarLocationCounter == 1)
			{
				mTransform->SetPosition(Vector3(0.5f, -0.125f, 0.0f));
				RoarLocationCounter++;
			}
			else if (RoarLocationCounter == 2)
			{
				mTransform->SetPosition(Vector3(-0.5f, -0.125f, 0.0f));
				RoarLocationCounter++;
			}
			else if (RoarLocationCounter == 3)
			{
				mTransform->SetPosition(Vector3(-0.8f, -0.125f, 0.0f));
				RoarLocationCounter++;
			}
			else if (RoarLocationCounter == 4)
			{
				mTransform->SetPosition(Vector3(0.8f, -0.125f, 0.0f));
				RoarLocationCounter = 0;
			}
		}
	}

	void PureVessel::Roar_On()
	{
		mState = eVesselState::RoarOn;

		if (Roar_On_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Roar_On_Left", true);
			Roar_On_Check = false;
		}
		if (Roar_On_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Roar_On_Right", true);
			Roar_On_Check = false;
		}
	}

	void PureVessel::Roar_On_Loop()
	{
		mState = eVesselState::RoarOnLoop;
		Roar_On_Loop_Timing += Time::DeltaTime();

		if (Roar_On_Loop_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Roar_On_Loop_Left", true);
			Roar_On_Loop_Check = false;
		}
		if (Roar_On_Loop_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Roar_On_Loop_Right", true);
			Roar_On_Loop_Check = false;
		}

		if(Roar_On_Loop_Timing > 0.5f)
			mState = eVesselState::RoarStart;
	}

	void PureVessel::Roar_Start()
	{
		mState = eVesselState::RoarStart;

		if (Roar_Start_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Roar_Start_Left", true);
			Roar_Start_Check = false;
		}
		if (Roar_Start_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Roar_Start_Right", true);
			Roar_Start_Check = false;
		}
	}

	void PureVessel::Roar_Loop()
	{
		mState = eVesselState::RoarLoop;
		Roar_Loop_Timing += Time::DeltaTime();

		if (Roar_Loop_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Roar_Loop_Left", true);
			Roar_Loop_Check = false;
		}
		if (Roar_Loop_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Roar_Loop_Right", true);
			Roar_Loop_Check = false;
		}

		if(Roar_Loop_Timing > 1.0f)
			mState = eVesselState::RoarEnd;
	}

	void PureVessel::Roar_End()
	{
		mState = eVesselState::RoarEnd;

		if (Roar_End_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Roar_End_Left", true);
			Roar_End_Check = false;
		}
		if (Roar_End_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Roar_End_Right", true);
			Roar_End_Check = false;
		}
	}


	void PureVessel::Dark_Tentacle_Tele_In()
	{
		mState = eVesselState::DarkTentacleTeleIn;

		if (DarkTentacle_Tele_In_Check)
			mDirection = Live_Direction;

		if (DarkTentacle_Tele_In_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Tentacle_Tele_On_Left", true);
			DarkTentacle_Tele_In_Check = false;

			if (mPlayerPos.x < 0.241f)
			{
				mTransform->SetPosition(Vector3(mPlayerPos.x + 0.7f, -0.125f, 0.0f));
			}
		}

		if (DarkTentacle_Tele_In_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Tentacle_Tele_On_Right", true);
			DarkTentacle_Tele_In_Check = false;

			if (mPlayerPos.x > -0.493f)
			{
				mTransform->SetPosition(Vector3(mPlayerPos.x - 0.7f, -0.125f, 0.0f));
			}
		}
	}

	void PureVessel::Dark_Tentacle_On()
	{
		mState = eVesselState::DarkTentacleOn;

		if (DarkTentacle_On_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Tentacle_On_Left", true);
			DarkTentacle_On_Check = false;
		}
		if (DarkTentacle_On_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Tentacle_On_Right", true);
			DarkTentacle_On_Check = false;
		}
	}

	void PureVessel::Dark_Tentacle_Start()
	{
		mState = eVesselState::DarkTentacleStart;

		if (DarkTentacle_Start_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Tentacle_Start_Left", true);
			DarkTentacle_Start_Check = false;
		}
		if (DarkTentacle_Start_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Tentacle_Start_Right", true);
			DarkTentacle_Start_Check = false;
		}
	}

	void PureVessel::Dark_Tentacle_Loop()
	{
		mState = eVesselState::DarkTentacleLoop;
		DarkTentacle_Loop_Timing += Time::DeltaTime();

		if (DarkTentacle_Loop_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Tentacle_Loop_Left", true);
			DarkTentacle_Loop_Check = false;
		}
		if (DarkTentacle_Loop_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Tentacle_Loop_Right", true);
			DarkTentacle_Loop_Check = false;
		}

		if(DarkTentacle_Loop_Timing > 1.0f)
			mState = eVesselState::DarkTentacleEnd;
	}

	void PureVessel::Dark_Tentacle_End()
	{
		mState = eVesselState::DarkTentacleEnd;

		if (DarkTentacle_End_Check && mDirection == eDirection::Left)
		{
			mAnimation->PlayAnimation(L"Tentacle_End_Left", true);
			DarkTentacle_End_Check = false;
		}
		if (DarkTentacle_End_Check && mDirection == eDirection::Right)
		{
			mAnimation->PlayAnimation(L"Tentacle_End_Right", true);
			DarkTentacle_End_Check = false;
		}
	}

	void PureVessel::Tele_Out()
	{
		mState = eVesselState::TeleOut;
		mTransform->SetScale(Vector3(0.9f, 0.9f, 0.0f));

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

		Intro_Idle_Timing        = 0.0f;
		Intro01_Timing           = 0.0f;
		Intro02_Timing           = 0.0f;
		Intro06_Timing           = 0.0f;
		Groggy_Loop_Timing       = 0.0f;
		Dash_On_Timing           = 0.0f;
		Knife_Spike_Loop_Timing  = 0.0f;
		Knife_Spread_Loop_Timing = 0.0f;
		DarkTentacle_Loop_Timing = 0.0f;
		Roar_On_Loop_Timing      = 0.0f;
		Roar_Loop_Timing         = 0.0f;

		Intro_Idle_Check = true;
		Intro_00_Check   = true;
		Intro_01_Check   = true;
		Intro_02_Check   = true;
		Intro_03_Check   = true;
		Intro_04_Check   = true;
		Intro_05_Check   = true;
		Intro_06_Check   = true;
		Intro_End_Check  = true;

		Idle_Check         = true;
		Tele_Out_Check     = true;
		Groggy_Start_Check = true;
		Groggy_Loop_Check  = true;
		Groggy_End_Check   = true;

		Counter_Cast_Check = true;
		Counter_Loop_Check = true;
		Counter_End_Check  = true;

		Dash_Tele_In_Check = true;
		Dash_On_Check      = true;
		Dash_Shoot_Check   = true;
		Dash_End_Check     = true;

		Knife_Spike_Tele_In_Check = true;
		Spike_On_Check            = true;
		Spike_Start_Check         = true;
		Spike_Loop_Check          = true;
		Spike_End_Check           = true;

		Slash_Tele_In_Check = true;
		Slash_On_Check      = true;
		Slash_00_Check      = true;
		Slash_01_Check      = true;
		Slash_02_Check      = true;
		Slash_03_Check      = true;
		Slash_04_Check      = true;
		Slash_05_Check      = true;
		Slash_End_Check     = true;

		DartShoot_Tele_In_Check = true;
		Spread_On_Check         = true;
		Spread_Start_Check      = true;
		Spread_Loop_Check       = true;
		Spread_End_Check        = true;

		DarkTentacle_Tele_In_Check = true;
		DarkTentacle_On_Check      = true;
		DarkTentacle_Start_Check   = true;
		DarkTentacle_Loop_Check    = true;
		DarkTentacle_End_Check     = true;

		Roar_Tele_In_Check = true;
		Roar_On_Check      = true;
		Roar_On_Loop_Check = true;
		Roar_Start_Check   = true;
		Roar_Loop_Check    = true;
		Roar_End_Check     = true;
	}

	void PureVessel::Death()
	{

	}

}