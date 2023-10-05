#pragma once
#include "kmGameObject.h"


namespace km
{
	class Animator;
	class Player;

	class DoubleJump_Effect : public GameObject
	{
	public:
		DoubleJump_Effect();
		virtual ~DoubleJump_Effect();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void DoubleJump_Left();
		virtual void DoubleJump_Right();
		
		void Destroy();


	private:
		Player* mPlayer;
		Animator* mAnimation;
		Transform* mTransform;

		Vector3 mPlayerPos;
		float mTime;
	};

}


