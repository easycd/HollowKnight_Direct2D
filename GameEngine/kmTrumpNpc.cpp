#include "kmTrumpNpc.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmObject.h"
#include "kmMeshRenderer.h"

namespace km
{
	TrumpNpc::TrumpNpc()
	{
	}

	TrumpNpc::~TrumpNpc()
	{
	}

	void TrumpNpc::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Idle = Resources::Load<Texture>(L"Trump_Idle", L"..\\Resources\\Boss_Grimm\\Npc\\Trump_Npc.png");
		mAnimation->Create(L"Trump_Idle", Idle, Vector2(0.0f, 0.0f), Vector2(329.0f, 344.0f), 11, Vector2(0.0f, 0.0f), 0.1f);

		mAnimation->PlayAnimation(L"Trump_Idle", true);
		GameObject::Initialize();
	}

	void TrumpNpc::Update()
	{

		GameObject::Update();
	}
}