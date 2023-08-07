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
		mAccelation = mForce / mMass; //���ӵ� = �� / ����

		// �ӵ��� ���ӵ��� �����ش�.
		mVelocity += mAccelation * Time::DeltaTime();
		mVelocity2 = mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// ������ ������
			VectorR gravity = mGravity;
			gravity.Normalize();

			float dot = rigidmath::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity -= mGravity * Time::DeltaTime();
		}

		// �߷°��ӵ� �ִ� �ӵ� ����
		VectorR gravity = mGravity;
		gravity.Normalize();
		float dot = rigidmath::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		VectorR sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length()) //�ִ�ӵ� < �߷� ����
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}

		//// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
		if (!(mVelocity == VectorR::Zero))
		{
			//�ӵ��� �ݴ�������� �������� ����ȴ�.
			VectorR friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime(); //���� * ������� * ������� * �ð�
		
			//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū ���
			if (mVelocity.Length() < friction.Length()) //�������� �� ũ�� �ӵ��� 0
			{
				mVelocity = VectorR::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}


		// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
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