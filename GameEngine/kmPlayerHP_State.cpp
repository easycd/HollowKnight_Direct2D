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

		HP_00->Idle();
		HP_01->Idle();
		HP_01->SetDistance(0.06f);
		HP_02->Idle();
		HP_02->SetDistance(0.12f);
		HP_03->Idle();
		HP_03->SetDistance(0.18f);
		HP_04->Idle();
		HP_04->SetDistance(0.24f);

		GameObject::Initialize();
	}

	void PlayerHP_State::Update()
	{
		mPlayer = SceneManager::GetPlayer();
		mPlayer_HP = mPlayer->GetPlayerHP();

		HPState = mPlayer->GetPlayerHPState();

		//HP 회복
		if (mPlayer_HP == 5 && Check_Break_04 == false && HPState)
		{
			Check_Break_04 = true;
			HP_04->Refill();
		}
		if (mPlayer_HP == 4 && Check_Break_03 == false && HPState)
		{
			Check_Break_03 = true;
			HP_03->Refill();
		}
		if (mPlayer_HP == 3 && Check_Break_02 == false && HPState)
		{
			Check_Break_02 = true;
			HP_02->Refill();
		}
		if (mPlayer_HP == 2 && Check_Break_01 == false && HPState)
		{
			Check_Break_01 = true;
			HP_01->Refill();
		}

		//HP 차감
		if (mPlayer_HP == 4 && Check_Break_04 && HPState == false)
		{
			Check_Break_04 = false;
			HP_04->Break();
		}
		if (mPlayer_HP == 3 && Check_Break_03 && HPState == false)
		{
			Check_Break_03 = false;
			HP_03->Break();
		}
		if (mPlayer_HP == 2 && Check_Break_02 && HPState == false)
		{
			Check_Break_02 = false;
			HP_02->Break();
		}
		if (mPlayer_HP == 1 && Check_Break_01 && HPState == false)
		{
			Check_Break_01 = false;
			HP_01->Break();
		}
		if (mPlayer_HP == 0 && Check_Break_00 && HPState == false)
		{
			Check_Break_00 = false;
			HP_00->Break();
		}

		GameObject::Update();
	}

	void PlayerHP_State::HP()
	{

	}
}