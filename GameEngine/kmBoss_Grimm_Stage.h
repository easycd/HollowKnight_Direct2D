#pragma once
#include "..\Engine_SOURCE\kmScene.h"

namespace km
{
	class Boss_Grimm_Stage : public Scene
	{
	public:
		Boss_Grimm_Stage();
		virtual ~Boss_Grimm_Stage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
