#pragma once
#include "..\Engine_SOURCE\kmScene.h"

namespace km
{
	class Player;
	class Grimm;

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
		
	};
}
