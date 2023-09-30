#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class AirDash_Effect : public GameObject
	{
	public:
		AirDash_Effect();
		virtual ~AirDash_Effect();

		virtual void Initialize();
		virtual void Update();

		void PlayEffect();
		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;

	};

}

