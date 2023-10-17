#include "kmSpear.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"

namespace km
{
	Spear::Spear()
	{
	}
	Spear::~Spear()
	{
	}
	void Spear::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> SpearOn = Resources::Load<Texture>(L"SpearOn", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Spear\\Spear.png");
		mAnimation->Create(L"SpearOn", SpearOn, Vector2(0.0f, 0.0f), Vector2(59.0f, 230.0f), 7, Vector2(0.0f, 0.0f), 0.01f);

		GameObject::Initialize();
	}
	void Spear::Update()
	{

		GameObject::Update();
	}
	void Spear::Spear_On()
	{
		if (Spear_On_Check)
		{
			mAnimation->PlayAnimation(L"SpearOn", true);
			Spear_On_Check = false;
		}
	}
	void Spear::Destroy()
	{
		object::Destroy(this);
	}
}