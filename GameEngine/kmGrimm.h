#pragma once
#include "kmGameObject.h"

namespace km
{
	class Player;

	class Spike_Object;
	class FlameBat;
	class FIreBall;

	class AirDash_Effect;
	class GroundDash_Effect;

	class Grimm : public GameObject
	{
	public:
		enum class ePatternState
		{
			Pattern,
			DisPattern,
		};

		enum class ePatternType
		{
			AirDash,
			Balloon,
			CapSpike,
			Cast,
			Slash,
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
		void Tele_In();
		void Tele_In_State();
		void Tele_Out();
		void Tele_Out_State();
		void AirDash_Loop_Move();
		void Death();
		void Check();

		//Object 생성클래스
		void Spike_Obj();
		void FireBall_Obj();

	private:
		ePatternState mPattern_State;
		ePatternType mPatternType;
		eGrimmState mState;
		eDirection mDirection;
		eDirection mGetDirection;

		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		Rigidbody* mRigidbody;
		GameObject sm;

		Player* mPlayer;
		Vector3 mGrimm_Live_Pos;
		Vector3 mGrimmPos;
		Vector3 mPlayerPos;
		Vector3 mGetPlayerPos;
		Vector3 mGetGimmPos;

		VectorR mPlayer_Direction;
		VectorR mGrimm_Direction;
		VectorR dr;
		VectorR Dash_Locate;

		int attack_pattern;

		bool Test;
		bool Ground_Check = false;
		bool Wall_Check = false;
		bool Pattern_Start = false;

	private:
		bool Spike_Object_Check = false;

	private:
		bool AirDash_Loop_Move_Check = false;
		bool AirDash_Attack_Move_Check = false;
		bool Slash_Move_Check = false;

	private:
		bool Pattern_Delay_Check = true;
		bool Balloon_Loop_Delay_Check = false;
		bool CapSpike_Loop_Delay_Check = false;
		bool Cast_Loop_Delay_Check = false;
		bool Slash_On_Delay_Check = false;
		bool Cast_Delay_Check = false;

	private:
		int AirDash_On_Location;
		int Slash_On_Location;

	private:
		float mTime;
		float Pattern_Delay;
		float AirDash_Attack_Delay;
		float Balloon_Loop_Delay;
		float CapSpike_Loop_Delay;
		float Cast_Loop_Delay;
		float Slash_On_Delay;
		float Cast_Delay;


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
        bool Death_Check               = true;
		bool AirDash_Tele_In_Check     = true;
		bool Balloon_Tele_In_Check     = true;
		bool Capspike_Tele_In_Check    = true;
		bool Cast_Tele_In_Check        = true;
		bool Slash_Tele_In_Check       = true;

		//SpikeObj
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

	private:
		float FlameBat_Delay;
		bool FlameBat_Obj_Play = false;
		bool Bat0_Play = true;;
		bool Bat1_Play = false;
		bool Bat2_Play = false;

		float FireBall_Delay_time;

		//Effect
	private:
		AirDash_Effect* mAirDash_Effect;
		GroundDash_Effect* mGroundDash_Effect;
		bool mAirDash_Effect_Check = true;
	};
}

