#pragma once
#include "kmGameObject.h"

namespace km
{
	class Player;
	class Animator;

	class Spike_Object;
	class FlameBat;
	class FIreBall;

	class AirDash_Effect;
	class GroundDash_Effect;

	class Grimm : public GameObject
	{
	public:
		enum class eDirection
		{
			Left,
			Right
		};

		enum class eGrimmState
		{
			Pattern,
			Idle,
			AirDashTeleIn,
			AirDashStart,
			AirDashLoop,
			AirDashLand,
			AirDashAttack,
			AirDashStop,
			BalloonTeleIn,
			BalloonStart,
			BalloonLoop,
			CapSpikeTeleIn,
			CapSpikeOn,
			CapSpikeLoop,
			CapSpikeEnd,
			CastTeleIn,
			Cast,
			SlashTeleIn,
			SlashOn,
			Slash,
			UpSlashReady,
			UpSlash,
			Tele_In,
			Tele_Out,
			Tele_Out_End,
			Death,
		};

		Grimm();
		virtual ~Grimm();

		virtual void Initialize() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		virtual void Update() override;

	public:
		void Pattern();
		void Tele_In();
		void Tele_Out();
		void Tele_Out_End();
		void Intro();
		void Idle();

		void AirDash_Tele_In();
		void AirDash_Start();
		void AirDash_Loop();
		void AirDash_Land();
		void AirDash_Attack();
		void AirDash_Stop();

		void Balloon_Tele_In();
		void Balloon_Start();
		void Balloon_Loop();

		void Capspike_Tele_In();
		void Capspike_On();
		void Capspike_Loop();
		void Capspike_End();

		void Cast_Tele_In();
		void Cast();

		void Slash_Tele_In();
		void Slash_On();
		void Slash();
		void UP_Slash_Ready();
		void Up_Slash();

		void Death();

		void Spike_Obj();
		void FireBall_Obj();

	private:
		eGrimmState mState;
		eDirection mLive_Direction;
		eDirection mDirection;
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		Rigidbody* mRigidbody;

		Player* mPlayer;

		Vector3 mGrimmPos;
		Vector3 mPlayerPos;
		VectorR mPlayer_Direction;
		VectorR mGrimm_Direction;
		VectorR dr;
		VectorR Dash_Locate;

		bool Ground_Check = false;
		bool Wall_Check = false;

	private:
		int PatternState;
		int AirDash_On_Location;

		float Test = 0.0f;

		float mPattern_Timing;
		float Balloon_Loop_Delay;
		float FireBall_Delay_time;
		float CapSpike_Loop_Delay;
		float FlameBat_Delay;
		float Cast_Delay;
		float Slash_On_Delay;

		bool Bat0_Play = true;
		bool Bat1_Play = true;
		bool Bat2_Play = true;

	private:
		bool Idle_Check = true;
		bool Tele_Out_Check = true;

		bool AirDash_Tele_In_Check = true;
		bool AirDash_Start_Check = true;
		bool AirDash_Loop_Check = true;
		bool AirDash_Land_Check = true;
		bool AirDash_Attack_Check = true;
		bool AirDash_Stop_Check = true;

		bool Balloon_Tele_In_Check = true;
		bool Balloon_Start_Check = true;
		bool Balloon_Loop_Check = true;

		bool Capspike_Tele_In_Check = true;
		bool Capspike_On_Check = true;
		bool Capspike_Loop_Check = true;
		bool Capspike_End_Check = true;

		bool Cast_Tele_In_Check = true;
		bool Cast_Check = true;

		bool Slash_Tele_In_Check = true;
		bool Slash_On_Check = true;
		bool Slash_Check = true;
		bool UP_Slash_Ready_Check = true;
		bool Up_Slash_Check = true;

	private:
		Spike_Object* Spike0;
		Spike_Object* Spike1;
		Spike_Object* Spike2;
		Spike_Object* Spike3;
		Spike_Object* Spike4;
		Spike_Object* Spike5;
		Spike_Object* Spike6;
		Spike_Object* Spike7;
		Spike_Object* Spike8;
		Spike_Object* Spike9;
		Spike_Object* Spike10;
		Spike_Object* Spike11;
		Spike_Object* Spike12;

		//FlameBatObj
		FlameBat* Bat0;
		FlameBat* Bat1;
		FlameBat* Bat2;
	};
}

