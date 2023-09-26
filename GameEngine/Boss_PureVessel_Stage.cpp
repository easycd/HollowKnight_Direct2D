#include "Boss_PureVessel_Stage.h"
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
#include "kmWall.h"
#include "kmComputeShader.h"
#include "kmLight.h"
#include "kmGameObject.h"

#include "kmPlayer.h"
#include "kmPureVessel.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Boss, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Ground, true);

		{
			GameObject* TitleBG = new GameObject();
			TitleBG->SetName(L"PureVesselStage_BG");
			AddGameObject(eLayerType::BG, TitleBG);
			MeshRenderer* mr = TitleBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"PureVesselStage_BG"));
			TitleBG->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
			TitleBG->GetComponent<Transform>()->SetScale(Vector3(2.4f, 1.1f, 0.0f));
		}

		//Ä³¸¯ÅÍ
		{
			mPlayer = object::Instantiate<Player>(eLayerType::Player);
			mPlayer->SetName(L"Player");
		
			mPlayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.1f, 0.0f));
			//mPlayer->GetComponent<Transform>()->SetPosition(Vector3(-3.3f, 0.1f, 0.0f));
		}

		{
			mPureVessel = object::Instantiate<PureVessel>(eLayerType::Boss);
			mPureVessel->SetName(L"PureVessel");
		}

		//Camera
		{
			GameObject* camera = object::Instantiate<GameObject>(Vector3(1.0f, 0.0f, 0.0f), eLayerType::Camera);
		
			mCamera = camera->AddComponent<Camera>();
			mCamera->TurnLayerMask(eLayerType::UI, false);
		
			CameraScript* camerscript = camera->AddComponent<CameraScript>();
			camerscript->SetTarget(mPlayer);
		}

		//Ground
		{
			GroundScript* ground = object::Instantiate<GroundScript>(eLayerType::Ground);
			ground->Initialize();
			Transform* tr = ground->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, -0.66f, 0.0f));
			tr->SetScale(Vector3(100.0f, 0.5f, 1.0f));
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
	void Boss_PureVessel_Stage::OnEnter()
	{
		mPureVessel->Intro_Idle();
		renderer::mainCamera = mCamera;
	}
	void Boss_PureVessel_Stage::OnExit()
	{
	}
}