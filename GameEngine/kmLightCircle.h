#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class LightCircle : public GameObject
	{
	public:
		LightCircle();
		virtual ~LightCircle();

		virtual void Initialize();
		virtual void Update();

		void Circle_On();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		bool Circle_On_Check = true;
	};
}

