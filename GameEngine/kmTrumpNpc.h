#pragma once
#include "kmGameObject.h"


namespace km
{
	class Animator;

	class TrumpNpc : public GameObject
	{
	public:
		TrumpNpc();
		virtual ~TrumpNpc();

		virtual void Initialize();
		virtual void Update();

	private:
		Transform* mTransform;
		Animator* mAnimation;

	};
}
