#pragma once
#include "..\Engine_SOURCE\kmScene.h"

namespace km
{
	class Player;
	class PlayerUI;
	class SoulGauge;
	class PlayerHP_State;

	class Dirtmouth : public Scene
	{
	public:
		Dirtmouth();
		virtual ~Dirtmouth();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual Player* GetPlayer() override { return player; }
		virtual CameraScript* GetCamera(){ return mCamerscript; }

		virtual void OnEnter();
		virtual void OnExit();

	private:
		Camera* mCamera;
		CameraScript* mCamerscript;

		Player* player;

		PlayerUI* mPlayerUI;
		SoulGauge* mSoulGauge;
		PlayerHP_State* HP_State;
	};
}
