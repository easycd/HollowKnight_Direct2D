#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class GroundDash_Effect : public GameObject
	{
	public:
		GroundDash_Effect();
		virtual ~GroundDash_Effect();

		virtual void Initialize();
		virtual void Update();

		void PlayEffect_Left();
		void PlayEffect_Right();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
	};
}

