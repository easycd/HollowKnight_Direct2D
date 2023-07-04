#include "Boss_PureVessel_Stage.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmMesh.h"
#include "kmCameraScript.h"
#include "kmCamera.h"
#include "kmSceneManager.h"
#include "kmInput.h"


namespace km
{
	Boss_PureVessel_Stage::Boss_PureVessel_Stage()
	{
	}
	Boss_PureVessel_Stage::~Boss_PureVessel_Stage()
	{
	}
	void Boss_PureVessel_Stage::Initialize()
	{
		{
			GameObject* TitleBG = new GameObject();
			TitleBG->SetName(L"PureVesselStage_BG");
			AddGameObject(eLayerType::BG, TitleBG);
			MeshRenderer* mr = TitleBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"PureVesselStage_BG"));
			TitleBG->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.1f, 0.0f));
			TitleBG->GetComponent<Transform>()->SetScale(Vector3(8.0f, 5.0f, 0.0f));
		}

		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::BG, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::BG, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}
	}
	void Boss_PureVessel_Stage::Update()
	{
		Scene::Update();
		//if (Input::GetKeyDown(eKeyCode::K))
		//{
		//	SceneManager::LoadScene(L"Dirtmouth");
		//}
	}
	void Boss_PureVessel_Stage::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Boss_PureVessel_Stage::Render()
	{
		Scene::Render();
	}
}