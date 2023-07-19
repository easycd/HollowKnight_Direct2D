#pragma once
#include "..\Engine_SOURCE\kmScene.h"

namespace km
{
	class Godhome : public Scene
	{
	public:
		Godhome();
		virtual ~Godhome();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}
