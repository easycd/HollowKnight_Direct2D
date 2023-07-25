#include "kmRigidbody.h"
#include "kmTime.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmMath.h"
namespace km
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 9000.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 100.0f);
		mFriction = 100.0f;
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		// F = M * A
		// A = M / F
		mAccelation = mForce / mMass; //가속도 = 힘 / 질량

		// 속도에 가속도를 더해준다.
		mVelocity += mAccelation * Time::DeltaTime();
		mVelocity2 = mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// 땅위에 있을때
			Vector2 gravity = mGravity;
			gravity.Normalizes();

			float dot = math::Vector2::Dots(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 중력가속도 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalizes();
		float dot = math::Vector2::Dots(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length()) //최대속도 < 중력 길이
		{
			gravity.Normalizes();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalizes();
			sideVelocity *= mLimitedVelocity.x;
		}

		// 마찰력 조건 ( 적용된 힘이 없고, 속도가 0이 아님)
		if (!(mVelocity == Vector2::Zero))
		{
			//속도에 반대방향으로 마찰력이 적용된다.
			Vector2 friction = -mVelocity;
			friction = friction.Normalizes() * mFriction * mMass * Time::DeltaTime(); //방향 * 마찰계수 * 질량계수 * 시간

			//마찰력으로 인한 속도 감소는 현재 속도보다 큰 경우
			if (mVelocity.Length() < friction.Length()) //마찰력이 더 크면 속도는 0
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}


		// 속도에 맞게끔 물체를 이동시킨다.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();

		tr->SetPosition(pos);
		mForce.Zero;
	}
	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}