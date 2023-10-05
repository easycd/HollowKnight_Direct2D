#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;
	class CameraScript;

	class PlayerHP : public GameObject
	{
	public:
		PlayerHP();
		virtual ~PlayerHP();

		virtual void Initialize();
		virtual void Update();

		void Empty();
		void Idle();
		void Break();
		void Refill();

		void Destroy();

		void SetDistance(float distance) { mDistance = distance; }


	private:
		Player* mPlayer;
		CameraScript* mCamraScript;
		Animator* mAnimation;
		Transform* mTransform;

		Vector3 mCameraPos;

		float mDistance;
	};

}
