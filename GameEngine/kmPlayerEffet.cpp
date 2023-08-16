#include "kmPlayerEffet.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmPlayerScript.h"
#include "kmMeshRenderer.h"

namespace km
{
	PlayerEffet::PlayerEffet()
		:mTime(0.0f)
	{

	}
	PlayerEffet::~PlayerEffet()
	{
	}

	void PlayerEffet::Initialize()
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector3(1.0f, 0.0f, 0.0f));

		MeshRenderer* mr = GetComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

		at = AddComponent<Animator>();
		std::shared_ptr<Texture> AttackRight = Resources::Load<Texture>(L"AttackRight", L"..\\Resources\\Knight\\Effect\\Attack\\Attack.png");
		std::shared_ptr<Texture> AttackLeft = Resources::Load<Texture>(L"AttackLeft", L"..\\Resources\\Knight\\Effect\\Attack\\Attack.png");

		std::shared_ptr<Texture> UpAttackRight = Resources::Load<Texture>(L"UpAttackRight", L"..\\Resources\\Knight\\Effect\\Attack\\UPAttack.png");
		std::shared_ptr<Texture> UpAttackLeft = Resources::Load<Texture>(L"UpAttackLeft", L"..\\Resources\\Knight\\Effect\\Attack\\UPAttack.png");

		std::shared_ptr<Texture> DownAttackRight = Resources::Load<Texture>(L"DownAttackRight", L"..\\Resources\\Knight\\Effect\\Attack\\DownAttack.png");
		std::shared_ptr<Texture> DownAttackLeft = Resources::Load<Texture>(L"DownAttackLeft", L"..\\Resources\\Knight\\Effect\\Attack\\DownAttack.png");

		at->Create(L"Attack_Right_Effect", AttackRight, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 15);
		at->Create(L"Attack_Left", AttackLeft, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 1);

		at->Create(L"Up_Attack_Right", UpAttackRight, Vector2(0.0f, 0.0f), Vector2(169.0f, 192.0f), 1);
		at->Create(L"Up_Attack_Left", UpAttackLeft, Vector2(0.0f, 0.0f), Vector2(169.0f, 192.0f), 1);

		at->Create(L"Down_Attack_Right", DownAttackRight, Vector2(0.0f, 0.0f), Vector2(182.0f, 209.0f), 1);
		at->Create(L"Down_Attack_Left", DownAttackLeft, Vector2(0.0f, 0.0f), Vector2(182.0f, 209.0f), 1);

		at->PlayAnimation(L"Attack_Right_Effect", true);
		GameObject::Initialize();
	}

	void PlayerEffet::Update()
	{
		Vector3 pos = mTransform->GetPosition();
		mTransform->SetPosition(pos);

		GameObject::Update();
	}

	void PlayerEffet::Normal_Attack_Effect()
	{
		at->PlayAnimation(L"Attack_Right_Effect", true);
	}

	void PlayerEffet::UP_Attack_Effect()
	{
	}

	void PlayerEffet::Down_Attack_Effect()
	{
	}
}