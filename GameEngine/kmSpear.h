#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	
	class Spear : public GameObject
	{
	public:
		Spear();
		virtual ~Spear();

		virtual void Initialize();
		virtual void Update();

		void Spear_On();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		bool Spear_On_Check = true;
	};
}
