#pragma once
#include <kmScript.h>

namespace km
{
	class GroundScript : public Script
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
	};
}

