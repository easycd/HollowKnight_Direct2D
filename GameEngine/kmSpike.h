#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class Spike : public GameObject
	{
	public:
		Spike();
		virtual ~Spike();

		virtual void Initialize();
		virtual void Update();

		void Spike_On();
		void Spike_End();

		void Destroy();
	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		bool Spike_On_Check  = true;
		bool Spike_End_Check = true;

		float Spike_On_Timing;
	};
}


