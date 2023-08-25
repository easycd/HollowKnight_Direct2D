#pragma once
#include "kmComponent.h"
#include "kmTransform.h"

namespace km
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other);// �浹ü �浹
		virtual void OnCollisionStay(Collider2D* other); // �浹�ϰ� ���� ��
		virtual void OnCollisionExit(Collider2D* other); // �浹�ϰ� ���������� ��

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }
		void SetPos(Vector2 pos) { mPos = pos; }

		Vector2 GetSize() { return mSize; }
		UINT GetColliderID() { return mColliderID; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;
		int mCollisionCount;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;
		Vector2 mPos;
	};
}

