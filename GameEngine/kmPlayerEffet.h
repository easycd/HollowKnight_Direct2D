#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;

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
		Player* mPlayer;
		Animator* at;
		Transform* mTransform;

		Vector3 pos;
		Vector3 mPlayerPos;
		float mTime;

	private:
		bool Slash_Left_Check       = false;
		bool Slash_Right_Check      = false;
		bool UP_Slash_Left_Check    = false;
		bool UP_Slash_Right_Check   = false;
		bool Down_Slash_Left_Check  = false;
		bool Down_Slash_Right_Check = false;






	};
}


