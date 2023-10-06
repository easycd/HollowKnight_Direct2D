#include "kmGirmm_Hand.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmMeshRenderer.h"
#include "kmObject.h"

namespace km
{
	Girmm_Hand::Girmm_Hand()
		: mTime(0.0f)
	{
	}
	Girmm_Hand::~Girmm_Hand()
	{
	}

	void Girmm_Hand::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Hand_Out = Resources::Load<Texture>(L"FireBallEffect_Left", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Hand\\Gimm_HandOut\\Hand_Out.png");
		std::shared_ptr<Texture> Hand_Click = Resources::Load<Texture>(L"Hand_Click", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Hand\\Grimm_HandClick\\Hand_Click.png");
		std::shared_ptr<Texture> Hand_Click_Idle = Resources::Load<Texture>(L"Hand_Click_Idle", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Hand\\Grimm_HandClick_Idle\\Hand_Click_Idle.png");
		std::shared_ptr<Texture> Hand_In = Resources::Load<Texture>(L"Hand_In", L"..\\Resources\\Boss_Grimm\\Boss_Grimm\\Grimm_Hand\\Grimm_HandIn\\Hand_In.png");

		mAnimation->Create(L"Hand_Out", Hand_Out, Vector2(0.0f, 0.0f), Vector2(353.0f, 296.0f), 8, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Hand_Click", Hand_Click, Vector2(0.0f, 0.0f), Vector2(353.0f, 296.0f), 3, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Hand_Click_Idle", Hand_Click_Idle, Vector2(0.0f, 0.0f), Vector2(353.0f, 296.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Hand_In", Hand_In, Vector2(0.0f, 0.0f), Vector2(353.0f, 296.0f), 6, Vector2(0.0f, 0.0f), 0.1f);

		mAnimation->CompleteEvent(L"Hand_Out") = std::bind(&Girmm_Hand::Hand_Click, this);
		mAnimation->CompleteEvent(L"Hand_Click") = std::bind(&Girmm_Hand::Hand_Click_Idle, this);
		mAnimation->CompleteEvent(L"Hand_In") = std::bind(&Girmm_Hand::Destroy, this);

		mTransform->SetPosition(Vector3(0.3f, -0.37f, 2.0f));
		mTransform->SetScale(Vector3(0.3f, 0.3f, 0.0f));

		GameObject::Initialize();
	}

	void Girmm_Hand::Update()
	{
		if (mHand_Click_Check)
		{
			mTime += Time::DeltaTime();

			if (mTime > 1.5f)
			{
				mHand_Click_Check = false;
				Hand_In();
			}
		}

		GameObject::Update();
	}

	void Girmm_Hand::Hand_Out()
	{
		mAnimation->PlayAnimation(L"Hand_Out", true);
	}

	void Girmm_Hand::Hand_Click()
	{
		mAnimation->PlayAnimation(L"Hand_Click", true);
	}

	void Girmm_Hand::Hand_Click_Idle()
	{
		mHand_Click_Check = true;
		mAnimation->PlayAnimation(L"Hand_Click_Idle", true);
	}

	void Girmm_Hand::Hand_In()
	{
		mAnimation->PlayAnimation(L"Hand_In", true);
	}

	void Girmm_Hand::Destroy()
	{
		object::Destroy(this);
	}
}