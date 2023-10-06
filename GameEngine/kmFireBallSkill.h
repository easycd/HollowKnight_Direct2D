#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;

	class FireBallSkill : public GameObject
	{
	public:
		enum class eDirection
		{
			Left,
			Right
		};

		FireBallSkill();
		virtual ~FireBallSkill();

		virtual void Initialize();
		virtual void Update();

		void Left_On();
		void Right_On();
		void Left_Loop();
		void Right_Loop();

		virtual void Destroy();

	private:
		Animator* mAnimation;
		Transform* mTransform;
		Collider2D* mCollider;
		eDirection mDirection;
		Player* mPlayer;

		Vector3 mPlayerPos;
		Vector3 mPos;
		float mTime;
	};

}

