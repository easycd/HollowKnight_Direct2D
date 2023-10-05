#include "kmPlayerHP_State.h"
#include "kmTransform.h"
#include "kmGameObject.h"
#include "kmAnimator.h"
#include "kmResources.h"
#include "kmObject.h"
#include "kmMeshRenderer.h"

#include "kmPlayer.h"
#include "kmPlayerHP.h"

namespace km
{
	PlayerHP_State::PlayerHP_State()
		: mPlayer_HP(0)
	{
	}
	PlayerHP_State::~PlayerHP_State()
	{
	}
	void PlayerHP_State::Initialize()
	{
		HP_00 = object::Instantiate<PlayerHP>(eLayerType::UI);
		HP_01 = object::Instantiate<PlayerHP>(eLayerType::UI);
		HP_02 = object::Instantiate<PlayerHP>(eLayerType::UI);
		HP_03 = object::Instantiate<PlayerHP>(eLayerType::UI);
		HP_04 = object::Instantiate<PlayerHP>(eLayerType::UI);

		HP_00->Empty();
		HP_01->Empty();
		HP_01->SetDistance(0.06f);
		HP_02->Empty();
		HP_02->SetDistance(0.12f);
		HP_03->Empty();
		HP_03->SetDistance(0.18f);
		HP_04->Empty();
		HP_04->SetDistance(0.24f);

		GameObject::Initialize();
	}

	void PlayerHP_State::Update()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayer_HP = mPlayer->GetPlayerHPState();

		if (mPlayer_HP == 4)
		{
			HP_04->Break();
		}
		if (mPlayer_HP == 3)
		{
			HP_03->Break();
		}
		if (mPlayer_HP == 2)
		{
			HP_02->Break();
		}
		if (mPlayer_HP == 1)
		{
			HP_01->Break();
		}
		if (mPlayer_HP == 0)
		{
			HP_00->Break();

		}

		GameObject::Update();
	}

	void PlayerHP_State::HP()
	{

	}
}