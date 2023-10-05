#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;
	class CameraScript;

	class SoulGauge : public GameObject
	{
	public:
		SoulGauge();
		virtual ~SoulGauge();

		virtual void Initialize();
		virtual void Update();


	private:
		Player* mPlayer;
		CameraScript* mCamraScript;
		Animator* mAnimation;
		Transform* mTransform;

		Vector3 mCameraPos;
	};


}

