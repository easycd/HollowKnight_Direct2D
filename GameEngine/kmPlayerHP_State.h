#pragma once
#include "kmGameObject.h"

namespace km
{
	class Animator;
	class Player;
	class PlayerHP;

	class PlayerHP_State : public GameObject
	{
	public:
		PlayerHP_State();
		virtual ~PlayerHP_State();

		virtual void Initialize();
		virtual void Update();

		void HP();


	private:
		Player* mPlayer;
		Animator* mAnimation;
		Transform* mTransform;

	private:
		int mPlayer_HP;
		bool HPState = true; //true면 회복 false면 HP 차감

	private:
		PlayerHP* HP_00;
		PlayerHP* HP_01;
		PlayerHP* HP_02;
		PlayerHP* HP_03;
		PlayerHP* HP_04;

	private:
		bool Check_Recover_00 = true;
		bool Check_Recover_01 = true;
		bool Check_Recover_02 = true;
		bool Check_Recover_03 = true;
		bool Check_Recover_04 = true;


		bool Check_Break_00 = true;
		bool Check_Break_01 = true;
		bool Check_Break_02 = true;
		bool Check_Break_03 = true;
		bool Check_Break_04 = true;
	};
}


