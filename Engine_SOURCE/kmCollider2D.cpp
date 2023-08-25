#include "kmCollider2D.h"
#include "kmGameObject.h"
#include "kmRenderer.h"


namespace km
{
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, mCollisionCount(0)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}

	Collider2D::~Collider2D()
	{
	}

	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}

	void Collider2D::Update()
	{
	}

	void Collider2D::LateUpdate()
	{
		assert(0 <= mCollisionCount);

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 scale = tr->GetScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;

		graphics::DebugMesh mesh = {};
		mesh.position = mPosition;
		mesh.scale = scale;
		mesh.rotation = tr->GetRotation();
		mesh.type = eColliderType::Rect;
		mesh.ColCount = mCollisionCount;

		renderer::PushDebugMeshAttribute(mesh);
	}

	void Collider2D::Render()
	{
	}
	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetComponents<Script>();
		
		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}

		mCollisionCount++;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetComponents<Script>();
		
		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}

		GetOwner()->OnCollisionStay(other);
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetComponents<Script>();
		
		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}

		mCollisionCount--;
		GetOwner()->OnCollisionExit(other);
	}
}
