#include "Focus_On_Effect.h"
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
	Focus_On_Effect::Focus_On_Effect()
	{
	}
	Focus_On_Effect::~Focus_On_Effect()
	{
	}
	void Focus_On_Effect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Focus_On = Resources::Load<Texture>(L"Focus_On", L"..\\Resources\\Knight\\Effect\\Fucos_OnEffect\\Focus_On.png");
		mAnimation->Create(L"Focus_On", Focus_On, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 8, Vector2(0.0f, 0.0f), 0.07f);

		mAnimation->CompleteEvent(L"Focus_On") = std::bind(&Focus_On_Effect::Destroy, this);

		mTransform->SetScale(Vector3(0.4f, 0.3f, 0.2f));
		GameObject::Initialize();

	}
	void Focus_On_Effect::Update()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		mTransform->SetPosition(Vector3(mPlayerPos.x, mPlayerPos.y + 0.04f, 0.2f));

		GameObject::Update();
	}
	void Focus_On_Effect::Start()
	{
		mAnimation->PlayAnimation(L"Focus_On", true);
	}
	void Focus_On_Effect::Destroy()
	{
		object::Destroy(this);
	}
}