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

	private:
		SDL_AudioDeviceID m_device;
		std::array<float, CHANNELS<size_t>* BUFFER_SIZE<size_t>> m_buffer;

		double m_time;
	};
}
