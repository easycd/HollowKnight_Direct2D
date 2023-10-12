#pragma once
#include "kmGameObject.h"

namespace km
{
	class Player;

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
			KnifeSpike,
			SlashTeleIn,
			Slash,
			KnifeSpreadTeleIn,
			KnifeSpread,
			Groggy,
			CircleAttackTeleIn,
			CircleAttack,
			DarkTentacleTeleIn,
			DarkTentacle,
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
		void Knife_Spike();

		void Slash_Tele_In();
		void Slash();

		void Knife_Spread_Tele_In();
		void Knife_Spread();

		//2 Pase
		void Groggy();

		void Circle_Attack_Tele_In();
		void Circle_Attack();

		void Dark_Tentacle_Tele_In();
		void Dark_Tentacle();

		void Tele_Out();
		void Tele_Out_State();
		void Death();


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

	private:
		float Intro_Idle_Timing;
		float Intro01_Timing;
		float Intro02_Timing;
		float Intro06_Timing;

	private:
		bool Intro_Idle_Check = true;
		bool Intro_00_Check = true;
		bool Intro_01_Check = true;
		bool Intro_02_Check = true;
		bool Intro_03_Check = true;
		bool Intro_04_Check = true;
		bool Intro_05_Check = true;
		bool Intro_06_Check = true;
		bool Intro_End_Check = true;

	private:
		bool Idle_Check = true;
		bool Tele_Out_Check = true;

		bool Counter_Cast_Check = true;
		bool Counter_Loop_Check = true;
		bool Counter_End_Check = true;

		bool Dash_On_Check = true;
		bool Dash_Shoot_Check = true;
		bool Dash_End_Check = true;


	};
}


