#pragma once
#include "..\Engine_SOURCE\kmSceneManager.h"
#include "kmPlayScene.h"
#include "kmTitleScene.h"
#include "kmDirtmouth.h"
#include "kmBoss_Grimm_Stage.h"
#include "kmGodhome.h"
#include "Boss_PureVessel_Stage.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\GameEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\GameEngine.lib")
#endif



namespace km
{
	void InitializeScenes()
	{
		//PlayScene* playScene = new PlayScene();
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<Dirtmouth>(L"Dirtmouth");
		SceneManager::CreateScene<Boss_Grimm_Stage>(L"Boss_Grimm_Stage");
		//SceneManager::CreateScene<Godhome>(L"Godhome");
		SceneManager::CreateScene<Boss_PureVessel_Stage>(L"Boss_PureVessel_Stage");

		SceneManager::LoadScene(L"TitleScene");
	}
}