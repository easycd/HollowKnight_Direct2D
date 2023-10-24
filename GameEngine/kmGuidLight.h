#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class GuidLight : public GameObject
	{
	public:
		GuidLight();
		virtual ~GuidLight();

		virtual void Initialize();
		virtual void Update();

		void GuidLight_00();
		void GuidLight_01();
		void GuidLight_02();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		bool GuidLight_00_Check = true;
		bool GuidLight_01_Check = true;
		bool GuidLight_02_Check = true;
		float Move_Timing;
	};
}


