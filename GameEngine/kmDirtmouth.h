#pragma once
#include "..\Engine_SOURCE\kmScene.h"

namespace km
{
	class Dirtmouth : public Scene
	{
	public:
		Dirtmouth();
		virtual ~Dirtmouth();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter();
		virtual void OnExit();

	private:
		GameObject* player;
		Camera* mCamera;
	};
}
