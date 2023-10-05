#include "kmSoulGauge.h"
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
	SoulGauge::SoulGauge()
	{
	}
	SoulGauge::~SoulGauge()
	{
	}
	void SoulGauge::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"DebugRect"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> Soul = Resources::Load<Texture>(L"Soul", L"..\\Resources\\UI\\HUD\\Soul.png");
		mAnimation->Create(L"Soul", Soul, Vector2(0.0f, 0.0f), Vector2(130.f, 125.0f), 1, Vector2(0.0f, 0.0f), 1.0f);

		mTransform->SetScale(Vector3(0.13f, 0.13f, 0.0f));

		mAnimation->PlayAnimation(L"Soul", true);
		GameObject::Initialize();
	}
	void SoulGauge::Update()
	{

		mCamraScript = SceneManager::GetCamera();
		mCameraPos = mCamraScript->GetOwner()->GetComponent<Transform>()->GetPosition();

		mTransform->SetPosition(Vector3(mCameraPos.x - 0.635f, mCameraPos.y + 0.3f, 0.0f));
		GameObject::Update();
	}
}