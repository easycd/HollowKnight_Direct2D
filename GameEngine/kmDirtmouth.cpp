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
#include "kmCollisionManager.h"
#include "kmAnimator.h"
#include "kmRigidbody.h"
#include "kmGroundScript.h"
#include "kmComputeShader.h"
#include "kmLight.h"
#include "kmGameObject.h"
#include "kmPlayer.h"

#include "kmPlayerUI.h"
#include "kmSoulGauge.h"
#include "kmPlayerHP_State.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

		ComputeShader* cs = new ComputeShader();
		cs->Create(L"PaintCS.hlsl", "main");

		{ //BackGround
			GameObject* GrimmTownBG = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 10.0f), eLayerType::BG);
			//GrimmTownBG->GetComponent<Transform>()->SetScale(Vector3(23.0f,6.2f, 0.0f));
			GrimmTownBG->GetComponent<Transform>()->SetScale(Vector3(5.0f, 1.2f, 0.0f));
			GrimmTownBG->SetName(L"Grimm_Town");
		
			MeshRenderer* mr = GrimmTownBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GrimmTown"));
			//player->AddComponent<CameraScript>();
		}

		//Ä³¸¯ÅÍ
		{
			player = object::Instantiate<Player>(eLayerType::Player);
			player->SetName(L"Player");
			player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 0.0f));
		}

		//Ground
		{
			GroundScript* ground = object::Instantiate<GroundScript>(eLayerType::Ground);
			ground->SetName(L"Ground");
			ground->Initialize();
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -0.48f, 0.0f));
			//tr->SetPosition(Vector3(0.0f, -0.4f, 0.0f));
			tr->SetScale(Vector3(100.0f, 0.1f, 1.0f));

		}

		{
			mPlayerUI = object::Instantiate<PlayerUI>(eLayerType::UI);
			mSoulGauge = object::Instantiate<SoulGauge>(eLayerType::UI);
			HP_State = object::Instantiate<PlayerHP_State>(eLayerType::UI);
		}

		{
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.0f), eLayerType::Camera);

			mCamera = camera->AddComponent<Camera>();
			mCamera->TurnLayerMask(eLayerType::UI, true);

			mCamerscript = camera->AddComponent<CameraScript>();
			mCamerscript->SetTarget(player);
			mCamerscript->SetWeight(Vector2(-1.698f, 1.68f));
		}

		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::Camera, camera);
		//
		//	mCamera = camera->AddComponent<Camera>();
		//	mCamera->TurnLayerMask(eLayerType::UI, false);
		//
		//	CameraScript* camerscript = camera->AddComponent<CameraScript>();
		//	camerscript->SetTarget(player);
		//}


		//UI Camera
		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::Player, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->TurnLayerMask(eLayerType::Player, false);
		//}

		{
			GameObject* light = new GameObject();
			light->SetName(L"Smile");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
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
	void Dirtmouth::OnEnter()
	{
		renderer::mainCamera = mCamera;
	}
	void Dirtmouth::OnExit()
	{
	}
}