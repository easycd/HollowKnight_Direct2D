#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class RoarEffect : public GameObject
	{
	public:
		RoarEffect();
		virtual ~RoarEffect();

		virtual void Initialize();
		virtual void Update();

		void Roar_Effect_On();
		void Roar_Effect_Start();
		void Roar_Effect_End();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		bool Roar_Effect_On_Check    = true;
		bool Roar_Effect_Start_Check = true;
		bool Roar_Effect_End_Check   = true;
	};
}

