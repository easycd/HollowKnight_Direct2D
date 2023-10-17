#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class LightCircle;

	class LightCircleobj_Guid : public GameObject
	{
	public:
		LightCircleobj_Guid();
		virtual ~LightCircleobj_Guid();

		virtual void Initialize();
		virtual void Update();

		void Guid_On();
		void Guid_End();
		void Circle();

		void Destroy();

		void SetGuidEndTiming(float time) { mTime = time; }

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		Vector3 mPos;
	private:
		LightCircle* mCircle;

	private:
		bool Guid_On_Check  = true;
		bool Guid_End_Check = true;

		float mTime;
		float Guid_On_Timing;
	};
}
