#include "kmCameraScript.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmInput.h"

namespace km
{
	void CameraScript::Initialize()
	{
	}
	void CameraScript::Update()
	{
		mTransfrom = GetOwner()->GetComponent<Transform>();
		mPos = mTransfrom->GetPosition();

		if (mTarget)
		{
			mTargetPos = mTarget->GetComponent<Transform>();
			PlayerPos = mTargetPos->GetPosition();

			if (mFirstSet)
			{
				if (PlayerPos.x < mWeight.x)
					mTransfrom->SetPosition(Vector3(mWeight.x, mHight, 0.0f));

			}

			if (mFirstSet == false)
			{
				if (PlayerPos.x >= mWeight.x && PlayerPos.x <= mWeight.y)
				{
					mTransfrom->SetPosition(Vector3(PlayerPos.x, mHight, 0.0f));
				}
				else
				{
					mTransfrom->SetPosition(Vector3(mPos.x, mHight, 0.0f));
				}
			}		
		}
		else
		{
			mTransfrom->SetPosition(Vector3(0.f, 0.f, -10.f));
		}

		mFirstSet = false;
	}
}
