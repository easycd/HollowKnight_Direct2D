#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class Dark_Tentacle_Effect : public GameObject
	{
	public:
		Dark_Tentacle_Effect();
		virtual ~Dark_Tentacle_Effect();

		virtual void Initialize();
		virtual void Update();

		void On_Left();
		void On_Right();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;

	private:
		bool On_Left_Check = true;
		bool On_Right_Check = true;

		float Destroy_Time;
	};
}

