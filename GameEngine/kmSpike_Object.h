#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class Spike_Object : public GameObject
	{
	public:
		Spike_Object();
		virtual ~Spike_Object();

		virtual void Initialize();
		virtual void Update();

		void Spike_On_Delay();
		void Spike_On();
		void Spike_Shot();
		void Spike_Loop();
		void Spike_Remove();
		void Spike_End();
		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		float mSpike_On_Delay;
		float mSpike_Loop_Delay;

	private:
		bool Spike_On_Delay_Time_Check = false;
		bool Spike_Loop_Delay_Time_Check = false;

	private:
		bool Spike_On_Delay_Check = true;
		bool Spike_On_Check       = true;
		bool Spike_Shot_Check     = true;
		bool Spike_Loop_Check     = true;
		bool Spike_Remove_Check   = true;
		bool Spike_End_Check      = true;
	};
}
