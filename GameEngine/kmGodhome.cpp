#include "kmGodhome.h"
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
	Godhome::Godhome()
	{
	}
	Godhome::~Godhome()
	{
	}
	void Godhome::Initialize()
	{
		{
			GameObject* TitleBG = new GameObject();
			TitleBG->SetName(L"GodHome_BG");
			AddGameObject(eLayerType::BG, TitleBG);
			MeshRenderer* mr = TitleBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GodHome_BG"));
			TitleBG->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.1f, 0.0f));
			TitleBG->GetComponent<Transform>()->SetScale(Vector3(20.0f, 6.0f, 0.0f));
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
		//{
		//	GameObject* camera = new GameObject();
		//	AddGameObject(eLayerType::BG, camera);
		//	camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		//	Camera* cameraComp = camera->AddComponent<Camera>();
		//	cameraComp->TurnLayerMask(eLayerType::Player, false);
		//	//camera->AddComponent<CameraScript>();
		//}
	}
	void Godhome::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::K))
		{
			SceneManager::LoadScene(L"Boss_PureVessel_Stage");
		}
	}
	void Godhome::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void Godhome::Render()
	{
		Scene::Render();
	}
}
