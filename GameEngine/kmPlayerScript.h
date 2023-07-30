#pragma once
#include <kmScript.h>

namespace km
{
	class Rigidbody;

	class PlayerScript : public Script
	{
	public:

		enum class PlayerState
		{
			Idle,
			Move,
			Jump,
			Dash,
			Attack,
		};
		PlayerScript();
		~PlayerScript();


		virtual void Initialize() override;
		virtual void Update() override;

		void Complete();

		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

	private:
		PlayerState mState;
		Rigidbody* mRigidbody;
		Animator* at;
		Transform* tr;
		Vector3 pos;

		VectorR velocity;
		int direction = 0; //0이면 왼쪽 1이면 오른쪽



	private:
		void Idle();
		void Move();
		void Jump();
		void Dash();
		void Attack();
	};
}

