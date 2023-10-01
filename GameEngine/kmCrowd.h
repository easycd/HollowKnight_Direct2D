#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;

	class Crowd : public GameObject
	{
	public:
		Crowd();
		virtual ~Crowd();

		virtual void Initialize();
		virtual void Update();

		virtual void Play_Left();
		virtual void Play_Right();

	private:
		Transform* mTransform;
		Animator* mAnimation;
	};
}
