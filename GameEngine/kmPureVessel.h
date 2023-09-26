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

	public:
		void Intro_Idle();
		void Intro_00();
		void Intro_01();
		void Intro_02();
		void Intro_03();
		void Intro_04();
		void Intro_05();
		void Intro_06();

		void Pattern();

		void Idle();

		void Counter();
		void Dash();
		void Knife_Spike();
		void Slash();
		void Knife_Spread();

		//2 Pase
		void Groggy();
		void Circle_Attack();
		void Dark_tentacle();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		Rigidbody* mRigidbody;
		Player* mPlayer;

	private:
		float IntroStart;
		float Intro02_Start;
		float Intro03_Start;
		float Intro_End;

	private:
		bool IntroStart_Check = true;
		bool Intro_02_Start_Check = false;
		bool Intro_03_Start_Check = false;
		bool Intro_End_Check = false;
	};
}


