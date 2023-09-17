#pragma once
#include "kmGameObject.h"

namespace km
{
	class Wall : public GameObject
	{
	public:
		Wall();
		virtual ~Wall();

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		Collider2D* col;
	};
}

