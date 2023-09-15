#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class FIreBall : public GameObject
	{
	public:
		FIreBall();
		virtual ~FIreBall();

		virtual void Initialize();
		virtual void Update();
		virtual void Set0();
		virtual void Set1();
		virtual void Set2();
		virtual void Set3();
		virtual void Set4();
		virtual void Set5();
		virtual void Set6();
		virtual void Set7();
		virtual void Set8();

		virtual void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

		Vector3 Pos;
		float mTime;
	private:
		bool Set_Check0 = false;
		bool Set_Check1 = false;
		bool Set_Check2 = false;
		bool Set_Check3 = false;
		bool Set_Check4 = false;
		bool Set_Check5 = false;
		bool Set_Check6 = false;
		bool Set_Check7 = false;
		bool Set_Check8 = false;
	};
}
