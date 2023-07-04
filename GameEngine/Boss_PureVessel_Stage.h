#pragma once
#include "..\Engine_SOURCE\kmScene.h"

namespace km
{
	class Boss_PureVessel_Stage : public Scene
	{
	public:
		Boss_PureVessel_Stage();
		virtual ~Boss_PureVessel_Stage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
