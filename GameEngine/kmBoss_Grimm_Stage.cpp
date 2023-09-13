#include "kmBoss_Grimm_Stage.h"
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
#include "kmPlayerScript.h"
#include "kmCollisionManager.h"
#include "kmAnimator.h"
#include "kmRigidbody.h"
#include "kmGroundScript.h"
#include "kmComputeShader.h"
#include "kmLight.h"
#include "kmGameObject.h"
#include "kmPlayer.h"
#include "kmGrimm.h"
#include "kmGrimmScript.h"

#include "kmSpike_Object.h"
#include "kmFlameBat.h"

#include "kmTrumpNpc.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Ground, true);

		ComputeShader* cs = new ComputeShader();
		cs->Create(L"PaintCS.hlsl", "main");

		//텐트 배경
		{
			GameObject* GrimmStageBG = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 10.0f), eLayerType::BG);
			GrimmStageBG->GetComponent<Transform>()->SetScale(Vector3(8.3f, 1.5f, 0.0f));
			GrimmStageBG->SetName(L"Grimm_Tent");
		
			MeshRenderer* mr = GrimmStageBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GrimmStage_BG"));
		}

		//바닥
		{
			GameObject* GrimmStageGround = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 8.0f), eLayerType::BG);
			GrimmStageGround->GetComponent<Transform>()->SetScale(Vector3(8.3f, 1.5f, 0.0f));
			GrimmStageGround->SetName(L"Grimm_Ground");

			MeshRenderer* mr = GrimmStageGround->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GrimmStage_Ground"));
		}

		//캐릭터
		{
			mPlayer = object::Instantiate<Player>(eLayerType::Player);
			mPlayer->SetName(L"Player");

			mPlayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.1f, 0.0f));
			//mPlayer->GetComponent<Transform>()->SetPosition(Vector3(-3.3f, 0.1f, 0.0f));
		}

		//보스
		{
			mGrimm = object::Instantiate<Grimm>(eLayerType::Boss);
			mGrimm->SetName(L"Grimm");
		}

		//보스
		{
			mNpc = object::Instantiate<TrumpNpc>(eLayerType::Npc);
			mNpc->SetName(L"Trump");
			mNpc->GetComponent<Transform>()->SetPosition(Vector3(-2.05f, -0.43f, 0.5f));
			mNpc->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.3f, 0.0f));
		}

		////Spike Object Test
		//{
		//	sp = object::Instantiate<Spike_Object>(eLayerType::Boss);
		//	sp->SetName(L"Spike");
		//}

		////FlameBat Test
		//{
		//	fb = object::Instantiate<FlameBat>(eLayerType::Boss);
		//	fb->SetName(L"FlameBat");
		//}
		

		//{
		//	Grimm = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 0.1f), eLayerType::Boss);
		//	Grimm->SetName(L"Grimm");
		//
		//	MeshRenderer* mr = Grimm->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimaionMaterial"));
		//
		//	Animator* at = Grimm->AddComponent<Animator>();
		//	Grimm->AddComponent<GrimmScript>();
		//}

		{
			GameObject* camera = object::Instantiate<GameObject>(Vector3(1.0f, 0.0f, 0.0f), eLayerType::Camera);

			mCamera = camera->AddComponent<Camera>();
			mCamera->TurnLayerMask(eLayerType::UI, false);

			CameraScript* camerscript = camera->AddComponent<CameraScript>();
			camerscript->SetTarget(mPlayer);
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

		////UI Camera
		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::Boss, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->TurnLayerMask(eLayerType::Boss, false);
		//	//camera->AddComponent<CameraScript>();
		//}

		//Ground
		{
			GroundScript* ground = object::Instantiate<GroundScript>(eLayerType::Ground);
			ground->Initialize();
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -0.8f, 0.0f));
			tr->SetScale(Vector3(100.0f, 0.5f, 1.0f));
		}

		{
			GameObject* light = new GameObject();
			light->SetName(L"Sun");
			AddGameObject(eLayerType::Light, light);
			Light* lightComp = light->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}
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
	void Boss_Grimm_Stage::Render()
	{
		Scene::Render();
	}
	void Boss_Grimm_Stage::OnEnter()
	{
		mGrimm->Idle();
		mNpc->Initialize();
		//sp->Spike_On_Delay();
		//fb->On();
		renderer::mainCamera = mCamera;
	}
	void Boss_Grimm_Stage::OnExit()
	{
	}
}