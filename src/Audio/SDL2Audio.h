#pragma once
#define SAMPLERATE 44100
#define CHANNELS 2
#define BUFFERSIZE 4096

#include "./IAudio.h"
#include "../Components/MasterMixer.h"

#include <array>
#include <SDL.h>

namespace audio
{
	class SDL2Audio final: public IAudio
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
		std::array<Sint16, CHANNELS * BUFFERSIZE> m_Buffer;

		double m_dTime;
	};
}
