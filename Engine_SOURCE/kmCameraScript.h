#pragma once
#include <kmScript.h>

namespace km
{
	class CameraScript : public Script
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;

		void SetTarget(GameObject* target) { mTarget = target; }
		void SetWeight(Vector2 weight) { mWeight = weight; }
		void SetHight(float hight) { mHight = hight; }


	private:
		GameObject* mTarget;
		Transform* mTransfrom;
		Transform* mTargetPos;
		Vector3 mPos;
		Vector3 PlayerPos;

		Vector2 mWeight;
		float mHight;
		bool mFirstSet = true;

	};
}
