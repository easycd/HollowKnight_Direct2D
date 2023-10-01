#include "kmCrowd.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmObject.h"
#include "kmMeshRenderer.h"

namespace km
{
	Crowd::Crowd()
	{
	}

	Crowd::~Crowd()
	{
	}

	void Crowd::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Crowd_Left = Resources::Load<Texture>(L"Crowd_Left", L"..\\\Resources\\Boss_Grimm\\Grimm_Tent\\Npc\\Crowd\\Left\\Crowd_Left.png");
		std::shared_ptr<Texture> Crowd_Right = Resources::Load<Texture>(L"Crowd_Right", L"..\\\Resources\\Boss_Grimm\\Grimm_Tent\\Npc\\Crowd\\Right\\Crowd_Right.png");

		mAnimation->Create(L"Crowd_Left", Crowd_Left, Vector2(0.0f, 0.0f), Vector2(389.0f, 248.0f), 1, Vector2(0.0f, 0.0f), 0.1f);
		mAnimation->Create(L"Crowd_Right", Crowd_Right, Vector2(0.0f, 0.0f), Vector2(389.0f, 248.0f), 1, Vector2(0.0f, 0.0f), 0.1f);

		GameObject::Initialize();
	}

	void Crowd::Update()
	{

		GameObject::Update();
	}

	void Crowd::Play_Left()
	{
		mAnimation->PlayAnimation(L"Crowd_Left", true);
	}

	void Crowd::Play_Right()
	{
		mAnimation->PlayAnimation(L"Crowd_Right", true);
	}
}