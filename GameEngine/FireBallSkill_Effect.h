#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;

	class FireBallSkill_Effect : public GameObject
	{
	public:
		FireBallSkill_Effect();
		virtual ~FireBallSkill_Effect();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void FireBallSkill_Left();
		virtual void FireBallSkill_Right();

		void Destroy();

	private:
		Player* mPlayer;
		Animator* mAnimation;
		Transform* mTransform;

		Vector3 mPlayerPos;
		float mTime;

		bool Left_Check = false;
		bool Right_Check = false;
	};

}
