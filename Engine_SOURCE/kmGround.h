#pragma once
#include "kmComponent.h"
#include "kmTransform.h"

class Collider2D;;
class CollisionManager;

namespace km
{
	class Ground : public Component
	{
	public:
		Ground();
		virtual ~Ground();


		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void LayerCollistions(eLayerType left, eLayerType right);
		virtual void ColliderCollisions(Collider2D* left, Collider2D* right);
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);


	private:
		Transform* mTransform;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;


	};
}
