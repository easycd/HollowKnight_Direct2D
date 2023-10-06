#pragma once
#include "kmResource.h"
#include "kmFmod.h"

namespace km
{
	using namespace km::math;
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		~AudioClip();

		virtual HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const Vector3 pos, const Vector3 vel);
		void SetLoop(bool loop) { mbLoop = loop; }
		void SetVolume(float vol);
		void SetMute(bool mute);

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;
	};
}


