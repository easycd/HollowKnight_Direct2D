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
		mAccelation = mForce / mMass; //���ӵ� = �� / ����

		// �ӵ��� ���ӵ��� �����ش�.
		mVelocity += mAccelation * Time::DeltaTime();
		mVelocity2 = mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// ������ ������
			Vector2 gravity = mGravity;
			gravity.Normalizes();

			float dot = math::Vector2::Dots(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �߷°��ӵ� �ִ� �ӵ� ����
		Vector2 gravity = mGravity;
		gravity.Normalizes();
		float dot = math::Vector2::Dots(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length()) //�ִ�ӵ� < �߷� ����
		{
			gravity.Normalizes();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalizes();
			sideVelocity *= mLimitedVelocity.x;
		}

		// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
		if (!(mVelocity == Vector2::Zero))
		{
			//�ӵ��� �ݴ�������� �������� ����ȴ�.
			Vector2 friction = -mVelocity;
			friction = friction.Normalizes() * mFriction * mMass * Time::DeltaTime(); //���� * ������� * ������� * �ð�

			//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū ���
			if (mVelocity.Length() < friction.Length()) //�������� �� ũ�� �ӵ��� 0
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}


		// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
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