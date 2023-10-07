#pragma once
#include "kmGameObject.h"

namespace km
{
	class Rigidbody;
	class RigidbodyMath;
	
	class PlayerEffet;
	class DoubleJump_Effect;
	class DsahEffect;
	class FireBallSkill_Effect;
	class Focus_Effect;
	class Focus_On_Effect;

	class AudioSource;

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
			Skill,
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

		int GetPlayerHP() { return mPlayerHP_State; }
		bool GetPlayerHPState() { return HPState; }

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		ePlayerState mState;
		Rigidbody* mRigidbody;
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		Vector3 mPlayerPos;
		Vector3 mSavePos;

		VectorR velocity;
		eDirection mDirection;
		float mTime;

		int mPlayerHP_State;
		bool HPState = true;

	private:
		PlayerEffet* mSlash_Effect;
		PlayerEffet* mUpSlash_Effect;
		PlayerEffet* mDownSlash_Effect;
		DoubleJump_Effect* mDoubleJump_Effect;
		DsahEffect* mDash_Effect;
		FireBallSkill_Effect* Skill_Effect;
		Focus_Effect* mFocus_Effect;
		Focus_On_Effect* mFocus_On_Effect;

	private:
		bool Dash_Left_Check = false;
		bool Dash_Right_Check = false;
		bool Fall_Dash_Check = false; //Fall 상태에서 방향키 + Dash 버튼 누르면 이동하는거랑 겹치기 때문에 bool 함수로 잠금 
		bool Jump_Delay = false;
		bool DoubleJump_Delay = false;

		bool Ground_Check = false;
		bool Fall_Delay = false;
		bool Fall_Ani_Check = true;

		bool Walk_Sound_Loop = false;
		bool Walk_Check = false;

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
		void Skill();

		void FocusStart();
		void Focus();
		void FocusOn();
		void FocusEnd();
		
		
		void Jump_End();
		void DoubleJump_End();
		void Dash_End();
		void Attack_End();
		void Skill_End();
		void FocusEnd_End();

		void Death();

	private:
		bool Idle_Check        = false;
		bool Move_Check		   = false;
		bool Jump_Check		   = true;
		bool Double_Jump_Check = true;
		bool Dash_Check		   = true;
		bool Fall_Check		   = false;
		bool UpAttack_Check	   = true;
		bool Attack_Check	   = true;
		bool DownAttack_Check  = true;
		bool Skill_Check       = true;
		bool Focus_Start_Check = true;
		bool Focus_Check       = true;
		bool Focus_On_Check    = true;
		bool Focus_End_Check   = true;

	private:

		

	private:
		AudioSource* mWalkSound;
		AudioSource* mJumpSound;
		AudioSource* mDoubleJump;
		AudioSource* mLandSound;
		AudioSource* mDash;
		AudioSource* mSlash;
		AudioSource* mDownSlash;
		AudioSource* mUpSlash;
		AudioSource* mFireBall;

	};
}