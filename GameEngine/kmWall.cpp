#include "kmWall.h"
#include "kmCollider2D.h"
#include "kmGameObject.h"

namespace km
{
	Wall::Wall()
	{
	}
	Wall::~Wall()
	{
	}
	void Wall::Initialize()
	{
		col = AddComponent<Collider2D>();

		GameObject::Initialize();
	}
	void Wall::Update()
	{
		GameObject::Update();
	}
}