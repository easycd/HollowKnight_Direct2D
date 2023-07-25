#pragma once
#include "kmComponent.h"

namespace km
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetMass(float mass) { mMass = mass; } // 질량 셋팅 함수
		void AddForce(Vector2 force); // 힘을 증가해줄수 있는 함수
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		Vector2 GetVelocity() { return mVelocity; }

	private:
		float mMass; //질량
		Vector2 mForce; //물체를 이동시키는 힘
		Vector2 mAccelation; //가속도
		Vector2 mVelocity; //속도
		Vector2 mVelocity2;
		Vector2 mGravity; //중력
		Vector2 mLimitedVelocity;

		bool mbGround; //땅에 붙었는지 안붙었는지 체크
		float mFriction; //마찰력

		//float mStaticFriction; //정지마찰력
		//float mKineticFriction; //운동마찰력
		//float mCoefficientFriction; //마찰력 계수
		//float mNormalForce; 
	};
}
