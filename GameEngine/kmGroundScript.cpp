#include "kmGroundScript.h"
#include "kmCollider2D.h"
#include "kmGameObject.h"

namespace km
{
	void GroundScript::Initialize()
	{

		Collider2D* collider = GetOwner()->AddComponent<Collider2D>();
	}
	void GroundScript::Update()
	{
	}
}