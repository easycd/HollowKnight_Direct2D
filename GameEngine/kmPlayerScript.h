#pragma once
#include <kmScript.h>

namespace km
{
	class Rigidbody;
	class RigidbodyMath;
	class PlayerEffet;

	class PlayerScript : public Script
	{
	public:

		enum class PlayerState
		{
			Idle,
			Move,
			Jump,
			DoubleJump,
			Fall,
			Dash,
			UpAttack,
			Attack,
			DownAttack,
			FireBall,
			FocusStart,
			Focus,
			FocusOn,
			FocusEnd,
			Death,
			End,
		};

		enum class eDirection
		{
			Left,
			Right
		};

		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();
		Vector3 GetPlayerPos() { return pos; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;


	private:
		PlayerState mState;
		Rigidbody* mRigidbody;
		PlayerEffet* mEffect;
		Animator* at;
		Transform* tr;
		Vector3 pos;

		VectorR velocity;
		eDirection Direction; //0이면 왼쪽 1이면 오른쪽
		float mTime;
		bool Test = true;

	private:
		PlayerEffet* Effect;

	private:
		void Idle();
		void Move();
		void Jump();
		void DoubleJump();
		void Dash();
		void Fall();
		void UpAttack();
		void Attack();
		void DownAttack();
		void FocusStart();
		void Focus();
		void FocusOn();
		void FocusEnd();
		void Death();
		void ActionInitialize();

		void Up_Attack_End_Evnet();
		void Attack_End_Event();
		void Down_Attack_End_Event();
		void Jump_End_Event();
		void Double_Jump_End_Event();

	private:
		bool idle_Check        = false;
		bool jump_Check        = false;
		bool double_jump_Check = false;
		bool dash_jump_Check   = false;
		bool fall_Check        = false;
		bool up_attack_Check   = false;
		bool attack_Check      = false;
		bool down_attack_Check = false;

	};
}

