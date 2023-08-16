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
		Vector3 mPos;

		float mTime;
		bool Test;

	};
}

