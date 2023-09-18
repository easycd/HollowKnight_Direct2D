#include "kmPureVessel.h"
#include "kmAnimation.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmRigidbody.h"
#include "kmCollider2D.h"
#include "kmCollisionManager.h"

namespace km
{
	PureVessel::PureVessel()
	{
	}
	PureVessel::~PureVessel()
	{
	}

	void PureVessel::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		GameObject::Initialize();
	}
	void PureVessel::Update()
	{

		GameObject::Update();
	}

	void PureVessel::OnCollisionEnter(Collider2D* other)
	{
	}

	void PureVessel::OnCollisionStay(Collider2D* other)
	{
	}

	void PureVessel::OnCollisionExit(Collider2D* other)
	{
	}

	void PureVessel::Pattern()
	{
	}

	void PureVessel::Idle()
	{
	}

	void PureVessel::Counter()
	{
	}

	void PureVessel::Dash()
	{
	}

	void PureVessel::Knife_Spike()
	{
	}

	void PureVessel::Slash()
	{
	}

	void PureVessel::Knife_Spread()
	{
	}

	void PureVessel::Groggy()
	{
	}

	void PureVessel::Circle_Attack()
	{
	}

	void PureVessel::Dark_tentacle()
	{
	}

}