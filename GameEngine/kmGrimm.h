#pragma once
#include "kmGameObject.h"

namespace km
{
	class Player;
	class Grimm : public GameObject
	{
	public:
		enum class ePatternState
		{
			Pattern,
			DisPattern,
		};

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
			UpSlashReady,
			UpSlash,
			Tele_In,
			Tele_Out,
			AirDashMove,
			Death,
			End,
		};

		enum class eDirection
		{
			Left,
			Right
		};

		Grimm();
		~Grimm();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	public:
		void Pattern();
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
		void UP_Slash_Ready();
		void Up_Slash();
		void Tele_In();
		void Tele_Out();
		void AirDash_Loop_Move();
		void AirDash_Attack_Move();
		void Death();
		void Check();

	private:
		ePatternState mPattern_State;
		eGrimmState mState;
		eDirection mDirection;
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		Rigidbody* mRigidbody;
		GameObject sm;

		Player* mPlayer;
		Vector3 mGrimmPos;
		Vector3 mPlayerPos;

		VectorR mPlayer_Direction;
		VectorR mGrimm_Direction;
		VectorR dr;
		VectorR Dash_Locate;

		int attack_pattern;
		int mDr;
		float mTime;
		float AirDash_Attack_Delay;
		bool Test;
		bool Ground_Check = false;

	private:
		bool Idle_Check                = true;
		bool AirDash_On_Check          = true;
		bool AirDash_Start_Check       = true;
		bool AirDash_Loop_Check        = true;
		bool AirDash_Land_Check        = true;
		bool AirDash_Attack_Check      = true;
		bool AirDash_Stop_Check        = true;
		bool Balloon_Start_Check       = true;
		bool Balloon_Loop_Check        = true;
		bool Capspike_On_Check         = true;
		bool Capspike_Loop_Check       = true;
		bool Capspike_End_Check        = true;
		bool Cast_Check                = true;
		bool Slash_On_Check            = true;
		bool Slash_Check               = true;
		bool Up_Slash_Check            = true;
        bool Tele_In_Check             = true;
        bool Tele_Out_Check            = true;
		bool AirDash_Loop_Move_Check   = false;
		bool AirDash_Attack_Move_Check = false;
        bool Death_Check               = true;
	};
}

