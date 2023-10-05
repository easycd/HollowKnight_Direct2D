#include "kmDsahEffect.h"
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
	DsahEffect::DsahEffect()
	{
	}
	DsahEffect::~DsahEffect()
	{
	}
	void DsahEffect::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Dash_Left = Resources::Load<Texture>(L"Dash_Left", L"..\\Resources\\Knight\\Effect\\Dash_Effect\\Left\\Dash_Left.png");
		std::shared_ptr<Texture> Dash_Right = Resources::Load<Texture>(L"Dash_Right", L"..\\Resources\\Knight\\Effect\\Dash_Effect\\Right\\Dash_Right.png");

		mAnimation->Create(L"Dash_Left", Dash_Left, Vector2(0.0f, 0.0f), Vector2(342.0f, 175.0f), 13, Vector2(0.0f, 0.0f), 0.05f);
		mAnimation->Create(L"Dash_Right", Dash_Right, Vector2(0.0f, 0.0f), Vector2(342.0f, 175.0f), 13, Vector2(0.0f, 0.0f), 0.05f);

		mAnimation->CompleteEvent(L"Dash_Left") = std::bind(&DsahEffect::Destroy, this);
		mAnimation->CompleteEvent(L"Dash_Right") = std::bind(&DsahEffect::Destroy, this);

		mTransform->SetScale(Vector3(0.2f, 0.1f, 0.0f));
		GameObject::Initialize();
	}
	void DsahEffect::Update()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayerPos = mPlayer->GetComponent<Transform>()->GetPosition();

		if (Dash_Left_Check)
		{
			mTransform->SetPosition(Vector3(mPlayerPos.x + 0.09f, mPlayerPos.y, 1.0f));
		}
		if (Dash_Right_Check)
		{
			mTransform->SetPosition(Vector3(mPlayerPos.x - 0.09f, mPlayerPos.y, 1.0f));
		}
		GameObject::Update();
	}
	void DsahEffect::Dash_Left()
	{
		Dash_Left_Check = true;
		mAnimation->PlayAnimation(L"Dash_Left", true);
	}
	void DsahEffect::Dash_Right()
	{
		Dash_Right_Check = true;
		mAnimation->PlayAnimation(L"Dash_Right", true);
	}
	void DsahEffect::Destroy()
	{
		object::Destroy(this);
	}
}