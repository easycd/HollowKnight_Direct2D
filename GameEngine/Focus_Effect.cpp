#include "Focus_Effect.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmMeshRenderer.h"
#include "kmObject.h"
#include "kmPlayer.h"

namespace km
{
	Focus_Effect::Focus_Effect()
	{
	}
	Focus_Effect::~Focus_Effect()
	{
	}
	void Focus_Effect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Focus_Start = Resources::Load<Texture>(L"Focus_Start", L"..\\Resources\\Knight\\Effect\\Focus_Effect\\Start\\Focus_Start.png");
		std::shared_ptr<Texture> Focus_Loop = Resources::Load<Texture>(L"Focus_Loop", L"..\\Resources\\Knight\\Effect\\Focus_Effect\\Loop\\Focus_Loop.png");
		std::shared_ptr<Texture> Focus_End = Resources::Load<Texture>(L"Focus_End", L"..\\Resources\\Knight\\Effect\\Focus_Effect\\End\\Focus_End.png");

		mAnimation->Create(L"Focus_Start", Focus_Start, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 7, Vector2(0.0f, 0.0f), 0.05f);
		mAnimation->Create(L"Focus_Loop", Focus_Loop, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 6, Vector2(0.0f, 0.0f), 0.05f);
		mAnimation->Create(L"Focus_End", Focus_End, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 2, Vector2(0.0f, 0.0f), 0.05f);

	
		mAnimation->CompleteEvent(L"Focus_Start") = std::bind(&Focus_Effect::Focus_Loop, this);
		mAnimation->CompleteEvent(L"Focus_End") = std::bind(&Focus_Effect::Destroy, this);
	
		mTransform->SetScale(Vector3(0.35f, 0.25f, 0.0f));
		GameObject::Initialize();
	}
	void Focus_Effect::Update()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mTransform->SetPosition(Vector3(mPlayerPos.x, mPlayerPos.y + 0.04f, 0.2f));

		GameObject::Update();
	}

	void Focus_Effect::Focus_Start()
	{
		mAnimation->PlayAnimation(L"Focus_Start", true);
	}

	void Focus_Effect::Focus_Loop()
	{
		if(Loop_Check)
			mAnimation->PlayAnimation(L"Focus_Loop", true);
	}

	void Focus_Effect::Focus_End()
	{
		mAnimation->PlayAnimation(L"Focus_End", true);
	}

	void Focus_Effect::Destroy()
	{
		object::Destroy(this);
	}
}