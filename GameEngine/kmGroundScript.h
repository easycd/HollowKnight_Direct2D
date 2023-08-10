#pragma once
#include "kmGameObject.h"

namespace km
{
	class GroundScript : public GameObject
	{
	public:
		GroundScript();
		virtual ~GroundScript();

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		Collider2D* col;
	};
}

