#include "kmDirtmouth.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmMesh.h"
#include "kmCameraScript.h"
#include "kmCamera.h"
#include "kmSceneManager.h"
#include "kmInput.h"
#include "kmObject.h"
#include "kmRenderer.h"
#include "kmCollider2D.h"

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
		{ //BackGround
			GameObject* GrimmTownBG = new GameObject();
			GrimmTownBG->SetName(L"Grimm_Town");
			AddGameObject(eLayerType::BG, GrimmTownBG);
			MeshRenderer* mr = GrimmTownBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GrimmTown"));
			GrimmTownBG->GetComponent<Transform>()->SetPosition(Vector3(5.0f, 0.5f, 0.0f));
			GrimmTownBG->GetComponent<Transform>()->SetScale(Vector3(23.0f,6.2f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		{ //HUD
			GameObject* GrimmTownBG = new GameObject();
			GrimmTownBG->SetName(L"PlayerHUD");
			AddGameObject(eLayerType::UI, GrimmTownBG);
			MeshRenderer* mr = GrimmTownBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Palyer_HUD"));
			GrimmTownBG->GetComponent<Transform>()->SetPosition(Vector3(-2.8f, 1.3f, 0.0f));
			GrimmTownBG->GetComponent<Transform>()->SetScale(Vector3(1.0f, 0.8f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

	


		//Main Camera
		Camera* cameraComp = nullptr;
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		////UI Camera
		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::Player, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->TurnLayerMask(eLayerType::Player, false);
		//	//camera->AddComponent<CameraScript>();
		//}
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
		Vector3 pos(800, 450, 0.0f);
		Vector3 pos2(800, 450, 1000.0f);
		Viewport viewport;
		viewport.width = 1600.0f;
		viewport.height = 900.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}
	void Dirtmouth::Render()
	{
		Scene::Render();
	}
}