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

		virtual void Slash_Left();
		virtual void Slash_Right();
		virtual void UP_Slash_Left();
		virtual void UP_Slash_Right();
		virtual void Down_Slash_Left();
		virtual void Down_Slash_Right();

		void Destroy();
		

	private:
		PlayerScript* player;
		Animator* at;
		Transform* mTransform;
		Vector3 pos;
		float mTime;

	};
}


