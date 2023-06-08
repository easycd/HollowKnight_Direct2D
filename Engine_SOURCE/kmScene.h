#pragma once
#include "kmEntity.h"
#include "kmGameObject.h"

namespace km
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	
	private:
		std::vector<GameObject*> mGameObjects;
	};
}

