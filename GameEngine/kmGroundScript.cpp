#include "kmGroundScript.h"
#include "kmCollider2D.h"
#include "kmGameObject.h"

namespace km
{
	GroundScript::GroundScript()
	{
	}
	GroundScript::~GroundScript()
	{
	}
	void GroundScript::Initialize()
	{

		//Collider2D* collider = GetOwner()->AddComponent<Collider2D>();
		col = AddComponent<Collider2D>();

		GameObject::Initialize();
	}
	void GroundScript::Update()
	{
		GameObject::Update();
	}
}