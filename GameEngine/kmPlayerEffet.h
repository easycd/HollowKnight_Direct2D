#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class PlayerScript;

	class PlayerEffet : public GameObject
	{
	public:

		PlayerEffet();
		~PlayerEffet();

		virtual void Initialize() override;
		virtual void Update() override;

		//private:
		void Normal_Attack_Effect();
		void UP_Attack_Effect();
		void Down_Attack_Effect();

	private:
		PlayerScript* player;
		Animator* at;
		Transform* mTransform;
		Vector3 pos;
		float mTime;

	};
}


