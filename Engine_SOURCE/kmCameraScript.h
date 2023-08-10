#pragma once
#include <kmScript.h>

namespace km
{
	class CameraScript : public Script
	{
	public:
		virtual void Update() override;

		void SetTarget(GameObject* target) { mTarget = target; }

	private:
		GameObject* mTarget;
	};
}
