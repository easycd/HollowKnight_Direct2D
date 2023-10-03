#include "kmGround.h"
#include "kmCollider2D.h"
#include "kmTransform.h"
#include "kmRigidbody.h"
#include "kmGameObject.h"
#include "kmRenderer.h"
#include "kmScene.h"
#include "kmSceneManager.h"

namespace km
{
	Ground::Ground()
		: Component(eComponentType::Ground)
	{
	}
	Ground::~Ground()
	{
	}
	void Ground::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}
	void Ground::Update()
	{
	}
	void Ground::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 scale = tr->GetScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;

		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = scale;
		mesh.rotation = tr->GetRotation();
		mesh.type = eColliderType::Rect;

		renderer::PushDebugMeshAttribute(mesh);
	}
	void Ground::LayerCollistions(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene(); //�����ϰ��ִ� SCene�� �����´�.

		const std::vector<GameObject*>& lefts = activeScene->GetLayer(left).GetGameObjects(); //�浹�� ���� ������Ʈ�� �����´�.
		const std::vector<GameObject*>& rights = activeScene->GetLayer(right).GetGameObjects(); //�浹�� ������ ������Ʈ�� �����´�.

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftObj->GetState() != GameObject::eState::Active)
				continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (leftObj == rightObj)
					continue;
				if (rightObj->GetState() != GameObject::eState::Active)
					continue;

				ColliderCollisions(leftCol, rightCol);
			}
		}
	}
	void Ground::ColliderCollisions(Collider2D* left, Collider2D* right)
	{
		//ColliderID id = {};
		//id.left = left->GetColliderID();
		//id.right = right->GetColliderID();
		//
		//// �浹������ �����´�
		//std::map<UINT64, bool>::iterator iter
		//	= mCollisionMap.find(id.id);
		//
		//if (iter == mCollisionMap.end())
		//{
		//	mCollisionMap.insert(std::make_pair(id.id, false));
		//	iter = mCollisionMap.find(id.id);
		//}
		//
		//if (Intersect(left, right))
		//{
		//	// �浹
		//	if (iter->second == false)
		//	{
		//		//���� �浹
		//		left->OnCollisionEnter(right);
		//		right->OnCollisionEnter(left);
		//	}
		//	else
		//	{
		//		// �浹 ��
		//		left->OnCollisionStay(right);
		//		right->OnCollisionStay(left);
		//	}
		//}
		//else
		//{
		//	// �浹 X
		//	if (iter->second == true)
		//	{
		//		// �浹�ϰ� �ִٰ� ������
		//		left->OnCollisionExit(right);
		//		right->OnCollisionExit(left);
		//	}
		//}
	}
	void Ground::Render(HDC hdc)
	{
	}
	void Ground::Release()
	{
	}
	void Ground::OnCollisionEnter(Collider* other)
	{
		//PlayerScript* player = dynamic_cast<PlayerScript*>(other->GetOwner());
	}
	void Ground::OnCollisionStay(Collider* other)
	{
	}
	void Ground::OnCollisionExit(Collider* other)
	{
	}
}