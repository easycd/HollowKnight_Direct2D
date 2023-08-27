#include "kmCameraScript.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmTime.h"
#include "kmInput.h"

namespace km
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		if (mTarget)
		{
			Transform* GetPos = mTarget->GetComponent<Transform>();
			Vector3 PlayerPos = GetPos->GetPosition();
			tr->SetPosition(Vector3(PlayerPos.x, PlayerPos.y + 0.3f, 0.0f));
		}
		else
		{
			tr->SetPosition(Vector3(0.f, 0.f, -10.f));
		}


		//if (Input::GetKey(eKeyCode::W))
		//{
		//	pos.z += 5.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::S))
		//{
		//	pos.z -= 5.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::A))
		//{
		//	pos.x -= 5.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::D))
		//{
		//	pos.x += 5.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::Q))
		//{
		//	pos.y -= 5.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::E))
		//{
		//	pos.y += 5.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}

	}
}
