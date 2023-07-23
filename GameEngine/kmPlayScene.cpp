#include "kmPlayScene.h"
#include "kmTransform.h"
#include "kmMeshRenderer.h"
#include "kmResources.h"
#include "kmMesh.h"
#include "kmCameraScript.h"
#include "kmCamera.h"
#include "kmSceneManager.h"
#include "kmGridScript.h"
#include "kmObject.h"
#include "kmRenderer.h"
#include "kmCollider2D.h"
#include "kmPlayerScript.h"
#include "kmCollisionManager.h"
#include "kmAnimator.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		{
			GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
			player->SetName(L"Zelda");

			Collider2D* cd = player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.2f, 1.2f));

			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));

			const float pi = 3.141592f;
			float degree = pi / 8.0f;

			player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
			//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));

			std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"LinkSprite", L"..\\Resources\\Texture\\linkSprites.png");
			Animator* at = player->AddComponent<Animator>();
			//at->Create(L"Idle", atlas, Vector2(0.0f, 0.0f), Vector2(120.0f, 130.0f), 3);
			at->Create(L"Idle", atlas, Vector2(0.0f, 0.0f), Vector2(349.0f, 186.0f), 9);

			at->PlayAnimation(L"Idle", true);
			player->AddComponent<PlayerScript>();
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::Monster, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			Collider2D* cd = player->AddComponent<Collider2D>();
			//player->AddComponent<PlayerScript>();
		}

		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Smile");
		//	AddGameObject(eLayerType::UI, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
		//	//player->AddComponent<CameraScript>();
		//}

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
		//  cameraComp->TurnLayerMask(eLayerType::Monster, false);
		//	//camera->AddComponent<CameraScript>();
		//}

		//{
		//	GameObject* grid = new GameObject();
		//	grid->SetName(L"Grid");
		//	AddGameObject(eLayerType::Grid, grid);
		//	MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		//	GridScript* gridSc = grid->AddComponent<GridScript>();
		//	gridSc->SetCamera(cameraComp);
		//}


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

	void PlayScene::Render()
	{
		Scene::Render();
	}
}