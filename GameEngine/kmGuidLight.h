#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class GuidLight : public GameObject
	{
		GuidLight();
		virtual ~GuidLight();

		virtual void Initialize();
		virtual void Update();

		void On();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		bool On_Check = true;
	};
}


