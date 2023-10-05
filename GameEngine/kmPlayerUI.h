#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;
	class CameraScript;

	class PlayerUI : public GameObject
	{
	public:
		PlayerUI();
		virtual ~PlayerUI();

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
