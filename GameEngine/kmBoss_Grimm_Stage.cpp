#include "kmBoss_Grimm_Stage.h"
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
	Boss_Grimm_Stage::Boss_Grimm_Stage()
	{
	}
	Boss_Grimm_Stage::~Boss_Grimm_Stage()
	{
	}
	void Boss_Grimm_Stage::Initialize()
	{
		{
			GameObject* GrimmStageBG = new GameObject();
			GrimmStageBG->SetName(L"Grimm");
			AddGameObject(eLayerType::BG, GrimmStageBG);
			MeshRenderer* mr = GrimmStageBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GrimmStage_BG"));
			GrimmStageBG->GetComponent<Transform>()->SetPosition(Vector3(16.0f,0.5f, 0.0f));
			GrimmStageBG->GetComponent<Transform>()->SetScale(Vector3(50.0f, 6.0f, 0.0f));
		}

		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::BG, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		////UI Camera
		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::BG, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->TurnLayerMask(eLayerType::Player, false);
		//	//camera->AddComponent<CameraScript>();
		//}
	}
	void Boss_Grimm_Stage::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::K))
		{
			SceneManager::LoadScene(L"Godhome");
		}
	}
	void Boss_Grimm_Stage::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Boss_Grimm_Stage::Render()
	{
		Scene::Render();
	}
}