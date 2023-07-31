#pragma once
#include "kmEntity.h"

namespace km
{
	using namespace km::enums;
	using namespace km::math;

	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		eComponentType GetType() { return mType; }
		GameObject* GetOwner() { return mOwner; }
		
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}

