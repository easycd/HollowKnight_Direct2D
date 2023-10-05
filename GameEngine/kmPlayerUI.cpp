#include "kmPlayerUI.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmObject.h"
#include "kmMeshRenderer.h"
#include "kmPlayer.h"
#include "kmCameraScript.h"

namespace km
{
	PlayerUI::PlayerUI()
	{
	}
	PlayerUI::~PlayerUI()
	{
	}

	void PlayerUI::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Hud_Flame = Resources::Load<Texture>(L"Hud_Flame", L"..\\Resources\\UI\\HUD\\HUD_Flame.png");
		mAnimation->Create(L"Hud_Flame", Hud_Flame, Vector2(0.0f, 0.0f), Vector2(257.0f, 164.0f), 1, Vector2(0.0f, 0.0f), 1.0f);


		mTransform->SetScale(Vector3(0.27f, 0.17f, 0.0f));
		mTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

		mAnimation->PlayAnimation(L"Hud_Flame", true);

		GameObject::Initialize();
	}
	void PlayerUI::Update()
	{
		mCamraScript = SceneManager::GetCamera();
		mCameraPos = mCamraScript->GetOwner()->GetComponent<Transform>()->GetPosition();

		mTransform->SetPosition(Vector3(mCameraPos.x - 0.58f, mCameraPos.y + 0.32f, 0.0f));
		GameObject::Update();
	}
}