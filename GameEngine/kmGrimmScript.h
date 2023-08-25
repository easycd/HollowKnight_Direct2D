#pragma once
#include <kmScript.h>

namespace km
{
	class GrimmScript : public Script
	{
	public:
		enum class eGrimmState
		{
			Idle,
			AirDashOn,
			AirDashStart,
			AirDashLoop,
			AirDashLand,
			AirDashAttack,
			AirDashStop,
			BalloonStart,
			BalloonLoop,
			CapSpikeOn,
			CapSpikeLoop,
			CapSpikeEnd,
			Cast,
			SlashOn,
			Slash,
			UpSlash,
			Tele_In,
			Tele_Out,
			Death,
			End,
		};

		enum class eDirection
		{
			Left,
			Right
		};

		GrimmScript();
		~GrimmScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	public:
		void Idle();
		void AirDash_On();
		void AirDash_Start();
		void AirDash_Loop();
		void AirDash_Land();
		void AirDash_Attack();
		void AirDash_Stop();
		void Balloon_Start();
		void Balloon_Loop();
		void Capspike_On();
		void Capspike_Loop();
		void Capspike_End();
		void Cast();
		void Slash_On();
		void Slash();
		void Up_Slash();
		void Tele_In();
		void Tele_Out();
		void Death();

	private:
		eGrimmState mState;
		eDirection mDirection;
		Animator* mAnimation;
		Transform* mTransform;
		Rigidbody* mRigidbody;
		Vector3 mPlayerPos;
		GameObject sm;

		PlayerScript* mPlayer;

		float mTime;
		bool Test;

	private:
		bool Idle_Check = true;
		bool AirDash_Start_Check = true;
	};
}

