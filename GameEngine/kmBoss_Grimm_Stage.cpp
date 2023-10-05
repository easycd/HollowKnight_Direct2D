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
#include "kmCollisionManager.h"
#include "kmAnimator.h"
#include "kmRigidbody.h"
#include "kmGroundScript.h"
#include "kmWall.h"
#include "kmComputeShader.h"
#include "kmLight.h"
#include "kmGameObject.h"
#include "kmPlayer.h"
#include "kmGrimm.h"
#include "kmGrimmScript.h"

#include "kmSpike_Object.h"
#include "kmFlameBat.h"

#include "kmTrumpNpc.h"
#include "kmCrowd.h"

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
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Wall, true);

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
		//배경 색
		{
			GameObject* BG = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 12.0f), eLayerType::BG);
			BG->GetComponent<Transform>()->SetScale(Vector3(8.3f, 1.5f, 0.0f));
			BG->SetName(L"Tent_BG");
		
			MeshRenderer* mr = BG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Black_BG"));
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

			mPlayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.1f, 0.1f));
			//mPlayer->GetComponent<Transform>()->SetPosition(Vector3(-3.9f, 0.1f, 0.0f));
		}

		//보스
		{
			mGrimm = object::Instantiate<Grimm>(eLayerType::Boss);
			mGrimm->SetName(L"Grimm");
		}

		//Trump NPC
		{
			mNpc = object::Instantiate<TrumpNpc>(eLayerType::Npc);
			mNpc->SetName(L"Trump");
			mNpc->GetComponent<Transform>()->SetPosition(Vector3(-2.05f, -0.43f, 0.5f));
			mNpc->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.3f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_00 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_00->SetName(L"Crowd00");
			mCrowd_00->GetComponent<Transform>()->SetPosition(Vector3(-1.0f, -0.13f, 11.0f));
			mCrowd_00->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_01 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_01->SetName(L"Crowd01");
			mCrowd_01->GetComponent<Transform>()->SetPosition(Vector3(-0.85f, 0.05f, 11.0f));
			mCrowd_01->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_02 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_02->SetName(L"Crowd02");
			mCrowd_02->GetComponent<Transform>()->SetPosition(Vector3(-0.7f, -0.15f, 11.0f));
			mCrowd_02->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_03 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_03->SetName(L"Crowd03");
			mCrowd_03->GetComponent<Transform>()->SetPosition(Vector3(-0.4f, -0.16f, 11.0f));
			mCrowd_03->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_04 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_04->SetName(L"Crowd04");
			mCrowd_04->GetComponent<Transform>()->SetPosition(Vector3(-0.5f, 0.0f, 11.1f));
			mCrowd_04->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_05 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_05->SetName(L"Crowd05");
			mCrowd_05->GetComponent<Transform>()->SetPosition(Vector3(-0.2f, 0.0f, 11.2f));
			mCrowd_05->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_06 = object::Instantiate<Crowd>(eLayerType::Npc); 
			mCrowd_06->SetName(L"Crowd06");
			mCrowd_06->GetComponent<Transform>()->SetPosition(Vector3(-0.05f, -0.19f, 11.0f));
			mCrowd_06->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_07 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_07->SetName(L"Crowd07");
			mCrowd_07->GetComponent<Transform>()->SetPosition(Vector3(0.22f, -0.19f, 11.0f));
			mCrowd_07->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_08 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_08->SetName(L"Crowd08");
			mCrowd_08->GetComponent<Transform>()->SetPosition(Vector3(0.5f, -0.15f, 11.0f));
			mCrowd_08->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_09 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_09->SetName(L"Crowd09");
			mCrowd_09->GetComponent<Transform>()->SetPosition(Vector3(0.12f, 0.0f, 11.0f));
			mCrowd_09->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}
		//Crowd NPC
		{
			mCrowd_10 = object::Instantiate<Crowd>(eLayerType::Npc);
			mCrowd_10->SetName(L"Crowd10");
			mCrowd_10->GetComponent<Transform>()->SetPosition(Vector3(0.45f, 0.0f, 11.1f));
			mCrowd_10->GetComponent<Transform>()->SetScale(Vector3(0.3f, 0.2f, 0.0f));
		}

		{
			GameObject* camera = object::Instantiate<GameObject>(Vector3(1.0f, 0.0f, 0.0f), eLayerType::Camera);

			mCamera = camera->AddComponent<Camera>();
			mCamera->TurnLayerMask(eLayerType::UI, false);

			CameraScript* camerscript = camera->AddComponent<CameraScript>();
			camerscript->SetTarget(mPlayer);
			camerscript->SetWeight(Vector2(-3.3f, 0.28f));
			camerscript->SetHight(-0.2f);
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

		//LeftWall
		{
			{
				Wall* LeftWall = object::Instantiate<Wall>(eLayerType::Wall);
				LeftWall->Initialize();
				Transform* tr = LeftWall->GetComponent<Transform>();
				tr->SetPosition(Vector3(-1.25f, 0.0f, 0.0f));
				tr->SetScale(Vector3(0.1f, 2.0f, 1.0f));
			}
		}

		//RightWall
		{
			{
				Wall* RightWall = object::Instantiate<Wall>(eLayerType::Wall);
				RightWall->Initialize();
				Transform* tr = RightWall->GetComponent<Transform>();
				tr->SetPosition(Vector3(1.0f, 0.0f, 0.0f));
				tr->SetScale(Vector3(0.1f, 2.0f, 1.0f));
			}
		}

		//Light
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
		mCrowd_00->Play_Right();
		mCrowd_01->Play_Right();
		mCrowd_02->Play_Right();
		mCrowd_03->Play_Right();
		mCrowd_04->Play_Right();
		mCrowd_05->Play_Right();
		mCrowd_06->Play_Left();
		mCrowd_07->Play_Left();
		mCrowd_08->Play_Left();
		mCrowd_09->Play_Left();
		mCrowd_10->Play_Left();
		renderer::mainCamera = mCamera;
	}
	void Boss_Grimm_Stage::OnExit()
	{
	}
}