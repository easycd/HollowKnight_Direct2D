#include "kmRigidbody.h"
#include "kmTime.h"
#include "kmGameObject.h"
#include "kmTransform.h"
#include "kmRigidbodyMath.h"

namespace km
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(VectorR::Zero)
		, mAccelation(VectorR::Zero)
		, mVelocity(VectorR::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 9000.0f;
		mbGround = false;
		mGravity = VectorR(0.0f, 13.0f);
		//mGravity = VectorR(0.0f, 0.0f);
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
			VectorR gravity = mGravity;
			gravity.Normalize();

			float dot = rigidmath::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity -= mGravity * Time::DeltaTime();
		}

		// 중력가속도 최대 속도 제한
		VectorR gravity = mGravity;
		gravity.Normalize();
		float dot = rigidmath::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		VectorR sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length()) //최대속도 < 중력 길이
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}

		//// 마찰력 조건 ( 적용된 힘이 없고, 속도가 0이 아님)
		if (!(mVelocity == VectorR::Zero))
		{
			//속도에 반대방향으로 마찰력이 적용된다.
			VectorR friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime(); //방향 * 마찰계수 * 질량계수 * 시간
		
			//마찰력으로 인한 속도 감소는 현재 속도보다 큰 경우
			if (mVelocity.Length() < friction.Length()) //마찰력이 더 크면 속도는 0
			{
				mVelocity = VectorR::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}


		// 속도에 맞게끔 물체를 이동시킨다.
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		VectorR cpos = VectorR(pos.x, pos.y);
		cpos = cpos + mVelocity * Time::DeltaTime();
		pos = Vector3(cpos.x, cpos.y, pos.z);
		tr->SetPosition(pos);
		mForce.Clear();
	}

	void Rigidbody::AddForce(VectorR force)
	{
		mForce += force;
	}
}