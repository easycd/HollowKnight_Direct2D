#pragma once
#include "..\Engine_SOURCE\kmScene.h"

namespace km
{
	class Player;
	class Grimm;
	class Spike_Object;
	class FlameBat;
	class TrumpNpc;
	class Crowd;

	class Boss_Grimm_Stage : public Scene
	{
	public:
		Boss_Grimm_Stage();
		virtual ~Boss_Grimm_Stage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter () override;
		virtual void OnExit() override;

		virtual Player* GetPlayer() override { return mPlayer; };

	private:
		Player* mPlayer;
		Grimm* mGrimm;
		Camera* mCamera;
		Spike_Object* sp;
		FlameBat* fb;
		TrumpNpc* mNpc;
		//Left
		Crowd* mCrowd_00;
		Crowd* mCrowd_01;
		Crowd* mCrowd_02;
		Crowd* mCrowd_03;
		Crowd* mCrowd_04;
		Crowd* mCrowd_05;

		//Right
		Crowd* mCrowd_06;
		Crowd* mCrowd_07;
		Crowd* mCrowd_08;
		Crowd* mCrowd_09;
		Crowd* mCrowd_10;


	};
}
