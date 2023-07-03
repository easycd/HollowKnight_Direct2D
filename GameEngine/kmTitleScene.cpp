#include "kmTitleScene.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmMesh.h"
#include "kmCameraScript.h"
#include "kmCamera.h"
#include "kmSceneManager.h"

namespace km
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		{
			GameObject* TitleBG = new GameObject();
			TitleBG->SetName(L"Title");
			AddGameObject(eLayerType::BG, TitleBG);
			MeshRenderer* mr = TitleBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TitleBG"));
			TitleBG->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			TitleBG->GetComponent<Transform>()->SetScale(Vector3(7.0f, 4.5f, 0.0f));
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

	void TitleScene::Update()
	{
		Scene::Update();
	}

	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}
}