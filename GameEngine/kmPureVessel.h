#pragma once
#include "kmGameObject.h"

namespace km
{
	class Player;
	
	class Spike;
	class DarkWhip;
	class LightCircle;
	class LightCircleobj_Guid;
	class GuidLight;

	class Dark_Tentacle_Effect;

	class AudioSource;

	class PureVessel : public GameObject
	{
	public:
		PureVessel();
		~PureVessel();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		enum class eVesselState
		{
			IntroIdle,
			Intro00,
			Intro01,
			Intro02,
			Intro03,
			Intro04,
			Intro05,
			Intro06,
			IntroEnd,
			Pattern,
			Idle,
			CounterCast,
			CounterLoop,
			CounterEnd,
			DashTeleIn,
			DashOn,
			DashShoot,
			DashEnd,
			KnifeSpikeTeleIn,
			KnifeSpikeOn,
			KnifeSpikeStart,
			KnifeSpikeLoop,
			KnifeSpikeEnd,
			SlashTeleIn,
			SlashOn,
			Slash00,
			Slash01,
			Slash02,
			Slash03,
			Slash04,
			Slash05,
			SlashEnd,
			KnifeSpreadTeleIn,
			KnifeSpreadOn,
			KnifeSpreadStart,
			KnifeSpreadLoop,
			KnifeSpreadEnd,
			GroggyStart,
			GroggyLoop,
			GroggyEnd,
			RoarTeleIn,
			RoarOn,
			RoarOnLoop,
			RoarStart,
			RoarLoop,
			RoarEnd,
			RoarIdle,
			DarkTentacleTeleIn,
			DarkTentacleOn,
			DarkTentacleStart,
			DarkTentacleLoop,
			DarkTentacleEnd,
			TeleOut,
			TeleOutState,
			Death,
		};

		enum class eDirection
		{
			Left,
			Right
		};

	public:
		void Intro_Idle();
		void Intro_00();
		void Intro_01();
		void Intro_02();
		void Intro_03();
		void Intro_04();
		void Intro_05();
		void Intro_06();
		void Intro_End();

		void Pattern();

		void Idle();

		void Counter_Cast();
		void Counter_Loop();
		void Counter_End();

		void Dash_Tele_In();
		void Dash_On();
		void Dash_Shoot();
		void Dash_End();
		 
		void Knife_Spike_Tele_In();
		void Knife_Spike_On();
		void Knife_Spike_Start();
		void Knife_Spike_Loop();
		void Knife_Spike_End();

		void Slash_Tele_In();
		void Slash_On();
		void Slash_00();
		void Slash_01();
		void Slash_02();
		void Slash_03();
		void Slash_04();
		void Slash_05();
		void Slash_End();

		void Knife_Spread_Tele_In();
		void Knife_Spread_On();
		void Knife_Spread_Start();
		void Knife_Spread_Loop();
		void Knife_Spread_End();

		//2 Pase
		void Groggy_Start();
		void Groggy_Loop();
		void Groggy_End();

		void Roar_Tele_In();
		void Roar_On();
		void Roar_On_Loop();
		void Roar_Start();
		void Roar_Loop();
		void Roar_End();
		void Roar_Idle();

		void Dark_Tentacle_Tele_In();
		void Dark_Tentacle_On();
		void Dark_Tentacle_Start();
		void Dark_Tentacle_Loop();
		void Dark_Tentacle_End();

		void Tele_Out();
		void Tele_Out_State();
		void Death();

		void SpikeObj();
		void CircleObj();
		void GuidLightObj();


	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		Rigidbody* mRigidbody;
		Player* mPlayer;

		eVesselState mState;
		eDirection Live_Direction;
		eDirection mDirection;

		Vector3 mPlayerPos;
		Vector3 mVesselPos;
		VectorR mPlayer_Direction;
		VectorR mGrimm_Direction;
		VectorR dr;
		int mPattern;
		bool Wall_Check = false;

	private:
		AudioSource* mBGM;
		AudioSource* mSlash_01;
		AudioSource* mSlash_02;
		AudioSource* mSlash_03;
		AudioSource* mDark_tentacle_On;
		AudioSource* mDark_tentacle_Start;
		AudioSource* mDash_On;
		AudioSource* mCircle_Burst;
		AudioSource* mRoar_On;
		AudioSource* mRoar_Focus;
		AudioSource* mSpikeAttack_On;
		AudioSource* mTele_In;


