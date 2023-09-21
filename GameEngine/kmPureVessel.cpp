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

		std::shared_ptr<Texture> Idle = Resources::Load<Texture>(L"Idle", L"..\\Resources\\Resources\\Boss_PureVessel\\PureVessel\\Pattern\\Idle\\Idle.png");
		
		//Intro
		std::shared_ptr<Texture> Intro00 = Resources::Load<Texture>(L"Intro00", L"..\\Resources\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro00\\Intro00.png");
		std::shared_ptr<Texture> Intro01 = Resources::Load<Texture>(L"Intro01", L"..\\Resources\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro01\\Intro01.png");
		std::shared_ptr<Texture> Intro02 = Resources::Load<Texture>(L"Intro02", L"..\\Resources\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro02\\Intro02.png");
		std::shared_ptr<Texture> Intro03 = Resources::Load<Texture>(L"Intro03", L"..\\Resources\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro03\\Intro03.png");
		std::shared_ptr<Texture> Intro04 = Resources::Load<Texture>(L"Intro04", L"..\\Resources\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro04\\Intro04.png");
		std::shared_ptr<Texture> Intro05 = Resources::Load<Texture>(L"Intro05", L"..\\Resources\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro05\\Intro05.png");
		std::shared_ptr<Texture> Intro06 = Resources::Load<Texture>(L"Intro06", L"..\\Resources\\Resources\\Boss_PureVessel\\PureVessel\\Intro\\Intro06\\Intro06.png");




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