#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;

	class DsahEffect : public GameObject
	{
	public:
		DsahEffect();
		virtual ~DsahEffect();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Dash_Left();
		virtual void Dash_Right();

		void Destroy();


	private:
		Player* mPlayer;
		Animator* mAnimation;
		Transform* mTransform;

		Vector3 mPlayerPos;
		float mTime;

	private:
		bool Dash_Left_Check = false;
		bool Dash_Right_Check = false;
	};

}


