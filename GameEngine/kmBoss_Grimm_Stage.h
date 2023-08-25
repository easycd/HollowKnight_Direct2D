#pragma once
#include "..\Engine_SOURCE\kmScene.h"

namespace km
{
	class Player;
	class Boss_Grimm_Stage : public Scene
	{
	public:
		Boss_Grimm_Stage();
		virtual ~Boss_Grimm_Stage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

	private:
		Player* player;
		GameObject* Grimm;
		Camera* mCamera;
		
	};
}
