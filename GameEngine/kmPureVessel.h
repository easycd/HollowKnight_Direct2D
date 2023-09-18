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
	};
}


