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
		float Initialize_Timing;

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

	private:
		int Set_Check0_Count;
		int Set_Check1_Count;
		int Set_Check2_Count;
		int Set_Check3_Count;
		int Set_Check4_Count;
		int Set_Check5_Count;
		int Set_Check6_Count;
		int Set_Check7_Count;
		int Set_Check8_Count;
	};
}