	private:
		Dark_Tentacle_Effect* mDark_Tentacle_Effect;

	private:
		DarkWhip* mDarkWhip_Up;
		DarkWhip* mDarkWhip_Down;

		Spike* mSpike00;
		Spike* mSpike01;
		Spike* mSpike02;
		Spike* mSpike03;
		Spike* mSpike04;
		Spike* mSpike05;
		Spike* mSpike06;
		Spike* mSpike07;
		Spike* mSpike08;
		Spike* mSpike09;
		Spike* mSpike10;
		Spike* mSpike11;
		Spike* mSpike12;

		LightCircleobj_Guid* mCircle_Guid00;
		LightCircleobj_Guid* mCircle_Guid01;
		LightCircleobj_Guid* mCircle_Guid02;
		LightCircleobj_Guid* mCircle_Guid03;
		LightCircleobj_Guid* mCircle_Guid04;
		LightCircleobj_Guid* mCircle_Guid05;
		LightCircleobj_Guid* mCircle_Guid06;
		LightCircleobj_Guid* mCircle_Guid07;

		GuidLight* mGuidLight00;
		GuidLight* mGuidLight01;
		GuidLight* mGuidLight02;
		GuidLight* mGuidLight03;
		GuidLight* mGuidLight04;

	private:
		Vector3 Temp_Pos;
		int RoarLocationCounter;

	private:
		float Pattern_Timing;

		float Intro_Idle_Timing;
		float Intro01_Timing;
		float Intro02_Timing;
		float Intro06_Timing;
		float Dash_On_Timing;
		float Knife_Spike_Loop_Timing;
		float Knife_Spread_Loop_Timing;
		float Groggy_Loop_Timing;
		float DarkTentacle_Loop_Timing;
		float Roar_On_Loop_Timing;
		float Roar_Loop_Timing;
		float Roar_Idle_Timing;

	private:
		bool Intro_Idle_Check = true;
		bool Intro_00_Check   = true;
		bool Intro_01_Check   = true;
		bool Intro_02_Check   = true;
		bool Intro_03_Check   = true;
		bool Intro_04_Check   = true;
		bool Intro_05_Check   = true;
		bool Intro_06_Check   = true;
		bool Intro_End_Check  = true;

	private:
		bool Idle_Check         = true;
		bool Tele_Out_Check     = true;
		bool Groggy_Start_Check = true;
		bool Groggy_Loop_Check  = true;
		bool Groggy_End_Check   = true;

		bool Counter_Cast_Check = true;
		bool Counter_Loop_Check = true;
		bool Counter_End_Check  = true;

		bool Dash_Tele_In_Check = true;
		bool Dash_On_Check      = true;
		bool Dash_Shoot_Check   = true;
		bool Dash_End_Check     = true;

		bool Knife_Spike_Tele_In_Check = true;
		bool Spike_On_Check            = true;
		bool Spike_Start_Check         = true;
		bool Spike_Loop_Check          = true;
		bool Spike_End_Check           = true;

		bool Slash_Tele_In_Check = true;
		bool Slash_On_Check      = true;
		bool Slash_00_Check      = true;
		bool Slash_01_Check      = true;
		bool Slash_02_Check      = true;
		bool Slash_03_Check      = true;
		bool Slash_04_Check      = true;
		bool Slash_05_Check      = true;
		bool Slash_End_Check     = true;

		bool DartShoot_Tele_In_Check = true;
		bool Spread_On_Check         = true;
		bool Spread_Start_Check      = true;
		bool Spread_Loop_Check       = true;
		bool Spread_End_Check        = true;

		bool DarkTentacle_Tele_In_Check = true;
		bool DarkTentacle_On_Check      = true;
		bool DarkTentacle_Start_Check   = true;
		bool DarkTentacle_Loop_Check    = true;
		bool DarkTentacle_End_Check     = true;

		bool Roar_Tele_In_Check = true;
		bool Roar_On_Check      = true;
		bool Roar_On_Loop_Check = true;
		bool Roar_Start_Check   = true;
		bool Roar_Loop_Check    = true;
		bool Roar_End_Check     = true;
		bool Roar_Idle_Check    = true;
	};
}


