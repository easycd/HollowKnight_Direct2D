#pragma once
#include "kmGameObject.h"

namespace km
{
	class Rigidbody;
	class RigidbodyMath;
	class PlayerEffet;

	class Player : public GameObject
	{
	public:
		enum class ePlayerState
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
			ShootBall,
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

		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Complete();
		Vector3 GetPlayerPos() { return mPlayerPos; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		ePlayerState mState;
		Rigidbody* mRigidbody;
		Animator* mAnimation;
		Transform* mTransform;
		Vector3 mPlayerPos;

		VectorR velocity;
		eDirection mDirection; //0�̸� ���� 1�̸� ������
		float mTime;

	private:
		PlayerEffet* mSlash_Effect;
		PlayerEffet* mUpSlash_Effect;
		PlayerEffet* mDownSlash_Effect;

	private:
		bool Dash_Left_Check = false;
		bool Dash_Right_Check = false;

		bool Ground_Check = false;
		bool Fall_Ani_Check = true;
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

		//void FocusStart();
		//void Focus();
		//void FocusOn();
		//void FocusEnd();
		//
		
		void Jump_End();
		void DoubleJump_End();
		void Dash_End();
		void UpAttack_End();
		void Attack_End();
		void DownAttack_End();

		//void Death();

	private:
		bool Idle_Check        = false;
		bool Move_Check		   = false;
		bool Jump_Check		   = false;
		bool Double_Jump_Check = false;
		bool Dash_Check		   = false;
		bool Fall_Check		   = false;
		bool UpAttack_Check	   = false;
		bool Attack_Check	   = false;
		bool DownAttack_Chekc  = false;
	};
}