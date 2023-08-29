#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class FlameBat : public GameObject
	{
	public:
		FlameBat();
		virtual ~FlameBat();

		virtual void Initialize();
		virtual void Update();

		void On();
		void Loop();
		void Destroy();

		void SetDirection(int mdirection) { mDirection = mdirection; }

		void SetExportTiming(float mtime) { mExport_Timing = mtime; }

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

		Vector3 mFlamePos;
		float mTime;

	private:
		bool On_Check = true;
		bool Loop_Check = true;

	private:
		//사출 방향: 0 왼쪽 / 1 오른쪽
		int mDirection;
		float mExport_Timing;
	};
}


