#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;

	class Focus_On_Effect : public GameObject
	{
	public:
		Focus_On_Effect();
		virtual ~Focus_On_Effect();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void Start();

		void Destroy();

	private:
		Player* mPlayer;
		Animator* mAnimation;
		Transform* mTransform;

		Vector3 mPlayerPos;
		float mTime;
	};
}
