#include "kmLightCircle.h"
#include "kmResources.h"
#include "kmAnimator.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmTime.h"
#include "kmObject.h"
#include "kmCollider2D.h"

namespace km
{
	LightCircle::LightCircle()
	{
	}
	LightCircle::~LightCircle()
	{
	}
	void LightCircle::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mAnimation = AddComponent<Animator>();

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<Texture> CircleObj = Resources::Load<Texture>(L"CircleObj", L"..\\Resources\\Boss_PureVessel\\PureVessel\\Object\\Circle\\CircleObj.png");

		mAnimation->Create(L"CircleObj", CircleObj, Vector2(0.0f, 0.0f), Vector2(707.0f, 608.0f), 6, Vector2(0.0f, 0.0f), 0.08f);

		mAnimation->CompleteEvent(L"CircleObj") = std::bind(&LightCircle::Destroy, this);

		mTransform->SetScale(Vector3(0.5f, 0.5f, 0.0f));
		GameObject::Initialize();
	}
	void LightCircle::Update()
	{

		GameObject::Update();
	}
	void LightCircle::Circle_On()
	{
		if (Circle_On_Check)
		{
			mCollider = AddComponent<Collider2D>();
			mCollider->SetSize(Vector2(0.7f, 0.7f));
			mAnimation->PlayAnimation(L"CircleObj", true);

			Circle_On_Check = false;
		}
	}
	void LightCircle::Destroy()
	{
		object::Destroy(this);
	}
}
