#pragma once

#include "IAudio.h"
#include "MasterMixer.h"

#include <SDL.h>

namespace audio
{
	class SDL2Audio : public IAudio
	{
	public:
		SDL2Audio();
		virtual ~SDL2Audio() override;

		virtual const int InitAudio() override;
		virtual void LockAudioThread() override;
		virtual void UnlockAudioThread() override;

	public:
		MasterMixer masterMixer;

	private:
		static void ForwardAudioCallback(void* const userdata, Uint8* const stream, const int streamLength);
		void AudioCallback(Uint8* const& stream, const int& streamLength);

	private:
		SDL_AudioDeviceID m_Device;

		double m_dTime;

	};
}
