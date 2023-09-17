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
		virtual void OnCollisionEnter(Collider2D* other) override;
		virtual void OnCollisionStay(Collider2D* other) override;
		virtual void OnCollisionExit(Collider2D* other) override;

		void On_Left();
		void On_Right();
		void Loop();
		void Destroy();

		void SetDirection(int mdirection) { mGetDir = mdirection; }

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
		int mGetDir;
		int mDirection;
		int mLoopDr;
		float mExport_Timing;
	};
}


