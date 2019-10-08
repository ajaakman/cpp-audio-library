#include "./SDL2Audio.h"

namespace audio
{
	SDL2Audio::SDL2Audio()
		: masterMixer(&m_dTime), m_Device(NULL), m_dTime(0.0f), m_Buffer()
	{	}

	SDL2Audio::~SDL2Audio()
	{
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		SDL_Quit();
	}

	const int SDL2Audio::InitAudio()
	{
		if (SDL_Init(SDL_INIT_AUDIO) != 0)
		{
			SDL_Log("Unable to initialize SDL: %s.", SDL_GetError());
			return 101;
		}

		SDL_AudioSpec specin;
		SDL_AudioSpec specout;

		SDL_memset(&specin, 0, sizeof(specin));
		SDL_memset(&specout, 0, sizeof(specout));

		specin.channels = CHANNELS<Uint8>;
		specin.freq = SAMPLE_RATE<int>;
		specin.format = AUDIO_F32;
		specin.samples = BUFFER_SIZE<Uint16>;
		specin.userdata = this;
		specin.callback = ForwardAudioCallback;

		m_Device = SDL_OpenAudioDevice(NULL, 0, &specin, &specout, 0);

		if (!m_Device)
		{
			SDL_Log("Failed to initialize audio device!!! %s.", SDL_GetError());
			return 102;
		}

		if (specin.freq != specout.freq)
		{
			SDL_Log("Requested fequency {%i} does not match received frequency: {%i}.", specin.freq, specout.freq);
			return 103;
		}

		if (specin.format != specout.format)
		{
			SDL_Log("Requested format does not match received format");
			return 104;
		}

		if (specin.channels != specout.channels)
		{
			SDL_Log("Requested channels {%i} does not match received channels: {%i}.", specin.channels, specout.channels);
			return 105;
		}

		if (specin.silence != specout.silence)
		{
			SDL_Log("Requested silence {%i} does not match received silence: {%i}.", specin.silence, specout.silence);
			return 106;
		}

		if (specin.samples != specout.samples)
		{
			SDL_Log("Requested samples {%i} does not match received samples: {%i}.", specin.samples, specout.samples);
			return 107;
		}

		if (specin.callback != specout.callback)
		{
			SDL_Log("Requested callback does not match received callback.");
			return 108;
		}

		if (specin.userdata != specout.userdata)
		{
			SDL_Log("Requested userdata does not match received userdata.");
			return 109;
		}

		SDL_PauseAudioDevice(m_Device, 0);

		return 0;
	}

	void SDL2Audio::LockAudioThread()
	{
		SDL_LockAudioDevice(m_Device);
	}

	void SDL2Audio::UnlockAudioThread()
	{
		SDL_UnlockAudioDevice(m_Device);
	}

	void SDL2Audio::ForwardAudioCallback(void* const userdata, Uint8* const stream, const int streamLength)
	{
		static_cast<SDL2Audio*>(userdata)->AudioCallback(stream, streamLength);
	}

	void SDL2Audio::AudioCallback(Uint8* const& stream, const int& streamLength)
	{
		for (size_t i = 0; i < m_Buffer.size(); i += CHANNELS<size_t>)
		{
			auto out = masterMixer.GetMasterOutput();

			for (size_t j = 0; j < CHANNELS<size_t>; j++)
			{
				m_Buffer[i + j] = out[j];
			}

			m_dTime += 1.0 / SAMPLE_RATE<double>;

			if (m_dTime > OSC_TUNE_ACC<double>)
			{
				double intpart;
				m_dTime = modf(m_dTime, &intpart);			
			}
		}

		SDL_memcpy(stream, &m_Buffer[0], streamLength);
	}
}