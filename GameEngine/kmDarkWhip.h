#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class DarkWhip : public GameObject
	{
	public:
		DarkWhip();
		virtual ~DarkWhip();

		virtual void Initialize();
		virtual void Update();

		void DarkWhip_On_Up_Left();
		void DarkWhip_On_Up_Right();
		void DarkWhip_On_Down_Left();
		void DarkWhip_On_Down_Right();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		bool DarkWhip_On_Up_Left_Check    = true;
		bool DarkWhip_On_Up_Right_Check   = true;
		bool DarkWhip_On_Down_Left_Check  = true;
		bool DarkWhip_On_Down_Right_Check = true;
	};
}
