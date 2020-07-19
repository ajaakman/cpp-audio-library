#pragma once

#include "./IAudio.h"
#include "../Globals.h"
#include "../Components/MasterMixer.h"

#include <array>
#include <SDL.h>

namespace audio
{
	class SDL2Audio final : public IAudio
	{
	public:
		SDL2Audio();
		~SDL2Audio() override;
		SDL2Audio(const SDL2Audio&) = delete;
		SDL2Audio(SDL2Audio&&) = delete;
		SDL2Audio& operator=(const SDL2Audio&) = delete;
		SDL2Audio& operator=(SDL2Audio&&) = delete;

		virtual const int initAudio() override;
		virtual void lockAudioThread() override;
		virtual void unlockAudioThread() override;

	public:
		MasterMixer masterMixer;

	private:
		static void forwardAudioCallback(void* const userdata, Uint8* const stream, const int stream_length);
		void audioCallback(Uint8* const& stream, const int& stream_length);

        friend int processAudio(void* ptr);

	private:
		SDL_AudioDeviceID m_device;
		std::array<float, CHANNELS<size_t>* BUFFER_SIZE<size_t>> m_buffer;

        SDL_Thread* audioThread{ nullptr };
        SDL_cond* cvAudioReadyToCopy{ nullptr };
        SDL_cond* cvAudioCopied{ nullptr };
        SDL_mutex* sdl_lock{ nullptr };
        SDL_mutex* audio_lock{ nullptr };

		double m_time;
        bool m_dataReady;
        bool m_dataCopied;
        bool m_shuttingDown;
	};
}
