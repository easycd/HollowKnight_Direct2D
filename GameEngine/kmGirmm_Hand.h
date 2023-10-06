#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class Girmm_Hand : public GameObject
	{
	public:
		Girmm_Hand();
		virtual ~Girmm_Hand();

		virtual void Initialize() override;
		virtual void Update() override;

		void Hand_Out();
		void Hand_Click();
		void Hand_Click_Idle();
		void Hand_In();

		void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;

		float mTime;

	private:
		bool mHand_Out_Check = false;
		bool mHand_Click_Check = false;
		bool mHand_In_Check = false;
	};
}

