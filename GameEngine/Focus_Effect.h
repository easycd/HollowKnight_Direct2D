#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;

	class Focus_Effect : public GameObject
	{
	public:
		Focus_Effect();
		virtual ~Focus_Effect();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Focus_Start();
		virtual void Focus_Loop();
		virtual void Focus_End();

		void Destroy();


	private:
		Player* mPlayer;
		Animator* mAnimation;
		Transform* mTransform;

		Vector3 mPlayerPos;
		float mTime;

	private:
		bool Loop_Check = true;
	};

}

