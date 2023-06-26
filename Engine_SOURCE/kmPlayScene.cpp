#include "kmPlayScene.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmMesh.h"
#include "kmCameraScript.h"
#include "kmCamera.h"

namespace km
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
	//	{
	//		GameObject* player = new GameObject();
	//		AddGameObject(eLayerType::Player, player);
	//		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
	//		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	//		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
	//		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//		//player->AddComponent<CameraScript>();
	//	}
		
		{
			GameObject* bg = new GameObject();
			AddGameObject(eLayerType::BG, bg);
			MeshRenderer* mr = bg->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"bg"));
			bg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			bg->GetComponent<Transform>()->SetScale(Vector3(10.0f, 10.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

	//	{
	//		GameObject* player = new GameObject(); 
	//		AddGameObject(eLayerType::Player, player);
	//		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
	//		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	//		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
	//		player->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
	//		//player->AddComponent<CameraScript>();
	//	}

	//	{
	//		GameObject* player = new GameObject();
	//		AddGameObject(eLayerType::Player, player);
	//		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
	//		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	//		mr->SetMaterial(Resources::Find<Material>(L"TitleBG"));
	//		player->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
	//		//player->AddComponent<CameraScript>();
	//	}

		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}