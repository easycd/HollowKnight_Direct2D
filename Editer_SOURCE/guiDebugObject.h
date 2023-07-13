#pragma once
#include "..\\Engine_SOURCE\\kmGameObject.h"

namespace gui
{
	class DebugObject : public km::GameObject
	{
	public:
		DebugObject();
		~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		
	};
}

