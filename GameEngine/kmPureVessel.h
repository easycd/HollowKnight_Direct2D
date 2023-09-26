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

		enum class ePatternType
		{
			Counter,
			Dash,
			Knife_Spike,
			Slash,
			Knife_Spread,
			Circle_Attack,
			Dark_Teneacle,
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

		void Dash_On();
		void Dash_Shoot();
		void Dash_End();

		void Knife_Spike();
		void Slash();
		void Knife_Spread();

		//2 Pase
		void Groggy();
		void Circle_Attack();
		void Dark_Tentacle();

		void Tele_Out();
		void Tele_Out_State();
		void Tele_In();


	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		Rigidbody* mRigidbody;
		Player* mPlayer;
		eDirection Live_Direction;
		eDirection mDirection;
		Vector3 mPlayerPos;
		Vector3 mVesselPos;
		VectorR mPlayer_Direction;
		VectorR mGrimm_Direction;
		VectorR dr;
		int mPattern;

	private:
		float IntroStart;
		float Intro02_Start;
		float Intro03_Start;
		float Intro_End_Start;

	private:
		float Counter_Loop_Delay;
		bool Dash_Move_Check = false;

	private:
		bool IntroStart_Check = true;
		bool Intro_02_Start_Check = false;
		bool Intro_03_Start_Check = false;
		bool Intro_End_Check = false;
		bool Intro_Idle_Check = true;

	private:
		bool Idle_Check = true;
		bool Counter_Cast_Check = true;
		bool Counter_Loop_Check = true;
		bool Counter_End_Check = true;
		bool Dash_On_Check = true;
		bool Dash_Shoot_Check = true;
		bool Dash_End_Check = true;


		bool Tele_In_Check = true;
		bool Tele_Out_Check = true;

	};
}


