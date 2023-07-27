#pragma once
#include "kmComponent.h"
#include "kmRigidbodyMath.h"

namespace km
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetMass(float mass) { mMass = mass; } // ���� ���� �Լ�
		void AddForce(VectorR force); // ���� �������ټ� �ִ� �Լ�
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(VectorR velocity) { mVelocity = velocity; }
		VectorR GetVelocity() { return mVelocity; }

	private:
		float mMass; //����
		VectorR mForce; //��ü�� �̵���Ű�� ��
		VectorR mAccelation; //���ӵ�
		VectorR mVelocity; //�ӵ�
		VectorR mVelocity2;
		VectorR mGravity; //�߷�
		VectorR mLimitedVelocity;

		bool mbGround; //���� �پ����� �Ⱥپ����� üũ
		float mFriction; //������

		//float mStaticFriction; //����������
		//float mKineticFriction; //�������
		//float mCoefficientFriction; //������ ���
		//float mNormalForce; 
	};
}
