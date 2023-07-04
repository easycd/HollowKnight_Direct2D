#include "kmDirtmouth.h"
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
	Dirtmouth::Dirtmouth()
	{
	}
	Dirtmouth::~Dirtmouth()
	{
	}
	void Dirtmouth::Initialize()
	{
		{
			GameObject* GrimmTownBG = new GameObject();
			GrimmTownBG->SetName(L"Grimm_Town");
			AddGameObject(eLayerType::BG, GrimmTownBG);
			MeshRenderer* mr = GrimmTownBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GrimmTown"));
			GrimmTownBG->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -1.0f, 0.0f));
			GrimmTownBG->GetComponent<Transform>()->SetScale(Vector3(7.0f, 4.5f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}
	}
	void Dirtmouth::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::K))
		{
			SceneManager::LoadScene(L"Boss_Grimm_Stage");
		}
	}
	void Dirtmouth::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Dirtmouth::Render()
	{
		Scene::Render();
	}
}